//
// Created by Marvin Haschker on 13.03.25.
//

#ifndef EXPRESSIONVISITOR_H
#define EXPRESSIONVISITOR_H

#include "AbstractVisitor.h"
#include "sema/Expression.h"
#include "sema/Namespace.h"
#include "CongBaseVisitor.h"
#include "Utils.h"

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

private:
    Namespace* ns;
    Function* fun;
};

#endif //EXPRESSIONVISITOR_H
