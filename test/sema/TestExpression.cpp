//
// Created by Marvin Haschker on 15.03.25.
//
#include <catch2/catch_test_macros.hpp>
#include <sema/EvaluationContext.h>

#include "../Common.h"

// Helper for showing operators in test output
std::string toString(const Operator& op) {
    return std::string(utils::get_string_for_operator(op));
}

struct ExpressionFixture {
    std::unique_ptr<Sema> sema;
    Sema* sema_ptr;

    ExpressionFixture() {
        sema = std::make_unique<Sema>();
        sema_ptr = sema.get();
    }

    ~ExpressionFixture() {
        sema.reset();
    }
};

TEST_CASE_METHOD(ExpressionFixture, "Constant expression invalid construction", "[expression]")
{
    INFO(sema->to_string());
    REQUIRE_THROWS_AS(ConstantExpression<long>(sema_ptr, nullptr, 0, false), std::runtime_error);
}

TEST_CASE_METHOD(ExpressionFixture, "Constant expression evaluates to value", "[expression]")
{
    const auto c_str = sema->builtin_concept<std::string>();
    const std::string val = "hello";
    INFO(sema->to_string());

    const auto exp = ConstantExpression(sema_ptr, c_str, val, false);
    REQUIRE(val == exp.eval());
    REQUIRE(c_str == std::get<const Concept*>(exp.get_result()));
    REQUIRE(exp.is_constant());
}

TEST_CASE_METHOD(ExpressionFixture, "Function parameter expression concrete construction", "[expression]")
{
    const auto* object = sema->builtin_concept<Object>();
    const auto* f = *Sema::create_function<ConcreteFunction>(sema_ptr, "test", sema_ptr, object);
    const auto p = std::make_shared<ConcreteFunctionParameter>("param", object);
    p->set_function(f);
    INFO(sema->to_string());

    const FunctionParameterExpression exp(sema_ptr, p.get());
    REQUIRE_FALSE(exp.is_constant());
    REQUIRE(object == std::get<const Concept*>(exp.get_result()));
    REQUIRE(p.get() == exp.get_param());
}

TEST_CASE_METHOD(ExpressionFixture, "Function parameter expression placeholder construction", "[expression]")
{
    const auto* object = sema->builtin_concept<Object>();
    auto* f = *Sema::create_function<ConcreteFunction>(sema_ptr, "test", sema_ptr, object);
    const auto* p = f->register_function_parameter(std::make_unique<PlaceholderFunctionParameter>("param", "T"));
    INFO(sema->to_string());

    const FunctionParameterExpression exp(sema_ptr, p);
    REQUIRE_FALSE(exp.is_constant());
    REQUIRE(p == std::get<const PlaceholderFunctionParameter*>(exp.get_result()));
    REQUIRE(p == exp.get_param());
}

TEST_CASE_METHOD(ExpressionFixture, "Bound function parameter expression construction", "[expression]")
{
    const auto* object = sema->builtin_concept<Object>();
    auto* f = *Sema::create_function<ConcreteFunction>(sema_ptr, "test", sema_ptr, object);
    const auto* p = f->register_function_parameter(std::make_unique<PlaceholderFunctionParameter>("param", "T"));
    INFO(sema->to_string());

    const FunctionParameterExpression exp(sema_ptr, p);
    REQUIRE(p == std::get<const PlaceholderFunctionParameter*>(exp.get_result()));

    const auto bound_exp = exp.bind(object);
    INFO("Created bound expression");

    REQUIRE_FALSE(bound_exp->is_constant());
    REQUIRE(object == std::get<const Concept*>(bound_exp->get_result()));
    REQUIRE(object == bound_exp->get_concept());
    REQUIRE(p == bound_exp->get_param());
}

TEST_CASE_METHOD(ExpressionFixture, "Call expression with null function throws", "[expression]")
{
    INFO(sema->to_string());
    REQUIRE_THROWS_AS(CallExpression(sema_ptr, nullptr, {}), std::runtime_error);
}

TEST_CASE_METHOD(ExpressionFixture, "Call expression with invalid arguments throws", "[expression]")
{
    const auto* object = sema->builtin_concept<Object>();
    auto* f = *Sema::create_function<ConcreteFunction>(sema_ptr, "test", sema_ptr, object);

    f->register_function_parameter(std::make_unique<ConcreteFunctionParameter>("param", sema->builtin_concept<bool>()));
    f->register_function_parameter(std::make_unique<ConcreteFunctionParameter>("param2", sema->builtin_concept<Object>()));
    INFO(sema->to_string());

    REQUIRE_THROWS_AS(CallExpression(sema_ptr, f, {
        std::make_shared<IntegerExpression>(sema_ptr, 1, false),
        std::make_shared<BooleanExpression>(sema_ptr, false, false)
    }), std::runtime_error);

    REQUIRE_THROWS_AS(CallExpression(sema_ptr, f, {}), std::runtime_error);
}

TEST_CASE_METHOD(ExpressionFixture, "Call expression result on concrete function", "[expression]")
{
    auto c_bool = sema->builtin_concept<bool>();
    auto f = Sema::create_function<ConcreteFunction>(sema_ptr, "f", sema_ptr, c_bool);
    INFO(sema->to_string());

    const auto callExp = std::make_shared<CallExpression>(sema_ptr, *f, vec<s_ptr<Expression>>{});
    REQUIRE(c_bool == std::get<const Concept*>(callExp->get_result()));
}

TEST_CASE_METHOD(ExpressionFixture, "Call expression result on dependent function", "[expression]")
{
    auto f = *Sema::create_function<DependentFunction>(sema_ptr, "f", sema_ptr);
    auto p = f->register_function_parameter<PlaceholderFunctionParameter>("param", "T");
    f->set_dependency(p);
    INFO(sema->to_string());

    const auto some_arg = std::make_shared<StringExpression>(sema_ptr, "hello");
    const auto callExp = std::make_shared<CallExpression>(sema_ptr, f, vec<s_ptr<Expression>>{ some_arg });
    INFO("Created call expression with string argument");

    REQUIRE(sema->builtin_concept<std::string>() == std::get<const Concept*>(callExp->get_result()));
}

TEST_CASE_METHOD(ExpressionFixture, "Arithmetic expression construction", "[expression]")
{
    const auto num1 = IntegerExpression::create(sema_ptr, 5, false);
    const auto num2 = IntegerExpression::create(sema_ptr, 10, false);
    INFO(sema->to_string());

    const auto expr = ArithmeticExpression::create(sema_ptr, num1, num2, Operator::ADD);
    INFO("Created arithmetic expression with operator: " + toString(expr->get_op()));

    REQUIRE(num1.get() == expr->get_left().get());
    REQUIRE(num2.get() == expr->get_right().get());
    REQUIRE(Operator::ADD == expr->get_op());
}

TEST_CASE_METHOD(ExpressionFixture, "Arithmetic expression with incompatible types throws", "[expression]")
{
    const auto num = IntegerExpression::create(sema_ptr, 5, false);
    const auto str = StringExpression::create(sema_ptr, "hello");
    INFO(sema->to_string());

    REQUIRE_THROWS_AS(ArithmeticExpression(sema_ptr, num, str, Operator::ADD), std::runtime_error);
}

TEST_CASE_METHOD(ExpressionFixture, "Arithmetic expression result with same types", "[expression]")
{
    const auto num1 = IntegerExpression::create(sema_ptr, 5, false);
    const auto num2 = IntegerExpression::create(sema_ptr, 10, false);
    const auto number_concept = sema->builtin_concept<long>();
    INFO(sema->to_string());

    const ArithmeticExpression expr(sema_ptr, num1, num2, Operator::ADD);
    INFO("Created arithmetic expression with operator: " + toString(expr.get_op()));

    REQUIRE(std::holds_alternative<const Concept*>(expr.get_result()));
    REQUIRE(number_concept == std::get<const Concept*>(expr.get_result()));
}

TEST_CASE_METHOD(ExpressionFixture, "Arithmetic expression result with mixed types", "[expression]")
{
    const auto num = IntegerExpression::create(sema_ptr, 5, false);
    const auto real = RealExpression::create(sema_ptr, 3.14, false);
    const auto real_concept = sema->builtin_concept<double>();
    INFO(sema->to_string());

    const ArithmeticExpression expr(sema_ptr, num, real, Operator::MUL);
    INFO("Created arithmetic expression with operator: " + toString(expr.get_op()));

    REQUIRE(std::holds_alternative<const Concept*>(expr.get_result()));
    REQUIRE(real_concept == std::get<const Concept*>(expr.get_result()));
}

TEST_CASE_METHOD(ExpressionFixture, "Arithmetic expression with placeholder", "[expression]")
{
    auto* f = *Sema::create_function<DependentFunction>(sema_ptr, "test", sema_ptr);
    auto* p = f->register_function_parameter<PlaceholderFunctionParameter>("param", "T");
    f->set_dependency(p);
    INFO(sema->to_string());

    const auto num = IntegerExpression::create(sema_ptr, 5, false);
    const auto param_expr = FunctionParameterExpression::create(sema_ptr, p);

    const auto expr = ArithmeticExpression::create(sema_ptr, num, param_expr, Operator::ADD);
    INFO("Created arithmetic expression with placeholder");

    REQUIRE(std::holds_alternative<const PlaceholderFunctionParameter*>(expr->get_result()));
    REQUIRE(p == std::get<const PlaceholderFunctionParameter*>(expr->get_result()));

    const auto number = sema->builtin_concept<long>();
    const auto bound_expr = EvaluationContext::bind_expression(expr, { {p, number} });
    INFO("Bound expression with Number concept");

    REQUIRE(std::holds_alternative<const Concept*>(bound_expr->get_result()));
    REQUIRE(number == std::get<const Concept*>(bound_expr->get_result()));
}

TEST_CASE_METHOD(ExpressionFixture, "Arithmetic expression with bound parameter", "[expression]")
{
    auto* f = *Sema::create_function<DependentFunction>(sema_ptr, "test", sema_ptr);
    auto* p = f->register_function_parameter<PlaceholderFunctionParameter>("param", "T");
    f->set_dependency(p);
    INFO(sema->to_string());

    const auto number_concept = sema->builtin_concept<long>();

    const auto param_expr = FunctionParameterExpression::create(sema_ptr, p);
    const auto bound_expr = param_expr->bind(number_concept);
    const auto num = IntegerExpression::create(sema_ptr, 5, false);
    INFO("Created bound parameter expression");

    const auto expr = ArithmeticExpression::create(sema_ptr, num, bound_expr, Operator::ADD);
    INFO("Created arithmetic expression with bound parameter");

    REQUIRE(std::holds_alternative<const Concept*>(expr->get_result()));
    REQUIRE(number_concept == std::get<const Concept*>(expr->get_result()));
}

TEST_CASE_METHOD(ExpressionFixture, "Arithmetic expression with different operators", "[expression]")
{
    const auto num1 = IntegerExpression::create(sema_ptr, 5, false);
    const auto num2 = IntegerExpression::create(sema_ptr, 10, false);
    const auto number_concept = sema->builtin_concept<long>();
    INFO(sema->to_string());

    const auto add = ArithmeticExpression::create(sema_ptr, num1, num2, Operator::ADD);
    const auto subtract = ArithmeticExpression::create(sema_ptr, num1, num2, Operator::SUB);
    const auto multiply = ArithmeticExpression::create(sema_ptr, num1, num2, Operator::MUL);
    const auto divide = ArithmeticExpression::create(sema_ptr, num1, num2, Operator::DIV);
    INFO("Created arithmetic expressions with different operators");

    REQUIRE(number_concept == std::get<const Concept*>(add->get_result()));
    REQUIRE(number_concept == std::get<const Concept*>(subtract->get_result()));
    REQUIRE(number_concept == std::get<const Concept*>(multiply->get_result()));
    REQUIRE(number_concept == std::get<const Concept*>(divide->get_result()));
}

TEST_CASE_METHOD(ExpressionFixture, "LetExpression basic functionality", "[expression][let]")
{
    INFO(sema->to_string());

    auto value_expr = std::make_shared<IntegerExpression>(sema_ptr, 42, false);

    vec<s_ptr<Expression>> body_exprs;
    body_exprs.push_back(std::make_shared<IntegerExpression>(sema_ptr, 100, false));
    
    vec<LetBinding> bindings;
    bindings.emplace_back("x", value_expr);

    const auto let_expr = LetExpression::create(sema_ptr, bindings, body_exprs);

    REQUIRE(let_expr->get_bindings().size() == 1);
    REQUIRE(let_expr->get_bindings()[0].identifier == "x");
    REQUIRE(let_expr->get_bindings()[0].value == value_expr);
    REQUIRE(let_expr->get_body() == body_exprs);
    
    const auto result = let_expr->get_result();

    REQUIRE(std::holds_alternative<const Concept*>(result));
}

TEST_CASE_METHOD(ExpressionFixture, "LetExpression with multiple body expressions", "[expression][let]")
{
    INFO(sema->to_string());
    
    const auto value_expr = std::make_shared<IntegerExpression>(sema_ptr, 42, false);
    
    vec<s_ptr<Expression>> body_exprs;
    body_exprs.push_back(std::make_shared<IntegerExpression>(sema_ptr, 10, false));
    body_exprs.push_back(std::make_shared<IntegerExpression>(sema_ptr, 20, false));
    body_exprs.push_back(std::make_shared<IntegerExpression>(sema_ptr, 30, false));
    
    vec<LetBinding> bindings;
    bindings.emplace_back("x", value_expr);

    const auto let_expr = LetExpression::create(sema_ptr, bindings, body_exprs);

    const auto result = let_expr->get_result();
    REQUIRE(std::holds_alternative<const Concept*>(result));
}

TEST_CASE_METHOD(ExpressionFixture, "LetExpression C++ export", "[expression][let][export]")
{
    INFO(sema->to_string());
    
    auto value_expr = std::make_shared<IntegerExpression>(sema_ptr, 42, false);
    vec<s_ptr<Expression>> body_exprs;
    body_exprs.push_back(std::make_shared<IntegerExpression>(sema_ptr, 100, false));
    
    vec<LetBinding> bindings;
    bindings.emplace_back("x", value_expr);

    auto let_expr = LetExpression::create(sema_ptr, bindings, body_exprs);

    std::string cpp_output = let_expr->to_cpp();

    REQUIRE(cpp_output.find("[&]() {") != std::string::npos);
    REQUIRE(cpp_output.find("auto x = ::cong::lang::NaturalStatic<42>{};") != std::string::npos);
    REQUIRE(cpp_output.find("return ::cong::lang::NaturalStatic<100>{};") != std::string::npos);
    REQUIRE(cpp_output.find("}()") != std::string::npos);
}

TEST_CASE_METHOD(ExpressionFixture, "LetExpression Python export", "[expression][let][export]")
{
    INFO(sema->to_string());
    
    const auto value_expr = std::make_shared<IntegerExpression>(sema_ptr, 42, false);
    vec<s_ptr<Expression>> body_exprs;
    body_exprs.push_back(std::make_shared<IntegerExpression>(sema_ptr, 100, false));
    
    vec<LetBinding> bindings;
    bindings.emplace_back("x", value_expr);

    const auto let_expr = LetExpression::create(sema_ptr, bindings, body_exprs);

    std::string python_output = let_expr->to_python();

    REQUIRE(python_output.find("(lambda x: (") != std::string::npos);
    REQUIRE(python_output.find("Number(100)") != std::string::npos);
    REQUIRE(python_output.find(")[-1])(") != std::string::npos);
    REQUIRE(python_output.find("Number(42)") != std::string::npos);
}

TEST_CASE_METHOD(ExpressionFixture, "LetExpression invalid construction", "[expression][let]")
{
    INFO(sema->to_string());
    
    const auto value_expr = std::make_shared<IntegerExpression>(sema_ptr, 42, false);
    
    vec<s_ptr<Expression>> empty_body;
    vec<LetBinding> bindings;
    bindings.emplace_back("x", value_expr);
    REQUIRE_THROWS_AS(LetExpression(sema_ptr, bindings, empty_body), std::runtime_error);

    vec<s_ptr<Expression>> body_exprs;
    body_exprs.push_back(std::make_shared<IntegerExpression>(sema_ptr, 100, false));

    vec<LetBinding> empty_identifier_bindings;
    empty_identifier_bindings.emplace_back("", value_expr);
    REQUIRE_THROWS_AS(LetExpression(sema_ptr, empty_identifier_bindings, body_exprs), std::runtime_error);

    vec<LetBinding> null_bindings;
    null_bindings.emplace_back("x", nullptr);
    REQUIRE_THROWS_AS(LetExpression(sema_ptr, null_bindings, body_exprs), std::runtime_error);
}

// String Expression Tests
TEST_CASE_METHOD(ExpressionFixture, "StringExpression basic functionality", "[expression][string]")
{
    INFO(sema->to_string());

    const std::string test_value = "hello world";
    const auto string_expr = StringExpression::create(sema_ptr, test_value);

    REQUIRE(string_expr->eval() == test_value);
    REQUIRE(string_expr->is_constant());
    REQUIRE(sema->builtin_concept<std::string>() == std::get<const Concept*>(string_expr->get_result()));
}

TEST_CASE_METHOD(ExpressionFixture, "StringExpression export functionality", "[expression][string][export]")
{
    INFO(sema->to_string());

    const std::string test_value = "test";
    const auto string_expr = StringExpression::create(sema_ptr, test_value);

    std::string cpp_output = string_expr->to_cpp();
    std::string python_output = string_expr->to_python();

    REQUIRE(cpp_output == test_value);
    REQUIRE(python_output == test_value);
}

// Real Expression Tests
TEST_CASE_METHOD(ExpressionFixture, "RealExpression basic functionality", "[expression][real]")
{
    INFO(sema->to_string());

    const double test_value = 3.14159;
    const auto real_expr = RealExpression::create(sema_ptr, test_value, false);

    REQUIRE(real_expr->eval() == test_value);
    REQUIRE(real_expr->is_constant());
    REQUIRE_FALSE(real_expr->is_dynamic());
    REQUIRE(sema->builtin_concept<double>() == std::get<const Concept*>(real_expr->get_result()));
}

TEST_CASE_METHOD(ExpressionFixture, "RealExpression dynamic vs static", "[expression][real]")
{
    INFO(sema->to_string());

    const double test_value = 2.718;
    const auto static_expr = RealExpression::create(sema_ptr, test_value, false);
    const auto dynamic_expr = RealExpression::create(sema_ptr, test_value, true);

    REQUIRE_FALSE(static_expr->is_dynamic());
    REQUIRE(dynamic_expr->is_dynamic());
    REQUIRE(static_expr->eval() == dynamic_expr->eval());
}

TEST_CASE_METHOD(ExpressionFixture, "RealExpression export functionality", "[expression][real][export]")
{
    INFO(sema->to_string());

    const double test_value = 1.5;
    const auto static_expr = RealExpression::create(sema_ptr, test_value, false);
    const auto dynamic_expr = RealExpression::create(sema_ptr, test_value, true);

    std::string static_cpp = static_expr->to_cpp();
    std::string dynamic_cpp = dynamic_expr->to_cpp();
    std::string python_output = static_expr->to_python();

    REQUIRE(static_cpp.find("::cong::lang::RealStatic<1.5>{}") != std::string::npos);
    REQUIRE(dynamic_cpp.find("::cong::lang::RealDynamic{1.5}") != std::string::npos);
    REQUIRE(python_output == "Real(1.5)");
}

// Integer Expression Tests
TEST_CASE_METHOD(ExpressionFixture, "IntegerExpression basic functionality", "[expression][integer]")
{
    INFO(sema->to_string());

    const long test_value = 42;
    const auto int_expr = IntegerExpression::create(sema_ptr, test_value, false);

    REQUIRE(int_expr->eval() == test_value);
    REQUIRE(int_expr->is_constant());
    REQUIRE_FALSE(int_expr->is_dynamic());
    REQUIRE(sema->builtin_concept<long>() == std::get<const Concept*>(int_expr->get_result()));
}

TEST_CASE_METHOD(ExpressionFixture, "IntegerExpression positive and negative values", "[expression][integer]")
{
    INFO(sema->to_string());

    const auto positive_expr = IntegerExpression::create(sema_ptr, 100, false);
    const auto negative_expr = IntegerExpression::create(sema_ptr, -50, false);
    const auto zero_expr = IntegerExpression::create(sema_ptr, 0, false);

    REQUIRE(positive_expr->eval() == 100);
    REQUIRE(negative_expr->eval() == -50);
    REQUIRE(zero_expr->eval() == 0);
}

TEST_CASE_METHOD(ExpressionFixture, "IntegerExpression export functionality", "[expression][integer][export]")
{
    INFO(sema->to_string());

    const auto positive_static = IntegerExpression::create(sema_ptr, 42, false);
    const auto positive_dynamic = IntegerExpression::create(sema_ptr, 42, true);
    const auto negative_static = IntegerExpression::create(sema_ptr, -10, false);
    const auto negative_dynamic = IntegerExpression::create(sema_ptr, -10, true);

    REQUIRE(positive_static->to_cpp().find("::cong::lang::NaturalStatic<42>{}") != std::string::npos);
    REQUIRE(positive_dynamic->to_cpp().find("::cong::lang::NaturalDynamic{42ul}") != std::string::npos);
    REQUIRE(negative_static->to_cpp().find("::cong::lang::IntegerStatic<-10>{}") != std::string::npos);
    REQUIRE(negative_dynamic->to_cpp().find("::cong::lang::IntegerDynamic{-10l}") != std::string::npos);

    REQUIRE(positive_static->to_python() == "Number(42)");
    REQUIRE(negative_static->to_python() == "Number(-10)");
}

// Boolean Expression Tests
TEST_CASE_METHOD(ExpressionFixture, "BooleanExpression basic functionality", "[expression][boolean]")
{
    INFO(sema->to_string());

    const auto true_expr = BooleanExpression::create(sema_ptr, true, false);
    const auto false_expr = BooleanExpression::create(sema_ptr, false, false);

    REQUIRE(true_expr->eval() == true);
    REQUIRE(false_expr->eval() == false);
    REQUIRE(true_expr->is_constant());
    REQUIRE(false_expr->is_constant());
    REQUIRE(sema->builtin_concept<bool>() == std::get<const Concept*>(true_expr->get_result()));
    REQUIRE(sema->builtin_concept<bool>() == std::get<const Concept*>(false_expr->get_result()));
}

TEST_CASE_METHOD(ExpressionFixture, "BooleanExpression export functionality", "[expression][boolean][export]")
{
    INFO(sema->to_string());

    const auto true_static = BooleanExpression::create(sema_ptr, true, false);
    const auto false_dynamic = BooleanExpression::create(sema_ptr, false, true);

    REQUIRE(true_static->to_cpp().find("::cong::lang::BooleanStatic<true>{}") != std::string::npos);
    REQUIRE(false_dynamic->to_cpp().find("::cong::lang::BooleanDynamic{false}") != std::string::npos);

    REQUIRE(true_static->to_python() == "Boolean(True)");
    REQUIRE(false_dynamic->to_python() == "Boolean(False)");
}

// LetVariableReferenceExpression Tests
TEST_CASE_METHOD(ExpressionFixture, "LetVariableReferenceExpression basic functionality", "[expression][letvar]")
{
    INFO(sema->to_string());

    const std::string identifier = "test_var";
    auto bound_value = std::make_shared<IntegerExpression>(sema_ptr, 123, false);

    const auto let_var_ref = LetVariableReferenceExpression::create(sema_ptr, identifier, bound_value);

    REQUIRE(let_var_ref->get_identifier() == identifier);
    REQUIRE(let_var_ref->get_bound_value() == bound_value);
    REQUIRE(let_var_ref->get_result() == bound_value->get_result());
}

TEST_CASE_METHOD(ExpressionFixture, "LetVariableReferenceExpression invalid construction", "[expression][letvar]")
{
    INFO(sema->to_string());

    auto bound_value = std::make_shared<IntegerExpression>(sema_ptr, 123, false);

    REQUIRE_THROWS_AS(LetVariableReferenceExpression(sema_ptr, "", bound_value), std::runtime_error);
    REQUIRE_THROWS_AS(LetVariableReferenceExpression(sema_ptr, "valid_name", nullptr), std::runtime_error);
}

TEST_CASE_METHOD(ExpressionFixture, "LetVariableReferenceExpression export functionality", "[expression][letvar][export]")
{
    INFO(sema->to_string());

    const std::string identifier = "my_variable";
    auto bound_value = std::make_shared<StringExpression>(sema_ptr, "test");

    const auto let_var_ref = LetVariableReferenceExpression::create(sema_ptr, identifier, bound_value);

    REQUIRE(let_var_ref->to_cpp() == identifier);
    REQUIRE(let_var_ref->to_python() == identifier);
}

// ConceptReferenceExpression Tests
TEST_CASE_METHOD(ExpressionFixture, "ConceptReferenceExpression basic functionality", "[expression][concept]")
{
    INFO(sema->to_string());

    const auto* string_concept = sema->builtin_concept<std::string>();
    const auto concept_ref = ConceptReferenceExpression::create(sema_ptr, string_concept);

    REQUIRE(concept_ref->get_concept() == string_concept);
    REQUIRE(string_concept == std::get<const Concept*>(concept_ref->get_result()));
}

TEST_CASE_METHOD(ExpressionFixture, "ConceptReferenceExpression invalid construction", "[expression][concept]")
{
    INFO(sema->to_string());

    REQUIRE_THROWS_AS(ConceptReferenceExpression(sema_ptr, nullptr), std::runtime_error);
}

TEST_CASE_METHOD(ExpressionFixture, "ConceptReferenceExpression export functionality", "[expression][concept][export]")
{
    INFO(sema->to_string());

    const auto* bool_concept = sema->builtin_concept<bool>();
    const auto concept_ref = ConceptReferenceExpression::create(sema_ptr, bool_concept);

    std::string cpp_output = concept_ref->to_cpp();
    std::string python_output = concept_ref->to_python();

    REQUIRE(cpp_output.find("::cong::lang::intern::Exp<") != std::string::npos);
    REQUIRE(cpp_output.find("ConceptBoolean>{}") != std::string::npos);
    REQUIRE(python_output.find("ConceptWrapper(ConceptBoolean)") != std::string::npos);
}

// OpenBindingExpression Tests
TEST_CASE_METHOD(ExpressionFixture, "OpenBindingExpression basic functionality", "[expression][openbinding]")
{
    INFO(sema->to_string());

    const unsigned int binding_index = 5;
    const auto open_binding = OpenBindingExpression::create(sema_ptr, binding_index);

    REQUIRE(open_binding->is_constant());

    const auto result = open_binding->get_result();
    REQUIRE(std::holds_alternative<OpenBinding>(result));
    REQUIRE(std::get<OpenBinding>(result).N == binding_index);
}

TEST_CASE_METHOD(ExpressionFixture, "OpenBindingExpression export functionality", "[expression][openbinding][export]")
{
    INFO(sema->to_string());

    const auto open_binding = OpenBindingExpression::create(sema_ptr, 3);

    std::string cpp_output = open_binding->to_cpp();
    std::string python_output = open_binding->to_python();

    REQUIRE(cpp_output == "::cong::lang::Proj<3>{}");
    REQUIRE(python_output == "Proj(3)");
}

// QuoteExpression Tests
TEST_CASE_METHOD(ExpressionFixture, "QuoteExpression basic functionality", "[expression][quote]")
{
    INFO(sema->to_string());

    auto inner_expr = std::make_shared<IntegerExpression>(sema_ptr, 42, false);
    const auto quote_expr = QuoteExpression::create(sema_ptr, inner_expr);

    REQUIRE(quote_expr->get_inner() == inner_expr);
    REQUIRE(quote_expr->get_result() == inner_expr->get_result());
}

TEST_CASE_METHOD(ExpressionFixture, "QuoteExpression export functionality", "[expression][quote][export]")
{
    INFO(sema->to_string());

    auto inner_expr = std::make_shared<StringExpression>(sema_ptr, "test");
    const auto quote_expr = QuoteExpression::create(sema_ptr, inner_expr);

    std::string cpp_output = quote_expr->to_cpp();
    std::string python_output = quote_expr->to_python();

    REQUIRE(cpp_output.find("::cong::lang::quote(") != std::string::npos);
    REQUIRE(cpp_output.find("test") != std::string::npos);
    REQUIRE(python_output.find("Quote(") != std::string::npos);
    REQUIRE(python_output.find("test") != std::string::npos);
}

// CastExpression Tests
TEST_CASE_METHOD(ExpressionFixture, "CastExpression basic functionality", "[expression][cast]")
{
    INFO(sema->to_string());

    const auto* target_concept = sema->builtin_concept<double>();
    auto value_expr = std::make_shared<IntegerExpression>(sema_ptr, 42, false);

    const auto cast_expr = CastExpression::create(sema_ptr, target_concept, value_expr);

    REQUIRE(target_concept == std::get<const Concept*>(cast_expr->get_result()));
}

TEST_CASE_METHOD(ExpressionFixture, "CastExpression export functionality", "[expression][cast][export]")
{
    INFO(sema->to_string());

    const auto* target_concept = sema->builtin_concept<double>();
    auto value_expr = std::make_shared<IntegerExpression>(sema_ptr, 42, false);

    const auto cast_expr = CastExpression::create(sema_ptr, target_concept, value_expr);

    // Cast expressions should pass through to the underlying value's export
    REQUIRE(cast_expr->to_cpp() == value_expr->to_cpp());
    REQUIRE(cast_expr->to_python() == value_expr->to_python());
}

// EvalExpression Tests
TEST_CASE_METHOD(ExpressionFixture, "EvalExpression basic functionality", "[expression][eval]")
{
    INFO(sema->to_string());

    auto inner_expr = std::make_shared<BooleanExpression>(sema_ptr, true, false);
    const auto eval_expr = EvalExpression::create(sema_ptr, inner_expr);

    REQUIRE(eval_expr->get_inner() == inner_expr);
    REQUIRE(eval_expr->get_result() == inner_expr->get_result());
}

TEST_CASE_METHOD(ExpressionFixture, "EvalExpression export functionality", "[expression][eval][export]")
{
    INFO(sema->to_string());

    auto inner_expr = std::make_shared<IntegerExpression>(sema_ptr, 123, false);
    const auto eval_expr = EvalExpression::create(sema_ptr, inner_expr);

    std::string cpp_output = eval_expr->to_cpp();
    std::string python_output = eval_expr->to_python();

    REQUIRE(cpp_output.find("::cong::lang::intern::eval(") != std::string::npos);
    REQUIRE(python_output.find("eval(") != std::string::npos);
}

// LambdaExpression Tests
TEST_CASE_METHOD(ExpressionFixture, "LambdaExpression basic functionality", "[expression][lambda]")
{
    INFO(sema->to_string());

    // Create a simple lambda with one parameter
    vec<std::tuple<std::string, std::variant<PlaceholderFunctionParameter*, Concept*>>> params;
    params.emplace_back(std::make_tuple(std::string("x"), static_cast<Concept*>(const_cast<Concept*>(sema->builtin_concept<long>()))));

    auto body = std::make_shared<IntegerExpression>(sema_ptr, 42, false);
    auto lambda_expr = std::make_shared<LambdaExpression>(sema_ptr, params, body);

    REQUIRE(lambda_expr->get_params().size() == 1);
    REQUIRE(lambda_expr->get_body() == body);
    REQUIRE(sema->builtin_concept<Map>() == std::get<const Concept*>(lambda_expr->get_result()));
}

TEST_CASE_METHOD(ExpressionFixture, "LambdaExpression export functionality", "[expression][lambda][export]")
{
    INFO(sema->to_string());

    vec<std::tuple<std::string, std::variant<PlaceholderFunctionParameter*, Concept*>>> params;
    params.emplace_back(std::make_tuple(std::string("param1"), static_cast<Concept*>(const_cast<Concept*>(sema->builtin_concept<long>()))));
    params.emplace_back(std::make_tuple(std::string("param2"), static_cast<Concept*>(const_cast<Concept*>(sema->builtin_concept<bool>()))));

    auto body = std::make_shared<BooleanExpression>(sema_ptr, true, false);
    auto lambda_expr = std::make_shared<LambdaExpression>(sema_ptr, params, body);

    std::string cpp_output = lambda_expr->to_cpp();
    std::string python_output = lambda_expr->to_python();

    REQUIRE(cpp_output.find("cong::lang::intern::WrapLambda([&](") != std::string::npos);
    REQUIRE(cpp_output.find("auto&& param1, auto&& param2") != std::string::npos);

    REQUIRE(python_output.find("WrapLambda(lambda ") != std::string::npos);
    REQUIRE(python_output.find("param1, param2") != std::string::npos);
}

// CallMetafunExpression Tests (base class)
TEST_CASE_METHOD(ExpressionFixture, "CallMetafunExpression invalid construction", "[expression][metafun]")
{
    INFO(sema->to_string());

    // Should throw when inner expression is null
    REQUIRE_THROWS_AS(QuoteExpression(sema_ptr, nullptr), std::runtime_error);
    REQUIRE_THROWS_AS(EvalExpression(sema_ptr, nullptr), std::runtime_error);
}
