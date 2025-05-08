//
// Created by Marvin Haschker on 14.03.25.
//
#include "visitor/FinalizingFunctionVisitor.h"

enum class GenericImplQualityType
{
    Space,
    Time
};

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
        GenericImplementation impl{s_ptr<Expression>(expr)};

        using DetailType = std::map<GenericImplQualityType, s_ptr<Expression>>;
        if (const std::any detailResult = visit(ctx->genericImplDetails());
            detailResult.has_value() && detailResult.type() == typeid(DetailType))
        {
            auto details = std::any_cast<DetailType>(detailResult);

            for (auto& [quality, exprPtr] : details)
            {
                if (quality == GenericImplQualityType::Space)
                    impl.set_space_complexity(exprPtr);
                else if (quality == GenericImplQualityType::Time)
                    impl.set_time_complexity(exprPtr);
            }
        }

        current_function->add_generic_implementation(impl);
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
        const opt<std::string> name = ctx->name ? ctx->name->getText() : "";

        current_function->add_requirement(s_ptr<Expression>(expr), name);
        return expr;
    }

    throw std::runtime_error("Could not parse expression");
}

std::any FinalizingFunctionVisitor::visitGenericImplDetails(CongParser::GenericImplDetailsContext* ctx)
{
    std::map<GenericImplQualityType, s_ptr<Expression>> impl_details{};
    
    for (const auto& a : ctx->genericImplDetail())
    {
        if (const std::any result = visit(a);
            result.has_value() && result.type() == typeid(std::pair<GenericImplQualityType, Expression*>))
        {
            const auto& pair = std::any_cast<std::pair<GenericImplQualityType, Expression*>>(result);
            impl_details[pair.first] = s_ptr<Expression>(pair.second);
        }
        else
            throw std::runtime_error("Could not parse generic implementation details");
    }

    return impl_details;
}
std::any FinalizingFunctionVisitor::visitGenericImplDetail(CongParser::GenericImplDetailContext* ctx)
{
    ExpressionVisitor visitor(get_current_namespace(), current_function);

    if (const std::any result = visitor.visit(ctx->expression());
        result.has_value() && result.type() == typeid(Expression*))
    {
        GenericImplQualityType quality = ctx->SPACE() ? GenericImplQualityType::Space : GenericImplQualityType::Time;
        return std::make_pair(quality, std::any_cast<Expression*>(result));
    }

    throw std::runtime_error("Could not parse expression");
}

