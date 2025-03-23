//
// Created by Marvin Haschker on 17.03.25.
//
#include "../Common.h"
#include <random>
#include "export/ConceptDependencyGraph.h"

TEST_GROUP(ConceptDependencyGraphGroup)
{
    CUSTOM_SEMA(
        (sema = std::make_unique<Sema>(false); sema_ptr = sema.get();),
        (std::cout << "\n" << sema->to_string(4) << std::endl; sema.reset();)
    )
};

TEST(ConceptDependencyGraphGroup, TestLinearDependencies)
{
    const auto conceptA = *Sema::create_concept(sema_ptr, "A");
    const auto conceptB = *Sema::create_concept(sema_ptr, "B", {{conceptA}});
    const auto conceptC = *Sema::create_concept(sema_ptr, "C", {{conceptB}});

    ConceptDependencyGraph graph;
    graph.build_graph(sema_ptr);

    const auto& sorted = graph.sorted_concepts();

    CHECK_EQUAL(3, sorted.size());

    CHECK_EQUAL(conceptA, sorted[0]);
    CHECK_EQUAL(conceptB, sorted[1]);
    CHECK_EQUAL(conceptC, sorted[2]);
}

TEST(ConceptDependencyGraphGroup, TestDiamondDependency)
{
    // Create concepts with diamond dependency: A <- B, A <- C, B <- D, C <- D
    auto conceptA = *Sema::create_concept(sema_ptr, "A");
    auto conceptB = *Sema::create_concept(sema_ptr, "B", {{conceptA}});
    auto conceptC = *Sema::create_concept(sema_ptr, "C", {{conceptA}});
    auto conceptD = *Sema::create_concept(sema_ptr, "D", {{conceptB, conceptC}});

    ConceptDependencyGraph graph;
    graph.build_graph(sema_ptr);

    const auto& sorted = graph.sorted_concepts();

    CHECK_EQUAL(4, sorted.size());

    // First should be A
    CHECK_EQUAL(conceptA, sorted.front());

    // Last should be D
    CHECK_EQUAL(conceptD, sorted.back());

    // Check B and C are in the middle (order between them doesn't matter)
    bool foundB = false, foundC = false;
    for (int i = 1; i < 3; i++) {
        if (sorted[i] == conceptB) foundB = true;
        if (sorted[i] == conceptC) foundC = true;
    }

    CHECK_TRUE(foundB);
    CHECK_TRUE(foundC);
}

TEST(ConceptDependencyGraphGroup, ComplexDependencies)
{
    auto* X = *Sema::create_concept(sema_ptr, "X");
    auto* Y = *Sema::create_concept(sema_ptr, "Y");
    auto* A = *Sema::create_concept(sema_ptr, "A", {{X}});
    auto* B = *Sema::create_concept(sema_ptr, "B", {{Y}});
    auto* C = *Sema::create_concept(sema_ptr, "C", {{A, B}});
    auto* D = *Sema::create_concept(sema_ptr, "D", {{B}});
    auto* E = *Sema::create_concept(sema_ptr, "E", {{A, D}});

    std::vector<const Concept*> concepts = {X, Y, A, B, C, D, E};

    // Shuffle with a fixed seed for reproducibility
    std::mt19937 g(42); // Fixed seed NOLINT(*-msc51-cpp)
    std::ranges::shuffle(concepts, g);

    ConceptDependencyGraph graph;
    graph.build_graph(concepts);

    const auto& sorted = graph.sorted_concepts();

    CHECK_EQUAL(7, sorted.size());

    // Check that the order satisfies dependencies
    // X and Y have no dependencies and can be in any order
    // A depends on X
    // B depends on Y
    // C depends on A and B
    // D depends on B
    // E depends on A and D

    std::unordered_map<const Concept*, size_t> positions;
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

TEST(ConceptDependencyGraphGroup, TestIsolatedConcepts)
{
    const auto A = *Sema::create_concept(sema_ptr, "A");
    const auto B = *Sema::create_concept(sema_ptr, "B");
    const auto C = *Sema::create_concept(sema_ptr, "C");

    std::vector<const Concept*> concepts = {A, B, C};
    std::mt19937 g(12345); // Fixed seed NOLINT(*-msc51-cpp)
    std::ranges::shuffle(concepts, g);

    ConceptDependencyGraph graph;
    graph.build_graph(concepts);

    auto& sorted = graph.sorted_concepts();

    CHECK_EQUAL(3, sorted.size());

    CHECK_TRUE_TEXT(std::ranges::find(sorted, A) != sorted.end(), "A should be in sorted vec");
    CHECK_TRUE_TEXT(std::ranges::find(sorted, B) != sorted.end(), "B should be in sorted vec");
    CHECK_TRUE_TEXT(std::ranges::find(sorted, C) != sorted.end(), "C should be in sorted vec");
}


TEST(ConceptDependencyGraphGroup, TestNestedNamespaces)
{
    // Create concepts in nested namespaces
    const auto nsA = *Sema::create_namespace("NamespaceA", sema_ptr, sema_ptr);
    const auto nsB = *Sema::create_namespace("NamespaceB", sema_ptr, nsA);

    auto X = *Sema::create_concept(sema_ptr, "X");
    auto A = *Sema::create_concept(nsA, "A", {{X}});
    auto B = *Sema::create_concept(nsB, "B", {{A}});

    ConceptDependencyGraph graph;
    graph.build_graph(sema_ptr);

    const auto& sorted = graph.sorted_concepts();

    CHECK_EQUAL(3, sorted.size());

    CHECK_EQUAL(X, sorted[0]);
    CHECK_EQUAL(A, sorted[1]);
    CHECK_EQUAL(B, sorted[2]);
}

TEST(ConceptDependencyGraphGroup, TestCyclicDependency)
{
    // Create a cycle A <- B <- C <- A
    auto A = *Sema::create_concept(sema_ptr, "A");
    auto B = *Sema::create_concept(sema_ptr, "B", {{A}});
    auto C = *Sema::create_concept(sema_ptr, "C", {{B}});

    // Should never happen in real life because it is caught by sema:
    A->extend_bases({C});

    ConceptDependencyGraph graph;
    CHECK_THROWS(std::runtime_error, graph.build_graph(sema_ptr));
}

TEST(ConceptDependencyGraphGroup, TestEmptyGraph)
{
    // Create a new empty Sema just for this test to ensure no concepts
    const auto emptySema = std::make_unique<Sema>(false);

    ConceptDependencyGraph graph;
    graph.build_graph(emptySema.get());

    const auto& sorted = graph.sorted_concepts();
    CHECK_EQUAL(0, sorted.size());
}

TEST(ConceptDependencyGraphGroup, TestAccessBeforeBuild)
{
    // Verify that accessing sorted_concepts before building throws
    ConceptDependencyGraph graph;
    CHECK_THROWS(std::runtime_error, graph.sorted_concepts());
}