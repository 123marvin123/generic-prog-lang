#include "visitor/ExpressionVisitor.h"

std::any ExpressionVisitor::visitLiteralExpression(CongParser::LiteralExpressionContext* ctx)
{
    Expression* exp = nullptr;
    if (ctx->literal()->REAL())
    {
        exp = new RealExpression(
            ns->get_sema(),
            std::stod(ctx->literal()->REAL()->getText()),
            ctx->literal()->DYNAMIC_ANNOTATOR() ? true : false);
    }
    else if (ctx->literal()->INTEGER())
    {
        exp = new IntegerExpression(
            ns->get_sema(),
            std::stol(ctx->literal()->INTEGER()->getText()),
            ctx->literal()->DYNAMIC_ANNOTATOR() ? true : false);
    }
    else if (ctx->literal()->STRING())
    {
        exp = new StringExpression(
            ns->get_sema(),
            utils::cleanup_string_literal(ctx->literal()->STRING()->getText()));
    }
    else if (ctx->literal()->BOOL())
    {
        exp = new BooleanExpression(
            ns->get_sema(),
            ctx->literal()->BOOL()->getText() == "true",
            ctx->literal()->DYNAMIC_ANNOTATOR() ? true : false);
    }

    if (exp)
        return utils::dyn_cast<Expression>(exp);

    throw std::runtime_error(std::format("Unknown literal type {}", ctx->getText()));
}

std::any ExpressionVisitor::visitParameterOrConceptReferenceExpression(CongParser::ParameterOrConceptReferenceExpressionContext* ctx)
{
    const std::string paramName = ctx->paramOrConcept->getText();

    if (!fun)
        throw SemaError("We are not inside a function context", ctx);

    if (const auto let_binding = findLetBinding(paramName)) {
        return utils::dyn_cast<Expression>(
            new LetVariableReferenceExpression(ns->get_sema(), paramName, let_binding->value)
        );
    }

    if (const auto lambda_param = findLambdaParam(paramName); lambda_param.has_value())
    {
        return utils::dyn_cast<Expression>(new LambdaVariableReferenceExpression(ns->get_sema(), std::get<0>
        (*lambda_param), std::get<1>(*lambda_param)));
    }
    
    const auto& fqi = utils::split_fully_qualified_identifier(paramName);
    if (const auto& concept_ = utils::resolve_fully_qualified_identifier<Concept>(fqi, ns);
        concept_.has_value())
    {
        return utils::dyn_cast<Expression>(new ConceptReferenceExpression(get_sema(), *concept_));
    }

    const opt<FunctionParameter*> param = fun->find_function_parameter(paramName);
    if (!param.has_value() || !param.value())
        throw SemaError(std::format("Could not find parameter or concept {}", paramName), ctx);

    try
    {
        return utils::dyn_cast<Expression>(new FunctionParameterExpression(ns->get_sema(), param.value()));
    }
    catch (const SemaError& e)
    {
        std::throw_with_nested(SemaError("Could not instantiate parameter expression", ctx));
    }
}

std::any ExpressionVisitor::visitCallExpression(CongParser::CallExpressionContext* ctx)
{
    const utils::FQIInfo& info = utils::split_fully_qualified_identifier(ctx->fun->getText());
    const opt<Function*> target_fun = utils::resolve_fully_qualified_identifier<Function>(info, ns);
    if (!target_fun.has_value() || !target_fun.value())
        throw SemaError(std::format("Could not find function {}", ctx->fun->getText()), ctx);

    vec<s_ptr<Expression>> subExpressions;
    subExpressions.reserve(ctx->expression().size());

    for (CongParser::ExpressionContext* exp : ctx->expression())
    {
        if (const std::any result = visit(exp);
            result.has_value() && result.type() == typeid(Expression*))
            subExpressions.push_back(std::shared_ptr<Expression>(std::any_cast<Expression*>(result)));
        else
            throw SemaError(std::format("Could not parse expression {}", exp->getText()), exp);
    }

    if (const auto& fun_params = target_fun.value()->get_parameters();
        subExpressions.size() != fun_params.size())
        throw SemaError(std::format("Function {} requires {} arguments but {} were provided.",
                                     target_fun.value()->get_identifier(),
                                     fun_params.size(), subExpressions.size()), ctx);

    try
    {
        return utils::dyn_cast<Expression>(new CallExpression(ns->get_sema(), target_fun.value(), subExpressions));
    }
    catch (const SemaError& e)
    {
        throw SemaError(std::format("Could not instantiate function call expression: {}", e.what()), ctx);
    }

}

std::any ExpressionVisitor::visitArithmeticExpression(CongParser::ArithmeticExpressionContext* ctx)
{
    Expression* left_exp = nullptr;
    Expression* right_exp = nullptr;

    if (const std::any left = visit(ctx->left); left.has_value() && left.type() == typeid(Expression*))
        left_exp = std::any_cast<Expression*>(left);
    else
        throw SemaError("Left expression is not valid", ctx);

    if (const std::any right = visit(ctx->right); right.has_value() && right.type() == typeid(Expression*))
        right_exp = std::any_cast<Expression*>(right);
    else
        throw SemaError("Right expression is not valid", ctx);

    const std::string operator_str = ctx->op->getText();
    auto op_result = utils::get_operator_for_string(operator_str);
    if (!op_result.has_value())
        throw std::runtime_error(std::format("Unknown operator {}", operator_str));

    try
    {
        return utils::dyn_cast<Expression>(
            new ArithmeticExpression(ns->get_sema(), s_ptr<Expression>(left_exp), s_ptr<Expression>(right_exp), *op_result));
    }
    catch (const SemaError& e)
    {
        throw SemaError("Could not instantiate arithmetic expression", ctx);
    }
}

std::any ExpressionVisitor::visitLetExpression(CongParser::LetExpressionContext* ctx)
{
    vec<LetBinding> current_scope;

    for (const auto& binding : ctx->letBinding())
    {
        if (std::any res = visit(binding); res.has_value() && res.type() == typeid(LetBinding))
        {
            const auto& b = std::any_cast<LetBinding>(res);
            current_scope.push_back(b);
        }
    }

    let_binding_stack.push(current_scope);

    vec<s_ptr<Expression>> body_expressions;

    auto* expr_block = ctx->body;
    for (auto* expr_ctx : expr_block->expression())
    {
        if (const std::any body_result = visit(expr_ctx);
            body_result.has_value() && body_result.type() == typeid(Expression*))
        {
            auto* body_exp = std::any_cast<Expression*>(body_result);
            body_expressions.push_back(s_ptr<Expression>(body_exp));
        }
        else
        {
            let_binding_stack.pop();
            throw SemaError("Could not parse body expression in let block", expr_ctx);
        }
    }

    let_binding_stack.pop();

    if (body_expressions.empty())
    {
        throw SemaError("Let expression body cannot be empty", ctx);
    }

    try
    {
        return utils::dyn_cast<Expression>(
            new LetExpression(ns->get_sema(), current_scope, std::move(body_expressions)));
    }
    catch (const SemaError& e)
    {
        throw SemaError("Could not instantiate let expression", ctx);
    }
}

std::any ExpressionVisitor::visitOpenBindingExpression(CongParser::OpenBindingExpressionContext* context)
{
    // get the placeholder name from the context
    const std::string& placeholder = context->OPEN_BINDING()->getText().substr(1);
    const unsigned int N = std::stoul(placeholder);

    return utils::dyn_cast<Expression>(new OpenBindingExpression(ns->get_sema(), N));
}

std::any ExpressionVisitor::visitQuoteExpression(CongParser::QuoteExpressionContext* context)
{
    if (const std::any result = visit(context->expression()); result.has_value() && result.type() == typeid(Expression*))
    {
        auto* value_exp = std::any_cast<Expression*>(result);
        return utils::dyn_cast<Expression>(new QuoteExpression(sema, s_ptr<Expression>(value_exp)));
    }

    throw SemaError("Could not instantiate inner quote expression");
}

std::any ExpressionVisitor::visitEvalExpression(CongParser::EvalExpressionContext* context)
{
    if (const std::any result = visit(context->expression());
        result.has_value() && result.type() == typeid(Expression*))
    {
        auto* value_exp = std::any_cast<Expression*>(result);
        return utils::dyn_cast<Expression>(new EvalExpression(sema, s_ptr<Expression>(value_exp)));
    }

    throw SemaError("Could not instantiate inner eval expression");
}
std::any ExpressionVisitor::visitRequiresCallExpression(CongParser::RequiresCallExpressionContext* ctx)
{
    if (const auto& r = fun->find_requirement(utils::cleanup_string_literal(ctx->STRING()->getText())); r.has_value())
    {
        return utils::dyn_cast<Expression>(new RequiresCallExpression(sema, *r.value(), fun));
    }

    throw SemaError(
        std::format("Requirement with name {} not found.", utils::cleanup_string_literal(ctx->STRING()->getText())),
        ctx);
}
std::any ExpressionVisitor::visitConditionalExpression(CongParser::ConditionalExpressionContext* ctx)
{
    const auto& [cond, left, right] = std::make_tuple(visit(ctx->cond), visit(ctx->left), visit(ctx->right));

    if (!cond.has_value() || cond.type() != typeid(Expression*))
        throw SemaError(std::format("Condition value is not valid"), ctx);
    if (!left.has_value() || left.type() != typeid(Expression*))
        throw SemaError(std::format("Left value is not valid"), ctx);
    if (!right.has_value() || right.type() != typeid(Expression*))
        throw SemaError(std::format("Right value is not valid"), ctx);

    auto* cond_exp = std::any_cast<Expression*>(cond);
    auto* left_exp = std::any_cast<Expression*>(left);
    auto* right_exp = std::any_cast<Expression*>(right);

    return utils::dyn_cast<Expression>(
        new CallExpression(sema, sema->cond_function,
                           {std::shared_ptr<Expression>{cond_exp}, std::shared_ptr<Expression>{left_exp},
                            std::shared_ptr<Expression>{right_exp}}));
}

std::any ExpressionVisitor::visitParenthesizedExpression(CongParser::ParenthesizedExpressionContext* ctx)
{
    return visit(ctx->expression());
}

std::any ExpressionVisitor::visitComparisonExpression(CongParser::ComparisonExpressionContext* ctx)
{
    const auto& [left, right] = std::make_pair(visit(ctx->left), visit(ctx->right));
    if (!left.has_value() || left.type() != typeid(Expression*))
        throw SemaError(std::format("Left value is not valid"), ctx);

    if (!right.has_value() || right.type() != typeid(Expression*))
        throw SemaError(std::format("Right value is not valid"), ctx);

    static std::map<std::string, const Function*> comparison_functions = {
        {"<", sema->isLess_function},          {"<=", sema->isLessEqual_function}, {">", sema->isGreater_function},
        {">=", sema->isGreaterEqual_function}, {"==", sema->isEqual_function},     {"!=", sema->isNotEqual_function}};

    const std::string operator_str = ctx->op->getText();
    const auto& it = comparison_functions.find(operator_str);
    if (it == comparison_functions.end())
    {
        throw SemaError(std::format("Unknown comparison operator {}", operator_str), ctx);
    }

    return utils::dyn_cast<Expression>(
        new CallExpression(sema, it->second,
                           {std::shared_ptr<Expression>(std::any_cast<Expression*>(left)),
                            std::shared_ptr<Expression>(std::any_cast<Expression*>(right))}));
}
std::any ExpressionVisitor::visitLetBinding(CongParser::LetBindingContext* ctx)
{
    const std::string identifier = ctx->name->getText();

    checkNameCollision(identifier, ctx);

    Expression* value_exp = nullptr;
    if (const std::any value_result = visit(ctx->value);
        value_result.has_value() && value_result.type() == typeid(Expression*))
        value_exp = std::any_cast<Expression*>(value_result);
    else
        throw SemaError(std::format("Could not parse let value expression for {}", identifier), ctx);

    s_ptr<Expression> value_ptr(value_exp);

    return LetBinding(identifier, value_ptr);
}
std::any ExpressionVisitor::visitLambdaExpression(CongParser::LambdaExpressionContext* ctx)
{
    if (const auto& params = visitParameterList(ctx->parameterList()); params.has_value() &&
        params.type() == typeid(vec<std::tuple<std::string, std::variant<PlaceholderFunctionParameter*, Concept*>>>))
    {
        const auto& p = std::any_cast<vec<std::tuple<std::string, std::variant<PlaceholderFunctionParameter*,
        Concept*>>>>(params);
        auto* lambdaExp = new LambdaExpression(sema, p, nullptr);
        lambda_exp_stack.push(lambdaExp);
        if (const auto& exp = visit(ctx->body); exp.has_value() && exp.type() == typeid(Expression*))
        {
            lambdaExp->set_body(s_ptr<Expression>(std::any_cast<Expression*>(exp)));
            lambda_exp_stack.pop();
            return utils::dyn_cast<Expression>(lambdaExp);
        }
        lambda_exp_stack.pop();
    }

    throw SemaError("Could not parse lambda expression", ctx);
}
std::any ExpressionVisitor::visitParameterList(CongParser::ParameterListContext* ctx)
{
    vec<std::tuple<std::string, std::variant<PlaceholderFunctionParameter*, Concept*>>> params;
    for (const auto& p : ctx->parameter())
    {
        if (const auto& v = visit(p); v.has_value())
        {
            if (v.type() == typeid(std::tuple<std::string, PlaceholderFunctionParameter*>))
                params.push_back(std::any_cast<std::tuple<std::string, PlaceholderFunctionParameter*>>(v));
            else if (v.type() == typeid(std::tuple<std::string, Concept*>))
                params.push_back(std::any_cast<std::tuple<std::string, Concept*>>(v));
            else
                throw SemaError("Could not parse parameter list", p);
        }
    }

    return params;
}
std::any ExpressionVisitor::visitParameter(CongParser::ParameterContext* ctx)
{
    std::string name = ctx->name->getText();
    checkNameCollision(name, ctx);

    if (const auto& x = visit(ctx->placeholderOrQualifiedId()); x.has_value())
    {
        if (x.type() == typeid(Concept*))
        {
            return std::make_tuple<std::string, Concept*>(std::move(name), std::any_cast<Concept*>(x));
        }
        if (x.type() == typeid(PlaceholderFunctionParameter*))
        {
            return std::make_tuple<std::string, PlaceholderFunctionParameter*>(std::move(name), std::any_cast<PlaceholderFunctionParameter*>(x));
        }
    }

    throw SemaError(std::format("Could not parse parameter {}", name), ctx->placeholderOrQualifiedId());
}
std::any ExpressionVisitor::visitPlaceholderOrQualifiedId(CongParser::PlaceholderOrQualifiedIdContext* ctx)
{
    if (const auto& res = visit(ctx->placeholder()); res.has_value() && res.type() == typeid(opt<PlaceholderFunctionParameter*>))
    {
        if (auto param = std::any_cast<opt<PlaceholderFunctionParameter*>>(res); param.has_value())
            return param.value();
    }

    if (const auto& res = visit(ctx->qualifiedIdentifier()); res.has_value() && res.type() == typeid(utils::FQIInfo))
    {
        const auto& fqiInfo = std::any_cast<utils::FQIInfo>(res);
        opt<Concept*> c = utils::resolve_fully_qualified_identifier<Concept>(fqiInfo, ns);
        if (c.has_value())
            return c.value();
    }

    return nullptr;
}

std::any ExpressionVisitor::visitPlaceholder(CongParser::PlaceholderContext* ctx)
{
    const std::string name = ctx->name->getText();
    return fun->find_placeholder(name);
}
std::any ExpressionVisitor::visitQualifiedIdentifier(CongParser::QualifiedIdentifierContext* ctx)
{
    return utils::split_fully_qualified_identifier(ctx->getText());
}


void ExpressionVisitor::checkNameCollision(const std::string& identifier, antlr4::ParserRuleContext* ctx)
const
{
    if (fun) {
        if (fun->find_function_parameter(identifier).has_value()) {
            throw SemaError(std::format("Name collision: '{}' is already a function parameter", identifier), ctx);
        }
    }
    
    Namespace* current_ns = ns;
    while (current_ns) {
        if (current_ns->get_identifier() == identifier) {
            throw SemaError(std::format("Name collision: '{}' is already a namespace name", identifier), ctx);
        }
        current_ns = current_ns->get_parent();
    }

    if (ns->find_function(identifier).has_value()) {
        throw SemaError(std::format("Name collision: '{}' is already a function name", identifier), ctx);
    }

    if (findLetBinding(identifier).has_value()) {
        throw SemaError(std::format("Name collision: '{}' is already bound in current scope", identifier), ctx);
    }
}

opt<LetBinding> ExpressionVisitor::findLetBinding(const std::string& identifier) const
{
    std::stack<std::vector<LetBinding>> temp_stack = let_binding_stack;

    while (!temp_stack.empty())
    {
        for (const auto& current_scope = temp_stack.top(); const auto& binding : current_scope)
        {
            if (binding.identifier == identifier)
            {
                return binding;
            }
        }
        temp_stack.pop();
    }

    return std::nullopt;
}

opt<std::pair<LambdaExpression*, std::size_t>>
ExpressionVisitor::findLambdaParam(const std::string& string) const
{
    std::stack<LambdaExpression*> temp_stack = lambda_exp_stack;

    while (!temp_stack.empty())
    {
        auto* current_scope = temp_stack.top();
        auto& params = current_scope->get_params();
        for (int i = 0; i < params.size(); i++)
        {
            if (std::get<0>(params[i]) == string)
                return std::make_pair(current_scope, i);
        }

        temp_stack.pop();
    }

    return std::nullopt;
}

