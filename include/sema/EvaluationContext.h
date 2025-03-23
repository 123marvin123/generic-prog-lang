//
// Created by Marvin Haschker on 14.03.25.
//

#ifndef EVALUATIONCONTEXT_H
#define EVALUATIONCONTEXT_H

#include "Utils.h"
#include "Expression.h"

struct EvaluationContext
{
    EvaluationContext() = delete;

    [[nodiscard]]
    static s_ptr<Expression> bind_expression(s_ptr<Expression> expr,
        const std::unordered_map<const PlaceholderFunctionParameter*, const Concept*>&);
};

#endif //EVALUATIONCONTEXT_H
