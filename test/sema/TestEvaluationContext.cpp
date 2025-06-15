//
// Created by Marvin Haschker on 16.03.25.
//
#include <catch2/catch_test_macros.hpp>
#include "../Common.h"
#include "sema/EvaluationContext.h"

struct EvaluationContextFixture
{
    std::unique_ptr<Sema> sema;
    Sema* sema_ptr;

    EvaluationContextFixture()
    {
        sema = std::make_unique<Sema>();
        sema_ptr = sema.get();
    }

    ~EvaluationContextFixture() { sema.reset(); }
};

TEST_CASE_METHOD(EvaluationContextFixture, "Evaluating constant expression", "[evaluation_context]")
{
    INFO(sema->to_string());
    const auto exp = std::make_shared<StringExpression>(sema.get(), "hello");

    REQUIRE(exp.get() == EvaluationContext::bind_expression(exp, {}).get());
}

TEST_CASE_METHOD(EvaluationContextFixture, "Evaluating concrete function call", "[evaluation_context]")
{
    auto c_bool = *sema->find_concept("Boolean");
    const auto sema_ptr = sema.get();
    auto f = Sema::create_function<ConcreteFunction>(sema.get(), "f", sema_ptr, c_bool);
    INFO(sema->to_string());

    const auto callExp = std::make_shared<CallExpression>(sema.get(), *f, vec<s_ptr<Expression>>{});

    INFO("Binding expression for concrete function call");
    REQUIRE(callExp.get() == EvaluationContext::bind_expression(callExp, {}).get());
}

TEST_CASE_METHOD(EvaluationContextFixture, "Evaluating empty dependent function call", "[evaluation_context]")
{
    auto f = *Sema::create_function<DependentFunction>(sema.get(), "f", sema_ptr);
    const auto p = f->register_function_parameter<PlaceholderFunctionParameter>("param", "T");
    f->set_dependency(p);
    INFO(sema->to_string());

    const auto some_dependency = std::make_shared<FunctionParameterExpression>(sema.get(), f->get_parameters()[0]);

    const auto callExp = std::make_shared<CallExpression>(sema.get(), f, vec<s_ptr<Expression>>{some_dependency});

    INFO("Checking function call result is placeholder");
    REQUIRE(p == std::get<const PlaceholderFunctionParameter*>(callExp->get_result()));

    INFO("Binding expression for empty dependent function call");
    REQUIRE(callExp.get() == EvaluationContext::bind_expression(callExp, {}).get());
}

TEST_CASE_METHOD(EvaluationContextFixture, "Evaluating dependent function call", "[evaluation_context]")
{
    auto f = *Sema::create_function<DependentFunction>(sema_ptr, "f", sema_ptr);
    auto p = f->register_function_parameter<PlaceholderFunctionParameter>("param", "T");
    f->set_dependency(p);
    INFO(sema->to_string());

    const auto some_dependency = std::make_shared<FunctionParameterExpression>(sema_ptr, p);

    const auto some_arg = std::make_shared<StringExpression>(sema_ptr, "hello");
    const auto callExp = std::make_shared<CallExpression>(sema_ptr, f, vec<s_ptr<Expression>>{some_dependency});
    const auto c_number = *sema->find_concept("Number");

    INFO("Binding dependent function call with Number concept");
    const auto newCallExp =
        utils::dyn_ptr_cast<CallExpression>(EvaluationContext::bind_expression(callExp, {{p, c_number}}));

    REQUIRE(newCallExp.get() != callExp.get());
    REQUIRE(c_number == std::get<const Concept*>(newCallExp->get_result()));
    REQUIRE(callExp->get_arguments().size() == newCallExp->get_arguments().size());
    REQUIRE(utils::is<BoundFunctionParameterExpression>(newCallExp->get_arguments()[0]));
}

TEST_CASE_METHOD(EvaluationContextFixture, "Evaluating nested dependent function call", "[evaluation_context]")
{
    const auto f = *Sema::create_function<DependentFunction>(sema_ptr, "f", sema_ptr);
    auto p = f->set_dependency(f->register_function_parameter<PlaceholderFunctionParameter>("param", "T"));

    auto boolean = *sema->find_concept("Boolean");
    auto f2 = *Sema::create_function<ConcreteFunction>(sema_ptr, "f2", sema_ptr, boolean);
    auto p2 = f2->register_function_parameter<PlaceholderFunctionParameter>("param", "T");
    INFO(sema->to_string());

    const auto callExp = CallExpression::create(
        sema_ptr, f,
        vec<s_ptr<Expression>>{CallExpression::create(
            sema_ptr, f, vec<s_ptr<Expression>>{FunctionParameterExpression::create(sema_ptr, p2)})});
    INFO("Created nested dependent function call");

    REQUIRE(std::holds_alternative<const PlaceholderFunctionParameter*>(callExp->get_result()));
    REQUIRE(p == std::get<const PlaceholderFunctionParameter*>(callExp->get_result()));

    INFO("Binding nested dependent function call with Boolean concept");
    const auto newCallExp = EvaluationContext::bind_expression(callExp, {{p2, boolean}});
    REQUIRE(newCallExp.get() != callExp.get());
    REQUIRE(std::holds_alternative<const Concept*>(newCallExp->get_result()));
    REQUIRE(boolean == std::get<const Concept*>(newCallExp->get_result()));
}

TEST_CASE_METHOD(EvaluationContextFixture, "Binding multiple placeholders", "[evaluation_context]")
{
    const auto f = *Sema::create_function<DependentFunction>(sema_ptr, "f", sema_ptr);
    auto p1 = f->register_function_parameter<PlaceholderFunctionParameter>("param1", "T");
    auto p2 = f->register_function_parameter<PlaceholderFunctionParameter>("param2", "U");
    f->set_dependency(p1);
    INFO(sema->to_string());

    const auto callExp =
        CallExpression::create(sema_ptr, f,
                               vec<s_ptr<Expression>>{FunctionParameterExpression::create(sema_ptr, p1),
                                                      FunctionParameterExpression::create(sema_ptr, p2)});
    INFO("Created function call with two placeholder parameters");

    auto boolean = *sema->find_concept("Boolean");
    auto number = *sema->find_concept("Number");

    INFO("Binding both placeholders with Boolean and Number concepts");
    const auto newCallExp = EvaluationContext::bind_expression(callExp, {{p1, boolean}, {p2, number}});

    REQUIRE(newCallExp.get() != callExp.get());
    REQUIRE(std::holds_alternative<const Concept*>(newCallExp->get_result()));
    REQUIRE(boolean == std::get<const Concept*>(newCallExp->get_result()));

    auto args = utils::dyn_ptr_cast<CallExpression>(newCallExp)->get_arguments();
    REQUIRE(utils::is<BoundFunctionParameterExpression>(args[0]));
    REQUIRE(utils::is<BoundFunctionParameterExpression>(args[1]));
}

TEST_CASE_METHOD(EvaluationContextFixture, "Partial binding", "[evaluation_context]")
{
    const auto f = *Sema::create_function<DependentFunction>(sema_ptr, "f", sema_ptr);
    auto p1 = f->register_function_parameter<PlaceholderFunctionParameter>("param1", "T");
    auto p2 = f->register_function_parameter<PlaceholderFunctionParameter>("param2", "U");
    f->set_dependency(p2);
    INFO(sema->to_string());

    const auto callExp =
        CallExpression::create(sema_ptr, f,
                               vec<s_ptr<Expression>>{FunctionParameterExpression::create(sema_ptr, p1),
                                                      FunctionParameterExpression::create(sema_ptr, p2)});
    INFO("Created function call with two placeholder parameters");

    auto number = *sema->find_concept("Number");

    INFO("Binding only first parameter with Number concept");
    const auto newCallExp = EvaluationContext::bind_expression(callExp, {{p1, number}});

    REQUIRE(newCallExp.get() != callExp.get());
    REQUIRE(std::holds_alternative<const PlaceholderFunctionParameter*>(newCallExp->get_result()));
    REQUIRE(p2 == std::get<const PlaceholderFunctionParameter*>(newCallExp->get_result()));
}

TEST_CASE_METHOD(EvaluationContextFixture, "Cyclic dependency", "[evaluation_context]")
{
    const auto f = *Sema::create_function<DependentFunction>(sema_ptr, "f", sema_ptr);
    auto p = f->register_function_parameter<PlaceholderFunctionParameter>("param", "T");
    f->set_dependency(p);
    INFO(sema->to_string());

    const auto callExp = CallExpression::create(
        sema_ptr, f,
        vec<s_ptr<Expression>>{CallExpression::create(
            sema_ptr, f, vec<s_ptr<Expression>>{FunctionParameterExpression::create(sema_ptr, p)})});
    INFO("Created function call with cyclic dependency");

    auto boolean = *sema->find_concept("Boolean");

    INFO("Binding cyclic dependency with Boolean concept");
    const auto newCallExp =
        utils::dyn_ptr_cast<CallExpression>(EvaluationContext::bind_expression(callExp, {{p, boolean}}));

    REQUIRE(newCallExp.get() != callExp.get());
    REQUIRE(std::holds_alternative<const Concept*>(newCallExp->get_result()));
    REQUIRE(boolean == std::get<const Concept*>(newCallExp->get_result()));

    auto innerCall = utils::dyn_ptr_cast<CallExpression>(newCallExp->get_arguments()[0]);
    REQUIRE(innerCall != nullptr);
    REQUIRE(std::holds_alternative<const Concept*>(innerCall->get_result()));
}

TEST_CASE_METHOD(EvaluationContextFixture, "Binding to concrete expression", "[evaluation_context]")
{
    const auto f = *Sema::create_function<DependentFunction>(sema_ptr, "f", sema_ptr);
    auto p = f->register_function_parameter<PlaceholderFunctionParameter>("param", "T");
    f->set_dependency(p);
    INFO(sema->to_string());

    auto stringExp = StringExpression::create(sema_ptr, "hello");
    const auto callExp = CallExpression::create(sema_ptr, f, vec<s_ptr<Expression>>{stringExp});
    INFO("Created function call with string expression argument");

    auto string = sema->builtin_concept<std::string>();
    INFO("Binding with String concept");
    const auto newCallExp =
        utils::dyn_ptr_cast<CallExpression>(EvaluationContext::bind_expression(callExp, {{p, string}}));

    REQUIRE(newCallExp.get() == callExp.get());
    REQUIRE(std::holds_alternative<const Concept*>(newCallExp->get_result()));
    REQUIRE(string == std::get<const Concept*>(newCallExp->get_result()));
    REQUIRE(stringExp.get() == newCallExp->get_arguments()[0].get());
}
