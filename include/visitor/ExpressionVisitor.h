#pragma once

#include "AbstractVisitor.h"
#include "sema/Expression.h"
#include "sema/Namespace.h"

// Structure to represent a let binding for scope checking
struct LetBinding {
    std::string identifier;
    s_ptr<Expression> value;
    
    LetBinding(std::string id, s_ptr<Expression> val) 
        : identifier(std::move(id)), value(std::move(val)) {}
};

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

private:
    Namespace* ns;
    Function* fun;
    std::stack<std::vector<LetBinding>> let_binding_stack;
    
    // Check for name collisions with existing symbols
    void checkNameCollision(const std::string& identifier, antlr4::ParserRuleContext* ctx = nullptr) const;
    
    // Find a let binding in the current scope stack
    [[nodiscard]]
    opt<LetBinding> findLetBinding(const std::string& identifier) const;
};
