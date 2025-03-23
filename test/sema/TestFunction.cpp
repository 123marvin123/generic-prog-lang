//
// Created by Marvin Haschker on 15.03.25.
//
#include "../Common.h"

#include "sema/Function.h"

TEST_GROUP(FunctionGroup)
{
    CUSTOM_SEMA(
        (
            sema = std::make_unique<Sema>();
            sema_ptr = sema.get();

            object = *sema->find_concept("Object");

            id = *Sema::create_function<DependentFunction>(sema_ptr, "id", sema_ptr);
            id->set_dependency(id->register_function_parameter<PlaceholderFunctionParameter>("a", "T"));

            id2 = *Sema::create_function<ConcreteFunction>(sema_ptr, "id2", sema_ptr, object);
            id2->register_function_parameter<ConcreteFunctionParameter>("param", object);
        ),
        (std::cout << "\n" << sema->to_string(4) << std::endl; sema.reset();)
    )
    DependentFunction* id;
    ConcreteFunction* id2;
    Concept* object;
};

TEST(FunctionGroup, TestConcreteFunctionThrowsForEmptyName)
{
    CHECK_THROWS(std::runtime_error, ConcreteFunction("", sema_ptr, object));
}

TEST(FunctionGroup, TestConcreteFunctionThrowsForNullConcept)
{
    CHECK_THROWS(std::runtime_error, ConcreteFunction("f", sema_ptr, nullptr));
}

TEST(FunctionGroup, TestDependentFunctionThrowsForEmptyName)
{
    auto* placeholder = new PlaceholderFunctionParameter("a", "T");
    CHECK_THROWS(std::runtime_error, DependentFunction("", sema_ptr));
    delete placeholder;
}

TEST(FunctionGroup, TestDependentFunctionThrowsForNullDependency)
{
    CHECK_THROWS(std::runtime_error, DependentFunction("f", sema_ptr).get_result());
}

TEST(FunctionGroup, TestConcreteFunctionConstruction)
{
    constexpr auto f_id = "some_fun";
    const ConcreteFunction k(f_id, sema_ptr, object);

    CHECK_EQUAL(f_id, std::string(k.get_identifier()));
    CHECK_EQUAL(object, std::get<const Concept*>(k.get_result()));
    CHECK_EQUAL(sema_ptr, k.get_namespace());
    CHECK_TRUE(k.get_parameters().empty());
    CHECK_TRUE(!k.is_dependent());
}

TEST(FunctionGroup, TestDependentFunctionConstruction)
{
    constexpr auto f_id = "some_fun";

    DependentFunction k(f_id, sema_ptr);

    CHECK_TRUE(k.get_parameters().empty());
    CHECK_EQUAL(f_id, std::string(k.get_identifier()));
    CHECK_EQUAL(sema_ptr, k.get_namespace());

    auto p = k.register_function_parameter<PlaceholderFunctionParameter>("a", "T");
    k.set_dependency(p);
    CHECK_EQUAL(1, k.get_parameters().size());
    CHECK_EQUAL(p, k.get_parameters()[0]);
    CHECK_EQUAL(p, std::get<PlaceholderFunctionParameter*>(k.get_result()));

    CHECK_TRUE(k.is_dependent());
}

TEST(FunctionGroup, TestRegisterParameterThrowsIfAlreadyRegistered)
{
    const auto p_id = std::string(id2->get_parameters()[0]->get_identifier());
    auto param = std::make_unique<ConcreteFunctionParameter>(p_id, object);
    CHECK_THROWS(std::runtime_error, id2->register_function_parameter(std::move(param)));
}

TEST(FunctionGroup, TestFindFunctionParameterReturnsCorrectParameter)
{
    constexpr auto p_id = "param2";
    auto param = std::make_unique<ConcreteFunctionParameter>(p_id, object);
    id2->register_function_parameter(std::move(param));

    const auto result = id2->find_function_parameter(p_id);
    CHECK(result.has_value());
    CHECK_EQUAL(p_id, std::string((*result)->get_identifier()));
}

TEST(FunctionGroup, TestFindFunctionParameterReturnsNullForNonExistentParameter)
{
    const auto result = id->find_function_parameter("non_existent_param");
    CHECK(!result.has_value());
}

TEST(FunctionGroup, FindFunctionParameterHandlesMultipleParameters)
{
    constexpr auto p1_id = "param1";
    constexpr auto p2_id = "param2";

    ConcreteFunction fn("testFunction", sema_ptr, object);

    auto param1 = std::make_unique<FunctionParameter>(p1_id);
    auto param2 = std::make_unique<FunctionParameter>(p2_id);

    fn.register_function_parameter(std::move(param1));
    fn.register_function_parameter(std::move(param2));

    auto result1 = fn.find_function_parameter(p1_id);
    auto result2 = fn.find_function_parameter(p2_id);

    CHECK(result1.has_value());
    CHECK(result1.value()->get_identifier() == p1_id);

    CHECK(result2.has_value());
    CHECK(result2.value()->get_identifier() == p2_id);
}