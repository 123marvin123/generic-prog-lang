//
// Created by Marvin Haschker on 15.03.25.
//
#include "../Common.h"
#include "sema/FunctionParameter.h"

TEST_GROUP(FunctionParamGroup)
{
    CUSTOM_SEMA(
        (
            sema = std::make_unique<Sema>();
            sema_ptr = sema.get();
            object = *sema->find_concept("Object");
            id = *Sema::create_function<ConcreteFunction>(sema_ptr, "id", sema_ptr, object);
            id2 = *Sema::create_function<ConcreteFunction>(sema_ptr, "id2", sema_ptr, object);
        ),
        (std::cout << "\n" << sema->to_string(4) << std::endl; sema.reset();)
    )
    Function* id, *id2;
    Concept* object;
};

TEST(FunctionParamGroup, ConcreteConstructorThrowsForEmptyName)
{
    CHECK_THROWS(std::runtime_error, ConcreteFunctionParameter("", object));
}

TEST(FunctionParamGroup, ConcreteConstructorThrowsForEmptyConcept)
{
    CHECK_THROWS(std::runtime_error, ConcreteFunctionParameter("", nullptr));
}

TEST(FunctionParamGroup, ConcreteParamConstructorInitializesCorrectly)
{
    constexpr auto p_id = "param";
    ConcreteFunctionParameter param(p_id, object);
    param.set_function(id);

    CHECK_EQUAL(p_id, std::string(param.get_identifier()));
    CHECK_EQUAL(id, param.get_function());
    CHECK_EQUAL(object, param.get_type());
}

TEST(FunctionParamGroup, ConcreteParamSetFunctionUpdatesFunctionPointer)
{
    constexpr auto p_id = "param";
    ConcreteFunctionParameter param(p_id, object);
    param.set_function(id2);
    CHECK_EQUAL(id2, param.get_function());
}

TEST(FunctionParamGroup, PlaceholderConstructorThrowsForEmptyName)
{
    CHECK_THROWS(std::runtime_error, PlaceholderFunctionParameter("", "T"));
}

TEST(FunctionParamGroup, PlaceholderConstructorThrowsForEmptyPlaceholderName)
{
    CHECK_THROWS(std::runtime_error, PlaceholderFunctionParameter("name", ""));
}

TEST(FunctionParamGroup, PlaceholderConstructorInitializesCorrectly)
{
    constexpr auto p_id = "param";
    constexpr auto type_placeholder_id = "T";
    PlaceholderFunctionParameter param(p_id, type_placeholder_id);
    param.set_function(id);

    CHECK_EQUAL(p_id, std::string(param.get_identifier()));
    CHECK_EQUAL(id, param.get_function());
    CHECK_EQUAL(type_placeholder_id, param.get_type_placeholder_name());
}

TEST(FunctionParamGroup, DependentParamConstructorThrowsForEmptyName)
{
    CHECK_THROWS(std::runtime_error, DependentFunctionParameter("", nullptr));
}

TEST(FunctionParamGroup, DependentParamConstructorThrowsForNullPlaceholder)
{
    CHECK_THROWS(std::runtime_error, DependentFunctionParameter("name", nullptr));
}

TEST(FunctionParamGroup, DependentParamConstructorInitializesCorrectly)
{
    constexpr auto p_id = "param";
    constexpr auto type_placeholder_id = "T";
    const PlaceholderFunctionParameter param(p_id, type_placeholder_id);

    constexpr auto p2_id = "param2";
    DependentFunctionParameter dependent_param(p2_id, &param);
    dependent_param.set_function(id);

    CHECK_EQUAL(p2_id, std::string(dependent_param.get_identifier()));
    CHECK_EQUAL(id, dependent_param.get_function());
    CHECK_EQUAL(&param, dependent_param.get_placeholder());
}