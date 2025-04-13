//
// Created by Marvin Haschker on 15.03.25.
//
#include <catch2/catch_test_macros.hpp>
#include "../Common.h"
#include "sema/FunctionParameter.h"

struct FunctionParamFixture
{
    std::unique_ptr<Sema> sema;
    Sema* sema_ptr;
    Function *id, *id2;
    Concept* object;

    FunctionParamFixture()
    {
        sema = std::make_unique<Sema>();
        sema_ptr = sema.get();
        object = *sema->find_concept("Object");
        id = *Sema::create_function<ConcreteFunction>(sema_ptr, "id", sema_ptr, object);
        id2 = *Sema::create_function<ConcreteFunction>(sema_ptr, "id2", sema_ptr, object);
    }

    ~FunctionParamFixture() { sema.reset(); }
};

TEST_CASE_METHOD(FunctionParamFixture, "Concrete constructor throws for empty name", "[function_param]")
{
    INFO(sema->to_string());
    REQUIRE_THROWS_AS(ConcreteFunctionParameter("", object), std::runtime_error);
}

TEST_CASE_METHOD(FunctionParamFixture, "Concrete constructor throws for empty concept", "[function_param]")
{
    INFO(sema->to_string());
    REQUIRE_THROWS_AS(ConcreteFunctionParameter("name", nullptr), std::runtime_error);
}

TEST_CASE_METHOD(FunctionParamFixture, "Concrete param constructor initializes correctly", "[function_param]")
{
    constexpr auto p_id = "param";
    ConcreteFunctionParameter param(p_id, object);
    param.set_function(id);

    INFO(sema->to_string());

    REQUIRE(std::string(param.get_identifier()) == p_id);
    REQUIRE(param.get_function() == id);
    REQUIRE(param.get_type() == object);
}

TEST_CASE_METHOD(FunctionParamFixture, "Concrete param set function updates function pointer", "[function_param]")
{
    constexpr auto p_id = "param";
    ConcreteFunctionParameter param(p_id, object);
    param.set_function(id2);

    INFO(sema->to_string());
    REQUIRE(param.get_function() == id2);
}

TEST_CASE_METHOD(FunctionParamFixture, "Placeholder constructor throws for empty name", "[function_param]")
{
    INFO(sema->to_string());
    REQUIRE_THROWS_AS(PlaceholderFunctionParameter("", "T"), std::runtime_error);
}

TEST_CASE_METHOD(FunctionParamFixture, "Placeholder constructor throws for empty placeholder name", "[function_param]")
{
    INFO(sema->to_string());
    REQUIRE_THROWS_AS(PlaceholderFunctionParameter("name", ""), std::runtime_error);
}

TEST_CASE_METHOD(FunctionParamFixture, "Placeholder constructor initializes correctly", "[function_param]")
{
    constexpr auto p_id = "param";
    constexpr auto type_placeholder_id = "T";
    PlaceholderFunctionParameter param(p_id, type_placeholder_id);
    param.set_function(id);

    INFO(sema->to_string());
    REQUIRE(std::string(param.get_identifier()) == p_id);
    REQUIRE(param.get_function() == id);
    REQUIRE(param.get_type_placeholder_name() == type_placeholder_id);
}

TEST_CASE_METHOD(FunctionParamFixture, "Dependent param constructor throws for empty name", "[function_param]")
{
    INFO(sema->to_string());
    REQUIRE_THROWS_AS(DependentFunctionParameter("", nullptr), std::runtime_error);
}

TEST_CASE_METHOD(FunctionParamFixture, "Dependent param constructor throws for null placeholder", "[function_param]")
{
    INFO(sema->to_string());
    REQUIRE_THROWS_AS(DependentFunctionParameter("name", nullptr), std::runtime_error);
}

TEST_CASE_METHOD(FunctionParamFixture, "Dependent param constructor initializes correctly", "[function_param]")
{
    constexpr auto p_id = "param";
    constexpr auto type_placeholder_id = "T";
    const PlaceholderFunctionParameter param(p_id, type_placeholder_id);

    constexpr auto p2_id = "param2";
    DependentFunctionParameter dependent_param(p2_id, &param);
    dependent_param.set_function(id);

    INFO(sema->to_string());
    REQUIRE(std::string(dependent_param.get_identifier()) == p2_id);
    REQUIRE(dependent_param.get_function() == id);
    REQUIRE(dependent_param.get_placeholder() == &param);
}
