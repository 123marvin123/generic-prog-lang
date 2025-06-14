#include "sema/EvaluationContext.h"
#include "sema/Function.h"

// Static member variable definition
Concept::OperationTable Concept::operation_table;

s_ptr<Expression> EvaluationContext::bind_expression(s_ptr<Expression> expr,
        const std::unordered_map<const PlaceholderFunctionParameter*, const Concept*>& bindings)
{
    if (std::holds_alternative<const Concept*>(expr->get_result()))
        return expr;

    if (const auto& funcParam = utils::dyn_ptr_cast<FunctionParameterExpression>(expr))
    {
        if (const auto& result = funcParam->get_result();
            std::holds_alternative<const PlaceholderFunctionParameter*>(result))
        {
            if (const auto& placeholder = std::get<const PlaceholderFunctionParameter*>(result);
                bindings.contains(placeholder))
                return funcParam->bind(bindings.at(placeholder));
        }

        return expr;
    }

    if (const auto& call = utils::dyn_ptr_cast<CallExpression>(expr))
    {
        vec<s_ptr<Expression>> newArguments;
        newArguments.reserve(call->get_arguments().size());

        int idx = -1;
        bool changed = false;
        for (const auto param : call->get_function()->get_parameters())
        {
            if (++idx >= call->get_arguments().size())
                break;

            if (const auto& current_result = call->get_arguments()[idx]->get_result();
                std::holds_alternative<const Concept*>(current_result))
            {
                newArguments.push_back(call->get_arguments()[idx]);
                continue;
            }

            if (const auto& inner_call = utils::dyn_ptr_cast<CallExpression>(call->get_arguments()[idx]))
            {
                auto new_exp = bind_expression(inner_call, bindings);
                if (new_exp.get() != inner_call.get()) changed = true;
                newArguments.push_back(new_exp);
                continue;
            }

            if (const auto placeholder = utils::dyn_cast<PlaceholderFunctionParameter>(param); bindings.contains(placeholder))
            {
                changed = true;
                const auto paramExp = utils::dyn_ptr_cast<FunctionParameterExpression>(call->get_arguments()[idx]).get();
                newArguments.push_back(paramExp->bind(bindings.at(placeholder)));
            }
            else
            {
                auto new_exp = bind_expression(call->get_arguments()[idx], bindings);
                if (new_exp.get() != call->get_arguments()[idx].get()) changed = true;

                newArguments.push_back(bind_expression(call->get_arguments()[idx], bindings));
            }

        }

        if (changed)
            return std::make_shared<CallExpression>(call->get_sema(), call->get_function(), newArguments);
        return call;
    }

    if (const auto arithExp = utils::dyn_ptr_cast<ArithmeticExpression>(expr))
    {
        s_ptr<Expression> left = arithExp->get_left();
        s_ptr<Expression> right = arithExp->get_right();

        if (const auto newLeftExp = bind_expression(arithExp->get_left(), bindings);
            newLeftExp != arithExp->get_left())
            left = newLeftExp;

        if (const auto newRightExp = bind_expression(arithExp->get_right(), bindings);
            newRightExp != arithExp->get_right())
            right = newRightExp;

        if (left != arithExp->get_left() || right != arithExp->get_right())
            return ArithmeticExpression::create(arithExp->get_sema(), left, right, arithExp->get_op());

        return arithExp;
    }

    throw std::runtime_error("Unhandled case.");
}
