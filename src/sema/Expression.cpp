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

std::variant<const Concept *, const PlaceholderFunctionParameter *>
CallExpression::get_result() const {
  const auto &result = get_function()->get_result();
  if (std::holds_alternative<const Concept *>(result))
    return std::get<const Concept *>(result);

  const auto &target_param = std::get<PlaceholderFunctionParameter *>(result);

  int idx = 0;
  for (const auto &param : get_function()->get_parameters()) {
    if (const auto &v = get_arguments()[idx]->get_result();
        param == target_param && std::holds_alternative<const Concept *>(v))
      return std::get<const Concept *>(v);
    idx++;
  }

  return target_param;
}

std::set<const Function *> CallExpression::get_depending_functions() const {
    std::set<const Function*> depending_functions{};

    depending_functions.emplace(this->get_function());

    for (const s_ptr<Expression>& exp : this->get_arguments()) {
        if (auto call_exp = utils::dyn_ptr_cast<CallExpression>(exp)) {
            // Recursively call get_depending_functions and insert the result
            // into the depending_functions set
            auto nested_functions = call_exp->get_depending_functions();
            depending_functions.insert(nested_functions.begin(), nested_functions.end());
        }
    }

    return depending_functions;
}

std::string CallExpression::to_cpp() const noexcept
{
    vec<std::string> str_args{};
    str_args.reserve(args.size());
    for (const auto& arg : args)
        str_args.push_back(arg->to_cpp());

    std::string joined_args =
        std::accumulate(std::next(str_args.begin()), str_args.end(), str_args[0],
                        [](std::string a, const std::string& b) { return std::move(a) + ", " + b; });

    const Namespace* ns = get_function()->get_namespace();
    std::string prefix = ns->get_full_name() + (ns->is_global() ? "" : "::");
    std::string id = utils::sanitize_cpp_identifier(get_function()->get_identifier());

    return std::format("{}{}({})", prefix, id, joined_args);
}

std::string CallExpression::to_python() const noexcept
{
    vec<std::string> str_args{};
    str_args.reserve(args.size());
    for (const auto& arg : args)
        str_args.push_back(arg->to_python());

    std::string joined_args =
        std::accumulate(std::next(str_args.begin()), str_args.end(), str_args[0],
                        [](std::string a, const std::string& b) { return std::move(a) + ", " + b; });

    std::string id = utils::sanitize_python_identifier(get_function()->get_identifier());

    return std::format("{}({})", id, joined_args);
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

LetExpression::LetExpression(Sema *sema, const std::string &identifier, 
                             s_ptr<Expression> value, vec<s_ptr<Expression>> body)
    : Expression(sema), identifier(identifier), value(std::move(value)), body(std::move(body))
{
    if (!this->value)
        throw std::runtime_error("Let expression value must not be empty");
    if (this->body.empty())
        throw std::runtime_error("Let expression body must not be empty");
    if (identifier.empty())
        throw std::runtime_error("Let expression identifier must not be empty");
}

std::variant<const Concept *, const PlaceholderFunctionParameter *>
LetExpression::get_result() const {
    if (!body.empty()) {
        return body.back()->get_result();
    }
    throw std::runtime_error("Let expression body is empty");
}

std::string LetExpression::to_cpp() const noexcept {
    std::ostringstream oss;
    oss << "[&]() {\n";
    oss << "    auto " << utils::sanitize_cpp_identifier(identifier) << " = " << value->to_cpp() << ";\n";
    
    // All expressions except the last are statements
    for (size_t i = 0; i < body.size() - 1; ++i) {
        oss << "    " << body[i]->to_cpp() << ";\n";
    }
    
    // The last expression is the return value
    if (!body.empty()) {
        oss << "    return " << body.back()->to_cpp() << ";\n";
    }
    
    oss << "}()";
    return oss.str();
}

std::string LetExpression::to_python() const noexcept {
    std::ostringstream oss;
    oss << "(lambda: (\n";
    oss << "    setattr(locals(), '" << identifier << "', " << value->to_python() << "),\n";
    
    // All expressions except the last
    for (size_t i = 0; i < body.size() - 1; ++i) {
        oss << "    " << body[i]->to_python() << ",\n";
    }
    
    // The last expression is the return value
    if (!body.empty()) {
        oss << "    " << body.back()->to_python() << "\n";
    }
    
    oss << ")[-1])()";
    return oss.str();
}

LetVariableReferenceExpression::LetVariableReferenceExpression(Sema *sema, const std::string &identifier, s_ptr<Expression> bound_value)
    : Expression(sema), identifier(identifier), bound_value(std::move(bound_value))
{
    if (identifier.empty())
        throw std::runtime_error("Let variable reference identifier must not be empty");
    if (!this->bound_value)
        throw std::runtime_error("Let variable reference bound value must not be empty");
}

std::variant<const Concept *, const PlaceholderFunctionParameter *>
LetVariableReferenceExpression::get_result() const {
    // The result of a let variable reference is the result of the bound expression
    return bound_value->get_result();
}

std::string LetVariableReferenceExpression::to_cpp() const noexcept {
    // In C++, we just use the identifier name since the variable is bound in the lambda scope
    return utils::sanitize_cpp_identifier(identifier);
}

std::string LetVariableReferenceExpression::to_python() const noexcept {
    // In Python, we just use the identifier name since it's in the local scope
    return identifier;
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
    else if (const auto& cast = utils::dyn_cast<Introspection<LetExpression>>(&e))
        ss << cast->to_string(tabsize);
    else if (const auto& cast = utils::dyn_cast<Introspection<LetVariableReferenceExpression>>(&e))
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

void LetExpression::DebugVisitor::visitExpression(const Expression& e)
{
    const auto& let_expr = dynamic_cast<const LetExpression&>(e);
    
    ss << spaces() << termcolor::green << "let " << termcolor::reset 
       << termcolor::blue << let_expr.get_identifier() << termcolor::reset 
       << " = ";
    
    // Show the value expression
    ss << let_expr.get_value()->to_string(0) << " " << termcolor::green << "{" << termcolor::reset << "\n";
    
    tabsize += 2;
    
    // Show body expressions
    for (size_t i = 0; i < let_expr.get_body().size(); ++i) {
        ss << let_expr.get_body()[i]->to_string(tabsize);
        if (i < let_expr.get_body().size() - 1) {
            ss << ";";
        }
        ss << "\n";
    }
    
    tabsize -= 2;
    ss << spaces() << termcolor::green << "}" << termcolor::reset;
}

void LetVariableReferenceExpression::DebugVisitor::visitExpression(const Expression& e)
{
    const auto& let_var_ref = dynamic_cast<const LetVariableReferenceExpression&>(e);
    
    ss << spaces() << termcolor::cyan << "let_var(" << termcolor::reset 
       << termcolor::blue << let_var_ref.get_identifier() << termcolor::reset 
       << termcolor::cyan << ")" << termcolor::reset;
}