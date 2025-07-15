#pragma once

#include "AbstractVisitor.h"
#include "sema/Expression.h"
#include "sema/Namespace.h"
#include "Decls.h"

struct ExpressionVisitor final : AbstractVisitor
{
    explicit ExpressionVisitor(Namespace* ns, Function* fun = nullptr) :
        AbstractVisitor(ns->get_sema(), false), ns(ns), fun(fun)
    {
    }

    std::any visitLiteralExpression(CongParser::LiteralExpressionContext* ctx) override;

    std::any visitParameterOrConceptReferenceExpression(CongParser::ParameterOrConceptReferenceExpressionContext* ctx)
    override;

    std::any visitCallExpression(CongParser::CallExpressionContext* ctx) override;

    std::any visitArithmeticExpression(CongParser::ArithmeticExpressionContext* ctx) override;

    std::any visitLetExpression(CongParser::LetExpressionContext* ctx) override;

    std::any visitOpenBindingExpression(CongParser::OpenBindingExpressionContext *context) override;

    std::any visitQuoteExpression(CongParser::QuoteExpressionContext *context) override;

    std::any visitEvalExpression(CongParser::EvalExpressionContext* context) override;

    std::any visitRequiresCallExpression(CongParser::RequiresCallExpressionContext* ctx) override;

    std::any visitConditionalExpression(CongParser::ConditionalExpressionContext* ctx) override;

    std::any visitParenthesizedExpression(CongParser::ParenthesizedExpressionContext* ctx) override;

    std::any visitComparisonExpression(CongParser::ComparisonExpressionContext* ctx) override;

    std::any visitLetBinding(CongParser::LetBindingContext* ctx) override;

    std::any visitLambdaExpression(CongParser::LambdaExpressionContext* ctx) override;

    std::any visitParameterList(CongParser::ParameterListContext* ctx) override;
    std::any visitParameter(CongParser::ParameterContext* ctx) override;
    std::any visitPlaceholderOrQualifiedId(CongParser::PlaceholderOrQualifiedIdContext* ctx) override;
    std::any visitPlaceholder(CongParser::PlaceholderContext* ctx) override;
    std::any visitQualifiedIdentifier(CongParser::QualifiedIdentifierContext* ctx) override;


private:
    Namespace* ns;
    Function* fun;
    std::stack<std::vector<LetBinding>> let_binding_stack;
    std::stack<LambdaExpression*> lambda_exp_stack;

    // Check for name collisions with existing symbols
    void checkNameCollision(const std::string& identifier, antlr4::ParserRuleContext* ctx = nullptr) const;
    
    // Find a let binding in the current scope stack
    [[nodiscard]]
    opt<LetBinding> findLetBinding(const std::string& identifier) const;

    [[nodiscard]]
    opt<std::pair<LambdaExpression*, std::size_t>>
    findLambdaParam(const std::string &string) const;
};
