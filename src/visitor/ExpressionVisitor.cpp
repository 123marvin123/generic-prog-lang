//
// Created by Marvin Haschker on 14.03.25.
//
#include "visitor/ExpressionVisitor.h"

std::any ExpressionVisitor::visitLiteralExpression(CongParser::LiteralExpressionContext* ctx)
{
    Expression* exp = nullptr;
    if (ctx->literal()->REAL())
        exp = new RealExpression(ns->get_sema(), std::stod(ctx->literal()->REAL()->getText()));
    else if (ctx->literal()->NUMBER())
        exp = new NumberExpression(ns->get_sema(), std::stol(ctx->literal()->NUMBER()->getText()));
    else if (ctx->literal()->STRING())
        exp = new StringExpression(ns->get_sema(), utils::cleanup_string_literal(ctx->literal()->STRING()->getText()));
    else if (ctx->literal()->BOOL())
        exp = new BooleanExpression(ns->get_sema(), ctx->literal()->BOOL()->getText() == "true");

    if (exp) return utils::dyn_cast<Expression>(exp);

    throw std::runtime_error("Unknown literal type");
}

std::any ExpressionVisitor::visitParameterReferenceExpression(CongParser::ParameterReferenceExpressionContext* ctx)
{
    const std::string paramName = ctx->param->getText();
    
    // First check for let-bindings in the current scope stack
    if (const auto let_binding = findLetBinding(paramName)) {
        // Create a LetVariableReferenceExpression that references the bound value
        return utils::dyn_cast<Expression>(
            new LetVariableReferenceExpression(ns->get_sema(), paramName, let_binding->value)
        );
    }
    
    // Then check for function parameters
    if (!fun)
        throw std::runtime_error("we are not inside a function context");

    const opt<FunctionParameter*> param = fun->find_function_parameter(paramName);
    if (!param.has_value() || !param.value())
        throw std::runtime_error(std::format("Could not find parameter {}", paramName));

    return utils::dyn_cast<Expression>(new FunctionParameterExpression(ns->get_sema(), param.value()));
}

std::any ExpressionVisitor::visitCallExpression(CongParser::CallExpressionContext* ctx)
{
    const utils::FQIInfo& info = utils::split_fully_qualified_identifier(ctx->fun->getText());
    const opt<Function*> target_fun = utils::resolve_fully_qualified_identifier<Function>(info, ns);
    if (!target_fun.has_value() || !target_fun.value())
        throw std::runtime_error(std::format("Could not find function {}", ctx->fun->getText()));

    vec<s_ptr<Expression>> subExpressions;
    subExpressions.reserve(ctx->expression().size());

    for (CongParser::ExpressionContext* exp : ctx->expression())
    {
        if (const std::any result = visit(exp);
            result.has_value() && result.type() == typeid(Expression*))
            subExpressions.push_back(std::shared_ptr<Expression>(std::any_cast<Expression*>(result)));
        else
            throw std::runtime_error(std::format("Could not parse expression {}", exp->getText()));
    }

    if (const auto& fun_params = target_fun.value()->get_parameters();
        subExpressions.size() < fun_params.size())
        throw std::runtime_error(std::format("Function {} requires {} arguments but only {} were provided.",
                                             target_fun.value()->get_identifier(),
                                             target_fun.value()->get_parameters().size(), subExpressions.size()));

    return utils::dyn_cast<Expression>(new CallExpression(ns->get_sema(), target_fun.value(), subExpressions));
}

std::any ExpressionVisitor::visitArithmeticExpression(CongParser::ArithmeticExpressionContext* ctx)
{
    Expression* left_exp = nullptr;
    Expression* right_exp = nullptr;

    if (const std::any left = visit(ctx->left); left.has_value() && left.type() == typeid(Expression*))
        left_exp = std::any_cast<Expression*>(left);
    else
        throw std::runtime_error("Left expression is not valid");

    if (const std::any right = visit(ctx->right); right.has_value() && right.type() == typeid(Expression*))
        right_exp = std::any_cast<Expression*>(right);
    else
        throw std::runtime_error("Right expression is not valid");

    const std::string operator_str = ctx->op->getText();
    auto op_result = utils::get_operator_for_string(operator_str);
    if (!op_result.has_value())
        throw std::runtime_error(std::format("Unknown operator {}", operator_str));

    return utils::dyn_cast<Expression>(
        new ArithmeticExpression(ns->get_sema(), s_ptr<Expression>(left_exp), s_ptr<Expression>(right_exp), *op_result));
}

std::any ExpressionVisitor::visitLetExpression(CongParser::LetExpressionContext* ctx)
{
    const std::string identifier = ctx->name->getText();

    checkNameCollision(identifier);
    
    Expression* value_exp = nullptr;
    if (const std::any value_result = visit(ctx->value); 
        value_result.has_value() && value_result.type() == typeid(Expression*))
        value_exp = std::any_cast<Expression*>(value_result);
    else
        throw std::runtime_error(std::format("Could not parse let value expression for {}", identifier));
    
    s_ptr<Expression> value_ptr(value_exp);

    vec<LetBinding> current_scope;
    current_scope.emplace_back(identifier, value_ptr);
    let_binding_stack.push(current_scope);

    vec<s_ptr<Expression>> body_expressions;

    auto* expr_block = ctx->body;
    for (auto* expr_ctx : expr_block->expression()) {
        if (const std::any body_result = visit(expr_ctx);
            body_result.has_value() && body_result.type() == typeid(Expression*)) {
            auto* body_exp = std::any_cast<Expression*>(body_result);
            body_expressions.push_back(s_ptr<Expression>(body_exp));
        } else {
            let_binding_stack.pop();
            throw std::runtime_error(std::format("Could not parse body expression in let block for {}", identifier));
        }
    }

    let_binding_stack.pop();
    
    if (body_expressions.empty()) {
        throw std::runtime_error(std::format("Let expression body for {} cannot be empty", identifier));
    }
    
    return utils::dyn_cast<Expression>(
        new LetExpression(ns->get_sema(), identifier, value_ptr, std::move(body_expressions)));
}

void ExpressionVisitor::checkNameCollision(const std::string& identifier) const
{
    if (fun) {
        if (fun->find_function_parameter(identifier).has_value()) {
            throw std::runtime_error(std::format("Name collision: '{}' is already a function parameter", identifier));
        }
    }
    
    Namespace* current_ns = ns;
    while (current_ns) {
        if (current_ns->get_identifier() == identifier) {
            throw std::runtime_error(std::format("Name collision: '{}' is already a namespace name", identifier));
        }
        current_ns = current_ns->get_parent();
    }

    if (ns->find_function(identifier).has_value()) {
        throw std::runtime_error(std::format("Name collision: '{}' is already a function name", identifier));
    }

    if (findLetBinding(identifier).has_value()) {
        throw std::runtime_error(std::format("Name collision: '{}' is already bound in current scope", identifier));
    }
}

opt<LetBinding> ExpressionVisitor::findLetBinding(const std::string& identifier) const
{
    std::stack<std::vector<LetBinding>> temp_stack = let_binding_stack;
    
    while (!temp_stack.empty()) {
        const auto& current_scope = temp_stack.top();
        for (const auto& binding : current_scope) {
            if (binding.identifier == identifier) {
                return binding;
            }
        }
        temp_stack.pop();
    }
    
    return std::nullopt;
}
