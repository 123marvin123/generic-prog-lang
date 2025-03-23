//
// Created by Marvin Haschker on 17.03.25.
//
#include "../Common.h"
#include <random>
#include <export/FunctionDependencyGraph.h>

TEST_GROUP(FunctionDependencyGraphGroup)
{
    DEFAULT_SEMA()
};

TEST(FunctionDependencyGraphGroup, TestLinearDependencies)
{
    auto boolean = *sema->find_concept("Boolean");

    // Create functions with simple linear dependencies: C -> B -> A
    const auto A = *Sema::create_function<ConcreteFunction>(sema_ptr, "A", sema_ptr, boolean);
    const auto B = *Sema::create_function<ConcreteFunction>(sema_ptr, "B", sema_ptr, boolean);
    const auto C = *Sema::create_function<ConcreteFunction>(sema_ptr, "C", sema_ptr, boolean);

    A->add_generic_implementation(BooleanExpression::create(sema_ptr, true));
    B->add_generic_implementation(CallExpression::create(sema_ptr, A, {}));
    C->add_generic_implementation(CallExpression::create(sema_ptr, B, {}));

    vec<Function*> functions = sema_ptr->functions();

    // Shuffle with a fixed seed for reproducibility
    std::mt19937 g(42); // Fixed seed NOLINT(*-msc51-cpp)
    std::ranges::shuffle(functions, g);

    FunctionDependencyGraph graph;
    graph.build_graph(functions);

    // Check the result
    const auto& sorted = graph.sorted_functions();

    // Verify we have exactly 3 functions
    CHECK_EQUAL(3, sorted.size());

    // The order should be: A, B, C
    CHECK_EQUAL(A, sorted[0]);
    CHECK_EQUAL(B, sorted[1]);
    CHECK_EQUAL(C, sorted[2]);
}

TEST(FunctionDependencyGraphGroup, TestComplexDependencies)
{
    auto boolean = *sema->find_concept("Boolean");

    auto* X = *Sema::create_function<ConcreteFunction>(sema_ptr, "X", sema_ptr, boolean);
    auto* Y = *Sema::create_function<ConcreteFunction>(sema_ptr, "Y", sema_ptr, boolean);

    auto* A = *Sema::create_function<ConcreteFunction>(sema_ptr, "A", sema_ptr, boolean);
    auto* B = *Sema::create_function<ConcreteFunction>(sema_ptr, "B", sema_ptr, boolean);
    auto* C = *Sema::create_function<ConcreteFunction>(sema_ptr, "C", sema_ptr, boolean);
    auto* D = *Sema::create_function<ConcreteFunction>(sema_ptr, "D", sema_ptr, boolean);
    auto* E = *Sema::create_function<ConcreteFunction>(sema_ptr, "E", sema_ptr, boolean);

    X->add_generic_implementation(BooleanExpression::create(sema_ptr, true));
    Y->add_generic_implementation(BooleanExpression::create(sema_ptr, true));

    A->add_generic_implementation(CallExpression::create(sema_ptr, X, {}));
    B->add_generic_implementation(CallExpression::create(sema_ptr, Y, {}));
    C->add_generic_implementation(ArithmeticExpression::create(
        sema_ptr,
        CallExpression::create(sema_ptr, A, {}),
        CallExpression::create(sema_ptr, B, {}),
        Operator::ADD
    ));
    D->add_generic_implementation(CallExpression::create(sema_ptr, B, {}));
    E->add_generic_implementation(ArithmeticExpression::create(
        sema_ptr,
        CallExpression::create(sema_ptr, A, {}),
        CallExpression::create(sema_ptr, D, {}),
        Operator::ADD
    ));

    std::vector<const Function*> functions = {X, Y, A, B, C, D, E};

    std::mt19937 g(42); // Fixed seed NOLINT(*-msc51-cpp)
    std::ranges::shuffle(functions, g);

    FunctionDependencyGraph graph;
    graph.build_graph(sema_ptr);

    const auto& sorted = graph.sorted_functions();
    CHECK_EQUAL(7, sorted.size());

    std::unordered_map<const Function*, size_t> positions;
    for (size_t i = 0; i < sorted.size(); i++) {
        positions[sorted[i]] = i;
    }

    CHECK_COMPARE(positions[X], <, positions[A]);
    CHECK_COMPARE(positions[Y], <, positions[B]);
    CHECK_COMPARE(positions[A], <, positions[C]);
    CHECK_COMPARE(positions[B], <, positions[C]);
    CHECK_COMPARE(positions[B], <, positions[D]);
    CHECK_COMPARE(positions[A], <, positions[E]);
    CHECK_COMPARE(positions[D], <, positions[E]);
}

TEST(FunctionDependencyGraphGroup, TestCyclicDependency)
{
    auto boolean = *sema->find_concept("Boolean");

    const auto A = *Sema::create_function<ConcreteFunction>(sema_ptr, "A", sema_ptr, boolean);
    const auto B = *Sema::create_function<ConcreteFunction>(sema_ptr, "B", sema_ptr, boolean);
    const auto C = *Sema::create_function<ConcreteFunction>(sema_ptr, "C", sema_ptr, boolean);

    // Create a cycle A -> B -> C -> A
    A->add_generic_implementation(CallExpression::create(sema_ptr, B, {}));
    B->add_generic_implementation(CallExpression::create(sema_ptr, C, {}));
    C->add_generic_implementation(CallExpression::create(sema_ptr, A, {}));

    FunctionDependencyGraph graph;

    CHECK_THROWS(std::runtime_error, graph.build_graph(sema_ptr));
}

TEST(FunctionDependencyGraphGroup, TestEmptyGraph)
{
    const auto emptySema = std::make_unique<Sema>(false);

    FunctionDependencyGraph graph;
    graph.build_graph(emptySema.get());

    const auto& sorted = graph.sorted_functions();
    CHECK_EQUAL(0, sorted.size());
}

TEST(FunctionDependencyGraphGroup, TestAccessBeforeBuild)
{
    const FunctionDependencyGraph graph;
    CHECK_THROWS(std::runtime_error, graph.sorted_functions());
}