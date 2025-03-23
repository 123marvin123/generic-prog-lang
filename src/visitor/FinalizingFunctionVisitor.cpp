//
// Created by Marvin Haschker on 14.03.25.
//
#include "visitor/FinalizingFunctionVisitor.h"

std::any FinalizingFunctionVisitor::visitFunctionStmnt(CongParser::FunctionStmntContext* ctx)
{
    std::string fnName = ctx->name->getText();
    const opt<Function*> fn = get_current_namespace()->find_function(fnName);
    if (!fn.has_value() || !fn.value())
        throw std::runtime_error(std::format("Could not find function {}", fnName));

    current_function = fn.value();

    visitChildren(ctx);

    return current_function;
}

std::any FinalizingFunctionVisitor::visitFunctionDescription(CongParser::FunctionDescriptionContext* ctx)
{
    if (!ctx->literal()->STRING())
        throw std::runtime_error("Function description must be a string");

    if (current_function->has_description())
        throw std::runtime_error("Function description already set");

    current_function->set_description(utils::cleanup_string_literal(ctx->literal()->STRING()->getText()));

    return ctx->getText();
}

std::any FinalizingFunctionVisitor::visitFunctionGenericImpl(CongParser::FunctionGenericImplContext* ctx)
{
    ExpressionVisitor visitor(get_current_namespace(), current_function);

    if (const std::any result = visitor.visit(ctx->expression());
        result.has_value() && result.type() == typeid(Expression*))
    {
        auto expr = std::any_cast<Expression*>(result);
        current_function->add_generic_implementation(s_ptr<Expression>(expr));
        return expr;
    }

    throw std::runtime_error("Could not parse expression");
}

std::any FinalizingFunctionVisitor::visitFunctionExpRequires(CongParser::FunctionExpRequiresContext* ctx)
{
    ExpressionVisitor visitor(get_current_namespace(), current_function);

    if (const std::any result = visitor.visit(ctx->expression());
        result.has_value() && result.type() == typeid(Expression*))
    {
        auto expr = std::any_cast<Expression*>(result);
        current_function->add_requirement(s_ptr<Expression>(expr));
        return expr;
    }

    throw std::runtime_error("Could not parse expression");
}
