//
// Created by Marvin Haschker on 13.03.25.
//

#ifndef EXPRESSIONVISITOR_H
#define EXPRESSIONVISITOR_H

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

    std::any visitParameterReferenceExpression(CongParser::ParameterReferenceExpressionContext* ctx) override;

    std::any visitCallExpression(CongParser::CallExpressionContext* ctx) override;

    std::any visitArithmeticExpression(CongParser::ArithmeticExpressionContext* ctx) override;

    std::any visitLetExpression(CongParser::LetExpressionContext* ctx) override;

    std::any visitOpenBindingExpression(CongParser::OpenBindingExpressionContext *context) override;

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

#endif //EXPRESSIONVISITOR_H
