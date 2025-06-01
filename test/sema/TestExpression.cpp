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
    REQUIRE_THROWS_AS(ConstantExpression<long>(sema_ptr, nullptr, 0), std::runtime_error);
}

TEST_CASE_METHOD(ExpressionFixture, "Constant expression evaluates to value", "[expression]")
{
    const auto c_str = *sema->find_concept("String");
    const std::string val = "hello";
    INFO(sema->to_string());

    const auto exp = ConstantExpression(sema_ptr, c_str, val);
    REQUIRE(val == exp.eval());
    REQUIRE(c_str == std::get<const Concept*>(exp.get_result()));
    REQUIRE(exp.is_constant());
}

TEST_CASE_METHOD(ExpressionFixture, "Function parameter expression concrete construction", "[expression]")
{
    const auto* object = *sema->find_concept("Object");
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
    const auto* object = *sema->find_concept("Object");
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
    const auto* object = *sema->find_concept("Object");
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
    const auto* object = *sema->find_concept("Object");
    auto* f = *Sema::create_function<ConcreteFunction>(sema_ptr, "test", sema_ptr, object);

    f->register_function_parameter(std::make_unique<ConcreteFunctionParameter>("param", sema->find_concept("Boolean").value()));
    f->register_function_parameter(std::make_unique<ConcreteFunctionParameter>("param2", sema->find_concept("Object").value()));
    INFO(sema->to_string());

    REQUIRE_THROWS_AS(CallExpression(sema_ptr, f, {
        std::make_shared<NumberExpression>(sema_ptr, 1),
        std::make_shared<BooleanExpression>(sema_ptr, false)
    }), std::runtime_error);

    REQUIRE_THROWS_AS(CallExpression(sema_ptr, f, {}), std::runtime_error);
}

TEST_CASE_METHOD(ExpressionFixture, "Call expression result on concrete function", "[expression]")
{
    auto c_bool = *sema->find_concept("Boolean");
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

    REQUIRE(sema->find_concept("String").value() == std::get<const Concept*>(callExp->get_result()));
}

TEST_CASE_METHOD(ExpressionFixture, "Arithmetic expression construction", "[expression]")
{
    const auto num1 = NumberExpression::create(sema_ptr, 5);
    const auto num2 = NumberExpression::create(sema_ptr, 10);
    INFO(sema->to_string());

    const auto expr = ArithmeticExpression::create(sema_ptr, num1, num2, Operator::ADD);
    INFO("Created arithmetic expression with operator: " + toString(expr->get_op()));

    REQUIRE(num1.get() == expr->get_left().get());
    REQUIRE(num2.get() == expr->get_right().get());
    REQUIRE(Operator::ADD == expr->get_op());
}

TEST_CASE_METHOD(ExpressionFixture, "Arithmetic expression with incompatible types throws", "[expression]")
{
    const auto num = NumberExpression::create(sema_ptr, 5);
    const auto str = StringExpression::create(sema_ptr, "hello");
    INFO(sema->to_string());

    REQUIRE_THROWS_AS(ArithmeticExpression(sema_ptr, num, str, Operator::ADD), std::runtime_error);
}

TEST_CASE_METHOD(ExpressionFixture, "Arithmetic expression result with same types", "[expression]")
{
    const auto num1 = NumberExpression::create(sema_ptr, 5);
    const auto num2 = NumberExpression::create(sema_ptr, 10);
    const auto number_concept = *sema->find_concept("Number");
    INFO(sema->to_string());

    const ArithmeticExpression expr(sema_ptr, num1, num2, Operator::ADD);
    INFO("Created arithmetic expression with operator: " + toString(expr.get_op()));

    REQUIRE(std::holds_alternative<const Concept*>(expr.get_result()));
    REQUIRE(number_concept == std::get<const Concept*>(expr.get_result()));
}

TEST_CASE_METHOD(ExpressionFixture, "Arithmetic expression result with mixed types", "[expression]")
{
    const auto num = NumberExpression::create(sema_ptr, 5);
    const auto real = RealExpression::create(sema_ptr, 3.14);
    const auto real_concept = *sema->find_concept("Real");
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

    const auto num = NumberExpression::create(sema_ptr, 5);
    const auto param_expr = FunctionParameterExpression::create(sema_ptr, p);

    const auto expr = ArithmeticExpression::create(sema_ptr, num, param_expr, Operator::ADD);
    INFO("Created arithmetic expression with placeholder");

    REQUIRE(std::holds_alternative<const PlaceholderFunctionParameter*>(expr->get_result()));
    REQUIRE(p == std::get<const PlaceholderFunctionParameter*>(expr->get_result()));

    const auto number = *sema->find_concept("Number");
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

    const auto number_concept = *sema->find_concept("Number");

    const auto param_expr = FunctionParameterExpression::create(sema_ptr, p);
    const auto bound_expr = param_expr->bind(number_concept);
    const auto num = NumberExpression::create(sema_ptr, 5);
    INFO("Created bound parameter expression");

    const auto expr = ArithmeticExpression::create(sema_ptr, num, bound_expr, Operator::ADD);
    INFO("Created arithmetic expression with bound parameter");

    REQUIRE(std::holds_alternative<const Concept*>(expr->get_result()));
    REQUIRE(number_concept == std::get<const Concept*>(expr->get_result()));
}

TEST_CASE_METHOD(ExpressionFixture, "Arithmetic expression with different operators", "[expression]")
{
    const auto num1 = NumberExpression::create(sema_ptr, 5);
    const auto num2 = NumberExpression::create(sema_ptr, 10);
    const auto number_concept = *sema->find_concept("Number");
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

    auto value_expr = std::make_shared<NumberExpression>(sema_ptr, 42);

    vec<s_ptr<Expression>> body_exprs;
    body_exprs.push_back(std::make_shared<NumberExpression>(sema_ptr, 100));
    
    const auto let_expr = LetExpression::create(sema_ptr, "x", value_expr, body_exprs);
    
    REQUIRE(let_expr->get_identifier() == "x");
    REQUIRE(let_expr->get_value() == value_expr);
    REQUIRE(let_expr->get_body() == body_exprs);
    
    const auto result = let_expr->get_result();

    REQUIRE(std::holds_alternative<const Concept*>(result));
}

TEST_CASE_METHOD(ExpressionFixture, "LetExpression with multiple body expressions", "[expression][let]")
{
    INFO(sema->to_string());
    
    const auto value_expr = std::make_shared<NumberExpression>(sema_ptr, 42);
    
    vec<s_ptr<Expression>> body_exprs;
    body_exprs.push_back(std::make_shared<NumberExpression>(sema_ptr, 10));
    body_exprs.push_back(std::make_shared<NumberExpression>(sema_ptr, 20));
    body_exprs.push_back(std::make_shared<NumberExpression>(sema_ptr, 30));
    
    const auto let_expr = LetExpression::create(sema_ptr, "x", value_expr, body_exprs);
    
    const auto result = let_expr->get_result();
    REQUIRE(std::holds_alternative<const Concept*>(result));
}

TEST_CASE_METHOD(ExpressionFixture, "LetExpression C++ export", "[expression][let][export]")
{
    INFO(sema->to_string());
    
    auto value_expr = std::make_shared<NumberExpression>(sema_ptr, 42);
    vec<s_ptr<Expression>> body_exprs;
    body_exprs.push_back(std::make_shared<NumberExpression>(sema_ptr, 100));
    
    auto let_expr = LetExpression::create(sema_ptr, "x", value_expr, body_exprs);
    
    std::string cpp_output = let_expr->to_cpp();

    REQUIRE(cpp_output.find("[&]() {") != std::string::npos);
    REQUIRE(cpp_output.find("auto x = ::cong::lang::NaturalStatic<42>{};") != std::string::npos);
    REQUIRE(cpp_output.find("return ::cong::lang::NaturalStatic<100>{};") != std::string::npos);
    REQUIRE(cpp_output.find("}()") != std::string::npos);
}

TEST_CASE_METHOD(ExpressionFixture, "LetExpression Python export", "[expression][let][export]")
{
    INFO(sema->to_string());
    
    const auto value_expr = std::make_shared<NumberExpression>(sema_ptr, 42);
    vec<s_ptr<Expression>> body_exprs;
    body_exprs.push_back(std::make_shared<NumberExpression>(sema_ptr, 100));
    
    const auto let_expr = LetExpression::create(sema_ptr, "x", value_expr, body_exprs);
    
    std::string python_output = let_expr->to_python();

    REQUIRE(python_output.find("(lambda: (") != std::string::npos);
    REQUIRE(python_output.find("setattr(locals(), 'x', Number(42))") != std::string::npos);
    REQUIRE(python_output.find("Number(100)") != std::string::npos);
    REQUIRE(python_output.find(")[-1])()") != std::string::npos);
}

TEST_CASE_METHOD(ExpressionFixture, "LetExpression invalid construction", "[expression][let]")
{
    INFO(sema->to_string());
    
    const auto value_expr = std::make_shared<NumberExpression>(sema_ptr, 42);
    
    vec<s_ptr<Expression>> empty_body;
    REQUIRE_THROWS_AS(LetExpression(sema_ptr, "x", value_expr, empty_body), std::runtime_error);
    
    vec<s_ptr<Expression>> body_exprs;
    body_exprs.push_back(std::make_shared<NumberExpression>(sema_ptr, 100));
    REQUIRE_THROWS_AS(LetExpression(sema_ptr, "", value_expr, body_exprs), std::runtime_error);

    REQUIRE_THROWS_AS(LetExpression(sema_ptr, "x", nullptr, body_exprs), std::runtime_error);
}