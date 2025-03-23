//
// Created by Marvin Haschker on 16.03.25.
//
#include "../Common.h"
#include "sema/EvaluationContext.h"

TEST_GROUP(EvaluationContextGroup)
{
    DEFAULT_SEMA()
};

TEST(EvaluationContextGroup, TestEvaluatingConstantExpression)
{
    const auto exp = std::make_shared<StringExpression>(sema.get(), "hello");

    CHECK_EQUAL(exp.get(), EvaluationContext::bind_expression(exp, {}).get());
}

TEST(EvaluationContextGroup, TestEvaluatingConcreteFunctionCall)
{
    auto c_bool = *sema->find_concept("Boolean");
    const auto sema_ptr = sema.get();
    auto f = Sema::create_function<ConcreteFunction>(sema.get(), "f", sema_ptr, c_bool);

    const auto callExp = std::make_shared<CallExpression>(sema.get(), *f, vec<s_ptr<Expression>>{});

    CHECK_EQUAL_TEXT(callExp.get(), EvaluationContext::bind_expression(callExp, {}).get(),
                    "Expression instance returned should be the same.");
}

TEST(EvaluationContextGroup, TestEvaluatingEmptyDependentFunctionCall)
{
    auto f = *Sema::create_function<DependentFunction>(sema.get(), "f", sema_ptr);
    const auto p = f->register_function_parameter<PlaceholderFunctionParameter>("param", "T");
    f->set_dependency(p);

    const auto some_dependency = std::make_shared<FunctionParameterExpression>(sema.get(), f->get_parameters()[0]);

    const auto callExp = std::make_shared<CallExpression>(sema.get(), f, vec<s_ptr<Expression>>{some_dependency});

    CHECK_EQUAL_TEXT(p, std::get<const PlaceholderFunctionParameter*>(callExp->get_result()),
                     "Resulting concept cannot be determined at this point");
    CHECK_EQUAL_TEXT(callExp.get(), EvaluationContext::bind_expression(callExp, {}).get(),
                     "Expression instance returned should be the same.");
}

TEST(EvaluationContextGroup, TestEvaluatingDependentFunctionCall)
{
    auto f = *Sema::create_function<DependentFunction>(sema_ptr, "f", sema_ptr);
    auto p = f->register_function_parameter<PlaceholderFunctionParameter>("param", "T");
    f->set_dependency(p);

    const auto some_dependency = std::make_shared<FunctionParameterExpression>(sema_ptr, p);

    const auto some_arg = std::make_shared<StringExpression>(sema_ptr, "hello");
    const auto callExp = std::make_shared<CallExpression>(sema_ptr, f, vec<s_ptr<Expression>>{some_dependency});
    const auto c_number = *sema->find_concept("Number");

    const auto newCallExp = utils::dyn_ptr_cast<CallExpression>(EvaluationContext::bind_expression(callExp, { {p, c_number} }));
    CHECK_TRUE_TEXT(newCallExp.get() != callExp.get(),
                    "Expression instance returned should be different.");
    CHECK_EQUAL_TEXT(c_number, std::get<const Concept*>(newCallExp->get_result()),
                    "Call Expression should return the bound concept.");
    CHECK_EQUAL_TEXT(callExp->get_arguments().size(), newCallExp->get_arguments().size(),
                    "Argument size should be the same");
    CHECK_TRUE_TEXT(utils::is<BoundFunctionParameterExpression>(newCallExp->get_arguments()[0]),
                    "First argument should be the bound parameter expression.");
}

TEST(EvaluationContextGroup, TestEvaluatingNestedDependentFunctionCall)
{
    const auto f = *Sema::create_function<DependentFunction>(sema_ptr, "f", sema_ptr);
    auto p = f->set_dependency(f->register_function_parameter<PlaceholderFunctionParameter>("param", "T"));

    auto boolean = *sema->find_concept("Boolean");
    auto f2 = *Sema::create_function<ConcreteFunction>(sema_ptr, "f2", sema_ptr, boolean);
    auto p2 = f2->register_function_parameter<PlaceholderFunctionParameter>("param", "T");

    const auto callExp = CallExpression::create(sema_ptr, f, vec<s_ptr<Expression>>{
        CallExpression::create(sema_ptr, f, vec<s_ptr<Expression>>{
            FunctionParameterExpression::create(sema_ptr, p2)
        })
    });

    CHECK_TRUE_TEXT(std::holds_alternative<const PlaceholderFunctionParameter*>(callExp->get_result()), "Result should be a placeholder");
    CHECK_EQUAL_TEXT(p, std::get<const PlaceholderFunctionParameter*>(callExp->get_result()), "Dependent type should be equal to p");

    const auto newCallExp = EvaluationContext::bind_expression(callExp, { {p2, boolean} });;
    CHECK_TRUE_TEXT(newCallExp.get() != callExp.get(), "Expression instance returned should be different.");
    CHECK_TRUE_TEXT(std::holds_alternative<const Concept*>(newCallExp->get_result()), "Result should contain a concept");
    CHECK_EQUAL_TEXT(boolean, std::get<const Concept*>(newCallExp->get_result()), "Result should be the boolean");
}

TEST(EvaluationContextGroup, TestBindingMultiplePlaceholders)
{
    const auto f = *Sema::create_function<DependentFunction>(sema_ptr, "f", sema_ptr);
    auto p1 = f->register_function_parameter<PlaceholderFunctionParameter>("param1", "T");
    auto p2 = f->register_function_parameter<PlaceholderFunctionParameter>("param2", "U");
    f->set_dependency(p1);

    const auto callExp = CallExpression::create(sema_ptr, f, vec<s_ptr<Expression>>{
        FunctionParameterExpression::create(sema_ptr, p1),
        FunctionParameterExpression::create(sema_ptr, p2)
    });

    auto boolean = *sema->find_concept("Boolean");
    auto number = *sema->find_concept("Number");

    const auto newCallExp = EvaluationContext::bind_expression(callExp, {
        {p1, boolean},
        {p2, number}
    });

    CHECK_TRUE_TEXT(newCallExp.get() != callExp.get(), "Expression instance returned should be different");
    CHECK_TRUE_TEXT(std::holds_alternative<const Concept*>(newCallExp->get_result()), "Result should contain a concept");
    CHECK_EQUAL_TEXT(boolean, std::get<const Concept*>(newCallExp->get_result()), "Result should be the boolean");

    auto args = utils::dyn_ptr_cast<CallExpression>(newCallExp)->get_arguments();
    CHECK_TRUE_TEXT(utils::is<BoundFunctionParameterExpression>(args[0]), "First argument should be bound");
    CHECK_TRUE_TEXT(utils::is<BoundFunctionParameterExpression>(args[1]), "Second argument should be bound");
}

TEST(EvaluationContextGroup, TestPartialBinding)
{
    const auto f = *Sema::create_function<DependentFunction>(sema_ptr, "f", sema_ptr);
    auto p1 = f->register_function_parameter<PlaceholderFunctionParameter>("param1", "T");
    auto p2 = f->register_function_parameter<PlaceholderFunctionParameter>("param2", "U");
    f->set_dependency(p2);

    const auto callExp = CallExpression::create(sema_ptr, f, vec<s_ptr<Expression>>{
        FunctionParameterExpression::create(sema_ptr, p1),
        FunctionParameterExpression::create(sema_ptr, p2)
    });

    auto number = *sema->find_concept("Number");

    // Only bind the first parameter
    const auto newCallExp = EvaluationContext::bind_expression(callExp, {{p1, number}});

    CHECK_TRUE_TEXT(newCallExp.get() != callExp.get(), "Expression instance returned should be different");
    CHECK_TRUE_TEXT(std::holds_alternative<const PlaceholderFunctionParameter*>(newCallExp->get_result()),
                    "Result should still be a placeholder");
    CHECK_EQUAL_TEXT(p2, std::get<const PlaceholderFunctionParameter*>(newCallExp->get_result()),
                    "Result should be the second placeholder");
}

TEST(EvaluationContextGroup, TestCyclicDependency)
{
    const auto f = *Sema::create_function<DependentFunction>(sema_ptr, "f", sema_ptr);
    auto p = f->register_function_parameter<PlaceholderFunctionParameter>("param", "T");
    f->set_dependency(p);

    const auto callExp = CallExpression::create(sema_ptr, f, vec<s_ptr<Expression>>{
        CallExpression::create(sema_ptr, f, vec<s_ptr<Expression>>{
            FunctionParameterExpression::create(sema_ptr, p)
        })
    });

    auto boolean = *sema->find_concept("Boolean");

    const auto newCallExp = utils::dyn_ptr_cast<CallExpression>(EvaluationContext::bind_expression(callExp, {{p, boolean}}));
    CHECK_TRUE_TEXT(newCallExp.get() != callExp.get(), "Expression instance returned should be different");
    CHECK_TRUE_TEXT(std::holds_alternative<const Concept*>(newCallExp->get_result()), "Result should be a concept");
    CHECK_EQUAL_TEXT(boolean, std::get<const Concept*>(newCallExp->get_result()), "Result should be boolean");

    auto innerCall = utils::dyn_ptr_cast<CallExpression>(newCallExp->get_arguments()[0]);
    CHECK_TRUE_TEXT(innerCall != nullptr, "First argument should be a call expression");
    CHECK_TRUE_TEXT(std::holds_alternative<const Concept*>(innerCall->get_result()),
                   "Inner call result should be a concept");
}

TEST(EvaluationContextGroup, TestBindingToConcreteExpression)
{
    const auto f = *Sema::create_function<DependentFunction>(sema_ptr, "f", sema_ptr);
    auto p = f->register_function_parameter<PlaceholderFunctionParameter>("param", "T");
    f->set_dependency(p);

    auto stringExp = StringExpression::create(sema_ptr, "hello");
    const auto callExp = CallExpression::create(sema_ptr, f, vec<s_ptr<Expression>>{stringExp});

    auto string = *sema->find_concept("String");
    const auto newCallExp = utils::dyn_ptr_cast<CallExpression>(EvaluationContext::bind_expression(callExp, {{p, string}}));

    CHECK_TRUE_TEXT(newCallExp.get() == callExp.get(), "Expression instance returned should not be different");
    CHECK_TRUE_TEXT(std::holds_alternative<const Concept*>(newCallExp->get_result()), "Result should be a concept");
    CHECK_EQUAL_TEXT(string, std::get<const Concept*>(newCallExp->get_result()), "Result should be string concept");
    CHECK_EQUAL_TEXT(stringExp.get(), newCallExp->get_arguments()[0].get(),
                    "Concrete expressions should remain unchanged");
}