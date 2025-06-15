//
// Created by Marvin Haschker on 17.03.25.
//
#include <catch2/catch_test_macros.hpp>
#include <export/FunctionDependencyGraph.h>
#include <random>
#include "../Common.h"
#include "sema/GenericImplementation.h"

struct FunctionDependencyGraphFixture
{
    std::unique_ptr<Sema> sema;
    Sema* sema_ptr;

    FunctionDependencyGraphFixture()
    {
        sema = std::make_unique<Sema>();
        sema_ptr = sema.get();
    }

    ~FunctionDependencyGraphFixture() { sema.reset(); }
};

TEST_CASE_METHOD(FunctionDependencyGraphFixture, "Linear dependencies are sorted correctly",
                 "[function_dependency_graph]")
{
    auto boolean = sema->builtin_concept<bool>();
    INFO(sema->to_string());

    // Create functions with simple linear dependencies: C -> B -> A
    const auto A = *Sema::create_function<ConcreteFunction>(sema_ptr, "A", sema_ptr, boolean);
    const auto B = *Sema::create_function<ConcreteFunction>(sema_ptr, "B", sema_ptr, boolean);
    const auto C = *Sema::create_function<ConcreteFunction>(sema_ptr, "C", sema_ptr, boolean);

    A->add_generic_implementation(GenericImplementation(BooleanExpression::create(sema_ptr, true)));
    B->add_generic_implementation(GenericImplementation(CallExpression::create(sema_ptr, A, {})));
    C->add_generic_implementation(GenericImplementation(CallExpression::create(sema_ptr, B, {})));
    INFO("Created linear dependency chain: C -> B -> A");

    vec<Function*> functions = sema_ptr->functions();

    // Shuffle with a fixed seed for reproducibility
    std::mt19937 g(42); // Fixed seed NOLINT(*-msc51-cpp)
    std::ranges::shuffle(functions, g);
    INFO("Shuffled function order");

    FunctionDependencyGraph graph;
    graph.build_graph(functions);
    INFO("Built dependency graph");

    // Check the result
    const auto& sorted = graph.sorted_functions();

    // Verify we have exactly 3 functions
    REQUIRE(sorted.size() == 3);

    // The order should be: A, B, C
    REQUIRE(sorted[0] == A);
    REQUIRE(sorted[1] == B);
    REQUIRE(sorted[2] == C);
}

TEST_CASE_METHOD(FunctionDependencyGraphFixture, "Complex dependencies are sorted correctly",
                 "[function_dependency_graph]")
{
    auto boolean = sema->builtin_concept<bool>();
    INFO(sema->to_string());

    auto* X = *Sema::create_function<ConcreteFunction>(sema_ptr, "X", sema_ptr, boolean);
    auto* Y = *Sema::create_function<ConcreteFunction>(sema_ptr, "Y", sema_ptr, boolean);

    auto* A = *Sema::create_function<ConcreteFunction>(sema_ptr, "A", sema_ptr, boolean);
    auto* B = *Sema::create_function<ConcreteFunction>(sema_ptr, "B", sema_ptr, boolean);
    auto* C = *Sema::create_function<ConcreteFunction>(sema_ptr, "C", sema_ptr, boolean);
    auto* D = *Sema::create_function<ConcreteFunction>(sema_ptr, "D", sema_ptr, boolean);
    auto* E = *Sema::create_function<ConcreteFunction>(sema_ptr, "E", sema_ptr, boolean);

    X->add_generic_implementation(GenericImplementation(BooleanExpression::create(sema_ptr, true)));
    Y->add_generic_implementation(GenericImplementation(BooleanExpression::create(sema_ptr, true)));

    A->add_generic_implementation(GenericImplementation(CallExpression::create(sema_ptr, X, {})));
    B->add_generic_implementation(GenericImplementation(CallExpression::create(sema_ptr, Y, {})));
    C->add_generic_implementation(GenericImplementation(ArithmeticExpression::create(sema_ptr, CallExpression::create(sema_ptr, A, {}),
                                                               CallExpression::create(sema_ptr, B, {}), Operator::ADD)));
    D->add_generic_implementation(GenericImplementation(CallExpression::create(sema_ptr, B, {})));
    E->add_generic_implementation(GenericImplementation(ArithmeticExpression::create(sema_ptr, CallExpression::create(sema_ptr, A, {}),
                                                               CallExpression::create(sema_ptr, D, {}), Operator::ADD)));
    INFO("Created complex dependency graph");

    std::vector<const Function*> functions = {X, Y, A, B, C, D, E};

    std::mt19937 g(42); // Fixed seed NOLINT(*-msc51-cpp)
    std::ranges::shuffle(functions, g);
    INFO("Shuffled function order");

    FunctionDependencyGraph graph;
    graph.build_graph(sema_ptr);

    const auto& sorted = graph.sorted_functions();
    REQUIRE(sorted.size() == 7);

    std::unordered_map<const Function*, size_t> positions;
    for (size_t i = 0; i < sorted.size(); i++)
    {
        positions[sorted[i]] = i;
    }
    INFO("Created position map to verify ordering constraints");

    REQUIRE(positions[X] < positions[A]);
    REQUIRE(positions[Y] < positions[B]);
    REQUIRE(positions[A] < positions[C]);
    REQUIRE(positions[B] < positions[C]);
    REQUIRE(positions[B] < positions[D]);
    REQUIRE(positions[A] < positions[E]);
    REQUIRE(positions[D] < positions[E]);
}

TEST_CASE_METHOD(FunctionDependencyGraphFixture, "Cyclic dependency throws exception", "[function_dependency_graph]")
{
    auto boolean = sema->builtin_concept<bool>();
    INFO(sema->to_string());

    const auto A = *Sema::create_function<ConcreteFunction>(sema_ptr, "A", sema_ptr, boolean);
    const auto B = *Sema::create_function<ConcreteFunction>(sema_ptr, "B", sema_ptr, boolean);
    const auto C = *Sema::create_function<ConcreteFunction>(sema_ptr, "C", sema_ptr, boolean);

    // Create a cycle A -> B -> C -> A
    A->add_generic_implementation(GenericImplementation(CallExpression::create(sema_ptr, B, {})));
    B->add_generic_implementation(GenericImplementation(CallExpression::create(sema_ptr, C, {})));
    C->add_generic_implementation(GenericImplementation(CallExpression::create(sema_ptr, A, {})));
    INFO("Created cyclic dependency: A -> B -> C -> A");

    FunctionDependencyGraph graph;

    REQUIRE_THROWS_AS(graph.build_graph(sema_ptr), std::runtime_error);
}

TEST_CASE("Empty graph produces empty result", "[function_dependency_graph]")
{
    const auto emptySema = std::make_unique<Sema>(false);
    INFO("Created empty Sema");

    FunctionDependencyGraph graph;
    graph.build_graph(emptySema.get());

    const auto& sorted = graph.sorted_functions();
    REQUIRE(sorted.size() == 0);
}

TEST_CASE("Access before build throws exception", "[function_dependency_graph]")
{
    const FunctionDependencyGraph graph;
    REQUIRE_THROWS_AS(graph.sorted_functions(), std::runtime_error);
}
