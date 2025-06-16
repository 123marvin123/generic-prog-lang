//
// Created by Marvin Haschker on 15.03.25.
//
#include <catch2/catch_test_macros.hpp>
#include "../Common.h"

#include "sema/Function.h"

struct FunctionFixture {
    std::unique_ptr<Sema> sema;
    Sema* sema_ptr;
    DependentFunction* id;
    ConcreteFunction* id2;
    const Concept* object;

    FunctionFixture() {
        sema = std::make_unique<Sema>();
        sema_ptr = sema.get();

        object = sema->builtin_concept<Object>();

        id = *Sema::create_function<DependentFunction>(sema_ptr, "id", sema_ptr);
        id->set_dependency(id->register_function_parameter<PlaceholderFunctionParameter>("a", "T"));

        id2 = *Sema::create_function<ConcreteFunction>(sema_ptr, "id2", sema_ptr, object);
        id2->register_function_parameter<ConcreteFunctionParameter>("param", object);
    }

    ~FunctionFixture() {
        sema.reset();
    }
};

TEST_CASE_METHOD(FunctionFixture, "Concrete function throws for empty name", "[function]")
{
    INFO(sema->to_string());
    REQUIRE_THROWS_AS(ConcreteFunction("", sema_ptr, object), std::runtime_error);
}

TEST_CASE_METHOD(FunctionFixture, "Concrete function throws for null concept", "[function]")
{
    INFO(sema->to_string());
    REQUIRE_THROWS_AS(ConcreteFunction("f", sema_ptr, nullptr), std::runtime_error);
}

TEST_CASE_METHOD(FunctionFixture, "Dependent function throws for empty name", "[function]")
{
    INFO(sema->to_string());
    REQUIRE_THROWS_AS(DependentFunction("", sema_ptr), std::runtime_error);
}

TEST_CASE_METHOD(FunctionFixture, "Dependent function throws for null dependency", "[function]")
{
    INFO(sema->to_string());
    REQUIRE_THROWS_AS(DependentFunction("f", sema_ptr).get_result(), std::runtime_error);
}

TEST_CASE_METHOD(FunctionFixture, "Concrete function construction", "[function]")
{
    constexpr auto f_id = "some_fun";
    const ConcreteFunction k(f_id, sema_ptr, object);

    INFO(sema->to_string());
    REQUIRE(std::string(k.get_identifier()) == f_id);
    REQUIRE(std::get<const Concept*>(k.get_result()) == object);
    REQUIRE(k.get_namespace() == sema_ptr);
    REQUIRE(k.get_parameters().empty());
    REQUIRE_FALSE(k.is_dependent());
}

TEST_CASE_METHOD(FunctionFixture, "Dependent function construction", "[function]")
{
    constexpr auto f_id = "some_fun";
    DependentFunction k(f_id, sema_ptr);

    INFO(sema->to_string());
    REQUIRE(k.get_parameters().empty());
    REQUIRE(std::string(k.get_identifier()) == f_id);
    REQUIRE(k.get_namespace() == sema_ptr);

    auto p = k.register_function_parameter<PlaceholderFunctionParameter>("a", "T");
    k.set_dependency(p);
    REQUIRE(k.get_parameters().size() == 1);
    REQUIRE(k.get_parameters()[0] == p);
    REQUIRE(std::get<PlaceholderFunctionParameter*>(k.get_result()) == p);
    REQUIRE(k.is_dependent());
}

TEST_CASE_METHOD(FunctionFixture, "Register parameter throws if already registered", "[function]")
{
    const auto p_id = std::string(id2->get_parameters()[0]->get_identifier());
    auto param = std::make_unique<ConcreteFunctionParameter>(p_id, object);

    INFO(sema->to_string());
    REQUIRE_THROWS_AS(id2->register_function_parameter(std::move(param)), std::runtime_error);
}

TEST_CASE_METHOD(FunctionFixture, "Find function parameter returns correct parameter", "[function]")
{
    constexpr auto p_id = "param2";
    auto param = std::make_unique<ConcreteFunctionParameter>(p_id, object);
    id2->register_function_parameter(std::move(param));

    INFO(sema->to_string());
    const auto result = id2->find_function_parameter(p_id);
    REQUIRE(result.has_value());
    REQUIRE(std::string((*result)->get_identifier()) == p_id);
}

TEST_CASE_METHOD(FunctionFixture, "Find function parameter returns null for non-existent parameter", "[function]")
{
    INFO(sema->to_string());
    const auto result = id->find_function_parameter("non_existent_param");
    REQUIRE_FALSE(result.has_value());
}

TEST_CASE_METHOD(FunctionFixture, "Find function parameter handles multiple parameters", "[function]")
{
    constexpr auto p1_id = "param1";
    constexpr auto p2_id = "param2";

    ConcreteFunction fn("testFunction", sema_ptr, object);

    auto param1 = std::make_unique<FunctionParameter>(p1_id);
    auto param2 = std::make_unique<FunctionParameter>(p2_id);

    fn.register_function_parameter(std::move(param1));
    fn.register_function_parameter(std::move(param2));

    INFO(sema->to_string());
    auto result1 = fn.find_function_parameter(p1_id);
    auto result2 = fn.find_function_parameter(p2_id);

    REQUIRE(result1.has_value());
    REQUIRE(std::string(result1.value()->get_identifier()) == p1_id);

    REQUIRE(result2.has_value());
    REQUIRE(std::string(result2.value()->get_identifier()) == p2_id);
}