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
    if (!fun)
        throw std::runtime_error("we are not inside a function context");

    const std::string paramName = ctx->param->getText();
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
