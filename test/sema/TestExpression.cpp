//
// Created by Marvin Haschker on 15.03.25.
//
#include <sema/EvaluationContext.h>

#include "../Common.h"

SimpleString StringFrom(const Operator& op)
{
    return {utils::get_string_for_operator(op).data()};
}

TEST_GROUP(ExpressionGroup)
{
    DEFAULT_SEMA()
};

TEST(ExpressionGroup, TestConstantExpressionInvalidConstruction)
{
    CHECK_THROWS(std::runtime_error, ConstantExpression<long>(sema_ptr, nullptr, 0));
}

TEST(ExpressionGroup, TestConstantExpressionEvalutesToValue)
{
    const auto c_str = *sema->find_concept("String");
    const std::string val = "hello";

    const auto exp = ConstantExpression(sema_ptr, c_str, val);
    CHECK_EQUAL(val, exp.eval());
    CHECK_EQUAL(c_str, std::get<const Concept*>(exp.get_result()));

    CHECK_TRUE(exp.is_constant());
}

TEST(ExpressionGroup, TestFunctionParameterExpressionConcreteConstruction)
{
    const auto* object = *sema->find_concept("Object");
    const auto* f = *Sema::create_function<ConcreteFunction>(sema_ptr, "test", sema_ptr, object);
    const auto p = std::make_shared<ConcreteFunctionParameter>("param", object);
    p->set_function(f);

    const FunctionParameterExpression exp(sema_ptr, p.get());
    CHECK_FALSE(exp.is_constant());
    CHECK_EQUAL(object, std::get<const Concept*>(exp.get_result()));
    CHECK_EQUAL(p.get(), exp.get_param());
}

TEST(ExpressionGroup, TestFunctionParameterExpressionPlaceholderConstruction)
{
    const auto* object = *sema->find_concept("Object");
    auto* f = *Sema::create_function<ConcreteFunction>(sema_ptr, "test", sema_ptr, object);
    const auto* p = f->register_function_parameter(std::make_unique<PlaceholderFunctionParameter>("param", "T"));

    const FunctionParameterExpression exp(sema_ptr, p);
    CHECK_FALSE(exp.is_constant());
    CHECK_EQUAL(p, std::get<const PlaceholderFunctionParameter*>(exp.get_result()));
    CHECK_EQUAL(p, exp.get_param());
}

TEST(ExpressionGroup, TestBoundFunctionParameterExpressionConstruction)
{
    const auto* object = *sema->find_concept("Object");
    auto* f = *Sema::create_function<ConcreteFunction>(sema_ptr, "test", sema_ptr, object);
    const auto* p = f->register_function_parameter(std::make_unique<PlaceholderFunctionParameter>("param", "T"));

    const FunctionParameterExpression exp(sema_ptr, p);
    CHECK_EQUAL(p, std::get<const PlaceholderFunctionParameter*>(exp.get_result()));

    const auto bound_exp = exp.bind(object);

    CHECK_FALSE(bound_exp->is_constant());
    CHECK_EQUAL(object, std::get<const Concept*>(bound_exp->get_result()));
    CHECK_EQUAL(object, bound_exp->get_concept());
    CHECK_EQUAL(p, bound_exp->get_param());
}

TEST(ExpressionGroup, TestCallExpressionNullFunction)
{
    CHECK_THROWS(std::runtime_error, CallExpression(sema_ptr, nullptr, {}));
}

TEST(ExpressionGroup, TestCallExpressionInvalidArguments)
{
    const auto* object = *sema->find_concept("Object");
    auto* f = *Sema::create_function<ConcreteFunction>(sema_ptr, "test", sema_ptr, object);

    f->register_function_parameter(std::make_unique<ConcreteFunctionParameter>("param", sema->find_concept("Boolean").value()));
    f->register_function_parameter(std::make_unique<ConcreteFunctionParameter>("param2", sema->find_concept("Object").value()));

    CHECK_THROWS(std::runtime_error, CallExpression(sema_ptr, f, { std::make_shared<NumberExpression>(sema_ptr, 1), std::make_shared<BooleanExpression>(sema_ptr, false) }));
    CHECK_THROWS(std::runtime_error, CallExpression(sema_ptr, f, { }));
}

TEST(ExpressionGroup, TestCallExpressionResultOnConcreteFunction)
{
    auto c_bool = *sema->find_concept("Boolean");
    auto f = Sema::create_function<ConcreteFunction>(sema_ptr, "f", sema_ptr, c_bool);

    const auto callExp = std::make_shared<CallExpression>(sema_ptr, *f, vec<s_ptr<Expression>>{});
    CHECK_EQUAL(c_bool, std::get<const Concept*>(callExp->get_result()));
}

TEST(ExpressionGroup, TestCallExpressionResultOnDependentFunction)
{
    auto f = *Sema::create_function<DependentFunction>(sema_ptr, "f", sema_ptr);
    auto p = f->register_function_parameter<PlaceholderFunctionParameter>("param", "T");
    f->set_dependency(p);

    const auto some_arg = std::make_shared<StringExpression>(sema_ptr, "hello");
    const auto callExp = std::make_shared<CallExpression>(sema_ptr, f, vec<s_ptr<Expression>>{ some_arg });

    CHECK_EQUAL(sema->find_concept("String").value(),
        std::get<const Concept*>(callExp->get_result()));
}

TEST(ExpressionGroup, TestArithmeticExpressionConstruction)
{
    const auto num1 = NumberExpression::create(sema_ptr, 5);
    const auto num2 = NumberExpression::create(sema_ptr, 10);

    const auto expr = ArithmeticExpression::create(sema_ptr, num1, num2, Operator::ADD);

    CHECK_EQUAL(num1.get(), expr->get_left().get());
    CHECK_EQUAL(num2.get(), expr->get_right().get());
    CHECK_EQUAL(Operator::ADD, expr->get_op());
}

TEST(ExpressionGroup, TestArithmeticExpressionIncompatibleTypes)
{
    const auto num = NumberExpression::create(sema_ptr, 5);
    const auto str = StringExpression::create(sema_ptr, "hello");

    CHECK_THROWS(std::runtime_error, ArithmeticExpression(sema_ptr, num, str, Operator::ADD));
}

TEST(ExpressionGroup, TestArithmeticExpressionResultSameTypes)
{
    const auto num1 = NumberExpression::create(sema_ptr, 5);
    const auto num2 = NumberExpression::create(sema_ptr, 10);
    const auto number_concept = *sema->find_concept("Number");

    const ArithmeticExpression expr(sema_ptr, num1, num2, Operator::ADD);

    CHECK_TRUE(std::holds_alternative<const Concept*>(expr.get_result()));
    CHECK_EQUAL(number_concept, std::get<const Concept*>(expr.get_result()));
}

TEST(ExpressionGroup, TestArithmeticExpressionResultMixedTypes)
{
    const auto num = NumberExpression::create(sema_ptr, 5);
    const auto real = RealExpression::create(sema_ptr, 3.14);
    const auto real_concept = *sema->find_concept("Real");

    const ArithmeticExpression expr(sema_ptr, num, real, Operator::MUL);

    CHECK_TRUE(std::holds_alternative<const Concept*>(expr.get_result()));
    CHECK_EQUAL(real_concept, std::get<const Concept*>(expr.get_result()));
}

TEST(ExpressionGroup, TestArithmeticExpressionWithPlaceholder)
{
    auto* f = *Sema::create_function<DependentFunction>(sema_ptr, "test", sema_ptr);
    auto* p = f->register_function_parameter<PlaceholderFunctionParameter>("param", "T");
    f->set_dependency(p);

    const auto num = NumberExpression::create(sema_ptr, 5);
    const auto param_expr = FunctionParameterExpression::create(sema_ptr, p);

    const auto expr = ArithmeticExpression::create(sema_ptr, num, param_expr, Operator::ADD);

    CHECK_TRUE(std::holds_alternative<const PlaceholderFunctionParameter*>(expr->get_result()));
    CHECK_EQUAL(p, std::get<const PlaceholderFunctionParameter*>(expr->get_result()));

    const auto number = *sema->find_concept("Number");
    const auto bound_expr = EvaluationContext::bind_expression(expr, { {p, number} });
    CHECK_TRUE(std::holds_alternative<const Concept*>(bound_expr->get_result()));
    CHECK_EQUAL_TEXT(number, std::get<const Concept*>(bound_expr->get_result()),
                    "Result should be the bound concept");
}

TEST(ExpressionGroup, TestArithmeticExpressionWithBoundParameter)
{
    auto* f = *Sema::create_function<DependentFunction>(sema_ptr, "test", sema_ptr);
    auto* p = f->register_function_parameter<PlaceholderFunctionParameter>("param", "T");
    f->set_dependency(p);

    const auto number_concept = *sema->find_concept("Number");

    const auto param_expr = FunctionParameterExpression::create(sema_ptr, p);
    const auto bound_expr = param_expr->bind(number_concept);
    const auto num = NumberExpression::create(sema_ptr, 5);

    const auto expr = ArithmeticExpression::create(sema_ptr, num, bound_expr, Operator::ADD);

    CHECK_TRUE(std::holds_alternative<const Concept*>(expr->get_result()));
    CHECK_EQUAL(number_concept, std::get<const Concept*>(expr->get_result()));
}

TEST(ExpressionGroup, TestArithmeticExpressionDifferentOperators)
{
    const auto num1 = NumberExpression::create(sema_ptr, 5);
    const auto num2 = NumberExpression::create(sema_ptr, 10);
    const auto number_concept = *sema->find_concept("Number");

    auto add = ArithmeticExpression::create(sema_ptr, num1, num2, Operator::ADD);
    auto subtract = ArithmeticExpression::create(sema_ptr, num1, num2, Operator::SUB);
    auto multiply = ArithmeticExpression::create(sema_ptr, num1, num2, Operator::MUL);
    auto divide = ArithmeticExpression::create(sema_ptr, num1, num2, Operator::DIV);

    CHECK_EQUAL(number_concept, std::get<const Concept*>(add->get_result()));
    CHECK_EQUAL(number_concept, std::get<const Concept*>(subtract->get_result()));
    CHECK_EQUAL(number_concept, std::get<const Concept*>(multiply->get_result()));
    CHECK_EQUAL(number_concept, std::get<const Concept*>(divide->get_result()));
}