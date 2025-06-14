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
        throw SemaError(std::format("Could not find function {}", fnName), ctx);

    current_function = fn.value();

    visitChildren(ctx);

    return current_function;
}

std::any FinalizingFunctionVisitor::visitFunctionDescription(CongParser::FunctionDescriptionContext* ctx)
{
    if (!ctx->literal()->STRING())
        throw SemaError("Function description must be a string", ctx);

    if (current_function->has_description())
        throw SemaError("Function description already set", ctx);

    current_function->set_description(utils::cleanup_string_literal(ctx->literal()->STRING()->getText()));

    return ctx->getText();
}

std::any FinalizingFunctionVisitor::visitFunctionExpRequires(CongParser::FunctionExpRequiresContext* ctx)
{
    ExpressionVisitor visitor(get_current_namespace(), current_function);

    if (const std::any result = visitor.visit(ctx->expression());
        result.has_value() && result.type() == typeid(Expression*))
    {
        auto expr = std::any_cast<Expression*>(result);
        const opt<std::string> name = ctx->name ? opt<std::string>{ctx->name->getText()} : std::nullopt;

        current_function->add_requirement(s_ptr<Expression>(expr), name);
        return expr;
    }

    throw SemaError("Could not parse expression", ctx);
}

std::any FinalizingFunctionVisitor::visitGenericImplDetails(CongParser::GenericImplDetailsContext* ctx)
{
    std::map<GenericImplQualityType, s_ptr<Expression>> impl_details{};
    std::string target_lang;

    for (const auto& a : ctx->genericImplDetail())
    {
        if (const std::any result = visit(a);
            result.has_value() && result.type() == typeid(std::pair<GenericImplQualityType, Expression*>))
        {
            const auto& pair = std::any_cast<std::pair<GenericImplQualityType, Expression*>>(result);
            impl_details[pair.first] = s_ptr<Expression>(pair.second);
        }
        else if (result.type() == typeid(std::string) && a->LANG() != nullptr)
        {
            if (!target_lang.empty())
                throw SemaError(std::format("Target language already set to {} for generic implementation; cannot set it to {}", target_lang, std::any_cast<std::string>(result)), a);
            target_lang = std::any_cast<std::string>(result);
        }
        else
            throw SemaError("Could not parse generic implementation details", ctx);
    }

    return std::make_tuple(impl_details, target_lang);
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
    if (ctx->targetLang)
    {
        return ctx->targetLang->getText();
    }

    throw SemaError("Could not parse expression", ctx);
}
std::any FinalizingFunctionVisitor::visitFunctionGenericImpl(CongParser::FunctionGenericImplContext* ctx)
{
    GenericImplementation impl{nullptr};

    using DetailType = std::tuple<std::map<GenericImplQualityType, s_ptr<Expression>>, std::string>;
    if (const std::any detailResult = visit(ctx->genericImplDetails());
        detailResult.has_value() && detailResult.type() == typeid(DetailType))
    {
        auto details = std::any_cast<DetailType>(detailResult);

        for (auto& [quality, exprPtr] : std::get<0>(details))
        {
            if (quality == GenericImplQualityType::Space)
                impl.set_space_complexity(exprPtr);
            else if (quality == GenericImplQualityType::Time)
                impl.set_time_complexity(exprPtr);
        }

        impl.set_language(utils::cleanup_string_literal(std::get<1>(details)));
    }

    bool isNative = ctx->g->hasLangArg;
    if (isNative)
    {
        antlr4::Token* startToken = ctx->body_native->getStart();
        antlr4::Token* stopToken = ctx->body_native->getStop();
        std::string originalText;

        if (startToken && stopToken)
        {
            if (antlr4::CharStream* inputStream = startToken->getInputStream())
            {
                antlr4::misc::Interval interval(startToken->getStartIndex(), stopToken->getStopIndex());
                originalText = inputStream->getText(interval);
            }
            else
            {
                throw SemaError("Could not parse start token", ctx->body_native);
            }
        }
        else
        {
            // empty
            originalText = "";
        }

        impl.set_native_implementation(originalText);
        current_function->add_generic_implementation(impl);
        return originalText;
    }

    ExpressionVisitor visitor(get_current_namespace(), current_function);

    if (const std::any result = visitor.visit(ctx->body_expr);
        result.has_value() && result.type() == typeid(Expression*))
    {
        auto expr = std::any_cast<Expression*>(result);
        impl.set_expression(s_ptr<Expression>(expr));

        try
        {
            current_function->add_generic_implementation(impl);
        }
        catch (const SemaError& e)
        {
            throw SemaError(e.what(), ctx);
        }

        return expr;
    }

    throw SemaError("Could not parse expression", ctx);
}


