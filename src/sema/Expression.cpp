//
// Created by Marvin Haschker on 12.03.25.
//

#include "sema/Expression.h"
#include <Utils.h>
#include "sema/Sema.h"

StringExpression::StringExpression(Sema* sema, const std::string& value) :
    ConstantExpression(sema, sema->builtin_concept<std::string>(), value)
{
}

RealExpression::RealExpression(Sema* sema, const double value) :
    ConstantExpression(sema, sema->builtin_concept<double>(), value)
{
}

NumberExpression::NumberExpression(Sema* sema, const long value) :
    ConstantExpression(sema, sema->builtin_concept<long>(), value)
{
}

BooleanExpression::BooleanExpression(Sema* sema, const bool value) :
    ConstantExpression(sema, sema->builtin_concept<bool>(), value)
{
}

std::variant<const Concept*, const PlaceholderFunctionParameter*> FunctionParameterExpression::get_result() const
{
    const auto param = get_param();
    if (const auto cast = utils::dyn_cast<ConcreteFunctionParameter>(param))
        return cast->get_type();
    if (const auto cast = utils::dyn_cast<DependentFunctionParameter>(param))
        return cast->get_placeholder();
    if (const auto cast = utils::dyn_cast<PlaceholderFunctionParameter>(param))
        return cast;

    throw std::runtime_error("Unhandled case");
}

s_ptr<BoundFunctionParameterExpression> FunctionParameterExpression::bind(const Concept* c) const
{
    return s_ptr<BoundFunctionParameterExpression>(new BoundFunctionParameterExpression(get_sema(), this, c));
}

CallExpression::CallExpression(Sema* sema, const Function* fun,
                               vec<s_ptr<Expression>> args) :
    Expression(sema), fun(fun), args(std::move(args))
{
    if (!fun)
        throw std::runtime_error("Function must not be empty");
    if (get_arguments().size() < fun->get_parameters().size())
        throw std::runtime_error(
            std::format("Function {} expects {} arguments but {} were provided",
                        fun->get_identifier(), fun->get_parameters().size(), get_arguments().size())
            );

    auto exp_it = get_arguments().begin();
    auto fun_params = fun->get_parameters();
    auto fun_it = fun_params.begin();
    int idx = 0;
    for (; exp_it != get_arguments().end(); ++fun_it, ++exp_it, ++idx)
    {
        if (const auto& v = (*exp_it)->get_result();
            std::holds_alternative<const Concept*>(v))
        {
            if (const auto concrete_param = utils::dyn_cast<ConcreteFunctionParameter>(*fun_it))
            {
                if (!concrete_param->get_type()->matches_concept(std::get<const Concept*>(v)))
                    throw std::runtime_error(std::format("Argument #{} does not match parameter concept {}",
                                                     idx, concrete_param->get_identifier()));
            }
        }
    }
}

std::variant<const Concept*, const PlaceholderFunctionParameter*> CallExpression::get_result() const
{
    const auto& result = get_function()->get_result();
    if (std::holds_alternative<const Concept*>(result))
        return std::get<const Concept*>(result);

    const auto& target_param = std::get<PlaceholderFunctionParameter*>(result);

    int idx = 0;
    for (const auto& param : get_function()->get_parameters())
    {
        if (const auto& v = get_arguments()[idx]->get_result();
            param == target_param && std::holds_alternative<const Concept*>(v))
            return std::get<const Concept*>(v);
        idx++;
    }

    return target_param;
}

ArithmeticExpression::ArithmeticExpression(Sema* sema, s_ptr<Expression> left, s_ptr<Expression> right, const Operator op):
    Expression(sema), left(std::move(left)), right(std::move(right)), op(op)
{
    if (std::holds_alternative<const Concept*>(get_left()->get_result()) &&
        std::holds_alternative<const Concept*>(get_right()->get_result()))
    {
        const auto left_concept = std::get<const Concept*>(get_left()->get_result());
        const auto right_concept = std::get<const Concept*>(get_right()->get_result());

        if (auto res = left_concept->get_operation_result(get_op(), right_concept); !res.is_valid)
            throw std::runtime_error("Incompatible types for arithmetic operation");
    }
}

std::variant<const Concept*, const PlaceholderFunctionParameter*> ArithmeticExpression::get_result() const
{
    auto left_result = left->get_result();
    auto right_result = right->get_result();

    if (std::holds_alternative<const Concept*>(left_result) && std::holds_alternative<const Concept*>(right_result))
    {
        const auto& left_concept = std::get<const Concept*>(left_result);
        const auto& right_concept = std::get<const Concept*>(right_result);

        if (const auto& [result_concept, is_valid] = left_concept->get_operation_result(op, right_concept);
            is_valid)
            return result_concept;
    }

    if (std::holds_alternative<const PlaceholderFunctionParameter*>(left_result))
        return left_result;

    return right_result;
}

void Expression::DebugVisitor::visitExpression(const Expression& e)
{
    if (const auto& cast = utils::dyn_cast<Introspection<BaseConstantExpression>>(&e))
        ss << cast->to_string(tabsize);
    else if (const auto& cast = utils::dyn_cast<Introspection<FunctionParameterExpression>>(&e))
        ss << cast->to_string(tabsize);
    else if (const auto& cast = utils::dyn_cast<Introspection<CallExpression>>(&e))
        ss << cast->to_string(tabsize);
    else if (const auto& cast = utils::dyn_cast<Introspection<BoundFunctionParameterExpression>>(&e))
        ss << cast->to_string(tabsize);
    else if (const auto& cast = utils::dyn_cast<Introspection<ArithmeticExpression>>(&e))
        ss << cast->to_string(tabsize);
    else
        throw std::runtime_error("Expression type not handled.");
}

void FunctionParameterExpression::DebugVisitor::visitExpression(const Expression& e)
{
    const auto& param = dynamic_cast<const FunctionParameterExpression&>(e);
    ss << spaces() << termcolor::blue << param.param->get_identifier() << termcolor::reset;
}

void BoundFunctionParameterExpression::DebugVisitor::visitExpression(const Expression& e)
{
    const auto& param = dynamic_cast<const BoundFunctionParameterExpression&>(e);

    ss << spaces() << termcolor::blue << param.get_param()->get_identifier() << termcolor::reset << " -> "
        << termcolor::yellow << param.get_concept()->get_identifier() << termcolor::reset;
}

void CallExpression::DebugVisitor::visitExpression(const Expression& e)
{
    const auto& param = dynamic_cast<const CallExpression&>(e);
    ss << spaces() << termcolor::blue << param.fun->get_identifier() << termcolor::reset << "(";

    tabsize += 2;
    const unsigned long length = std::string(tabsize, ' ').length();
    bool breakNext = false;
    for (auto it = param.args.begin(); it != param.args.end(); ++it)
    {
        std::string output = (*it)->to_string(tabsize);

        if (output.length() - length < 20)
        {
            output.erase(0, length);
            breakNext = false;
        }
        else
        {
            ss << "\n";
            breakNext = true;
        }

        ss << output << termcolor::reset;
        if (it + 1 != param.args.end())
            ss << ",";
    }
    tabsize -= 2;

    if (breakNext)
        ss << "\n" << spaces();
    ss << ") -> ";
    if (const auto& res = e.get_result();
        std::holds_alternative<const Concept*>(res))
        ss << termcolor::yellow << std::get<const Concept*>(res)->get_identifier() << termcolor::reset;
    else
        ss << termcolor::blue << std::get<const PlaceholderFunctionParameter*>(res)->get_type_placeholder_name() <<
            termcolor::reset;
}

void ArithmeticExpression::DebugVisitor::visitExpression(const Expression& e)
{
    const auto& param = dynamic_cast<const ArithmeticExpression&>(e);

    const Expression* left = param.get_left().get();
    const Expression* right = param.get_right().get();
    const std::string_view op_str = utils::get_string_for_operator(param.get_op());

    ss << spaces() << left->to_string() << " " << termcolor::blue << op_str << termcolor::reset << " " << right->to_string();
}