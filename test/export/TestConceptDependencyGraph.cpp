//
// Created by Marvin Haschker on 17.03.25.
//
#include <catch2/catch_test_macros.hpp>
#include <random>
#include "../Common.h"
#include "export/ConceptDependencyGraph.h"

struct ConceptDependencyGraphFixture {
    std::unique_ptr<Sema> sema;
    Sema* sema_ptr;

    ConceptDependencyGraphFixture() {
        sema = std::make_unique<Sema>(false);
        sema_ptr = sema.get();
    }

    ~ConceptDependencyGraphFixture() {
        sema.reset();
    }
};

TEST_CASE_METHOD(ConceptDependencyGraphFixture, "Linear dependencies are sorted correctly", "[concept_dependency_graph]")
{
    const auto conceptA = *Sema::create_concept(sema_ptr, "A");
    const auto conceptB = *Sema::create_concept(sema_ptr, "B", {{conceptA}});
    const auto conceptC = *Sema::create_concept(sema_ptr, "C", {{conceptB}});
    INFO(sema->to_string());

    ConceptDependencyGraph graph;
    graph.build_graph(sema_ptr);
    INFO("Built dependency graph");

    const auto& sorted = graph.sorted_concepts();

    REQUIRE(sorted.size() == 3);

    REQUIRE(sorted[0] == conceptA);
    REQUIRE(sorted[1] == conceptB);
    REQUIRE(sorted[2] == conceptC);
}

TEST_CASE_METHOD(ConceptDependencyGraphFixture, "Diamond dependency is sorted correctly", "[concept_dependency_graph]")
{
    // Create concepts with diamond dependency: A <- B, A <- C, B <- D, C <- D
    auto conceptA = *Sema::create_concept(sema_ptr, "A");
    auto conceptB = *Sema::create_concept(sema_ptr, "B", {{conceptA}});
    auto conceptC = *Sema::create_concept(sema_ptr, "C", {{conceptA}});
    auto conceptD = *Sema::create_concept(sema_ptr, "D", {{conceptB, conceptC}});
    INFO(sema->to_string());

    ConceptDependencyGraph graph;
    graph.build_graph(sema_ptr);
    INFO("Built dependency graph");

    const auto& sorted = graph.sorted_concepts();

    REQUIRE(sorted.size() == 4);

    // First should be A
    REQUIRE(sorted.front() == conceptA);

    // Last should be D
    REQUIRE(sorted.back() == conceptD);

    // Check B and C are in the middle (order between them doesn't matter)
    bool foundB = false, foundC = false;
    for (int i = 1; i < 3; i++) {
        if (sorted[i] == conceptB) foundB = true;
        if (sorted[i] == conceptC) foundC = true;
    }

    INFO("B and C should be in positions 1 and 2 (in any order)");
    REQUIRE(foundB);
    REQUIRE(foundC);
}

TEST_CASE_METHOD(ConceptDependencyGraphFixture, "Complex dependencies are sorted correctly", "[concept_dependency_graph]")
{
    auto* X = *Sema::create_concept(sema_ptr, "X");
    auto* Y = *Sema::create_concept(sema_ptr, "Y");
    auto* A = *Sema::create_concept(sema_ptr, "A", {{X}});
    auto* B = *Sema::create_concept(sema_ptr, "B", {{Y}});
    auto* C = *Sema::create_concept(sema_ptr, "C", {{A, B}});
    auto* D = *Sema::create_concept(sema_ptr, "D", {{B}});
    auto* E = *Sema::create_concept(sema_ptr, "E", {{A, D}});
    INFO(sema->to_string());

    std::vector<const Concept*> concepts = {X, Y, A, B, C, D, E};

    // Shuffle with a fixed seed for reproducibility
    std::mt19937 g(42); // Fixed seed NOLINT(*-msc51-cpp)
    std::ranges::shuffle(concepts, g);
    INFO("Shuffled concept order");

    ConceptDependencyGraph graph;
    graph.build_graph(concepts);
    INFO("Built dependency graph from shuffled concepts");

    const auto& sorted = graph.sorted_concepts();

    REQUIRE(sorted.size() == 7);

    // Check that the order satisfies dependencies
    std::unordered_map<const Concept*, size_t> positions;
    for (size_t i = 0; i < sorted.size(); i++) {
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

TEST_CASE_METHOD(ConceptDependencyGraphFixture, "Isolated concepts are sorted", "[concept_dependency_graph]")
{
    const auto A = *Sema::create_concept(sema_ptr, "A");
    const auto B = *Sema::create_concept(sema_ptr, "B");
    const auto C = *Sema::create_concept(sema_ptr, "C");
    INFO(sema->to_string());

    std::vector<const Concept*> concepts = {A, B, C};
    std::mt19937 g(12345); // Fixed seed NOLINT(*-msc51-cpp)
    std::ranges::shuffle(concepts, g);
    INFO("Shuffled isolated concepts");

    ConceptDependencyGraph graph;
    graph.build_graph(concepts);
    INFO("Built dependency graph");

    auto& sorted = graph.sorted_concepts();

    REQUIRE(sorted.size() == 3);

    INFO("A should be in sorted vector");
    REQUIRE(std::ranges::find(sorted, A) != sorted.end());
    INFO("B should be in sorted vector");
    REQUIRE(std::ranges::find(sorted, B) != sorted.end());
    INFO("C should be in sorted vector");
    REQUIRE(std::ranges::find(sorted, C) != sorted.end());
}

TEST_CASE_METHOD(ConceptDependencyGraphFixture, "Nested namespaces are handled correctly", "[concept_dependency_graph]")
{
    // Create concepts in nested namespaces
    const auto nsA = *Sema::create_namespace("NamespaceA", sema_ptr, sema_ptr);
    const auto nsB = *Sema::create_namespace("NamespaceB", sema_ptr, nsA);

    auto X = *Sema::create_concept(sema_ptr, "X");
    auto A = *Sema::create_concept(nsA, "A", {{X}});
    auto B = *Sema::create_concept(nsB, "B", {{A}});
    INFO(sema->to_string());

    ConceptDependencyGraph graph;
    graph.build_graph(sema_ptr);
    INFO("Built dependency graph with nested namespaces");

    const auto& sorted = graph.sorted_concepts();

    REQUIRE(sorted.size() == 3);

    REQUIRE(sorted[0] == X);
    REQUIRE(sorted[1] == A);
    REQUIRE(sorted[2] == B);
}

TEST_CASE_METHOD(ConceptDependencyGraphFixture, "Cyclic dependency throws exception", "[concept_dependency_graph]")
{
    // Create a cycle A <- B <- C <- A
    auto A = *Sema::create_concept(sema_ptr, "A");
    auto B = *Sema::create_concept(sema_ptr, "B", {{A}});
    auto C = *Sema::create_concept(sema_ptr, "C", {{B}});
    INFO(sema->to_string());

    // Should never happen in real life because it is caught by sema:
    A->extend_bases({C});
    INFO("Created cyclic dependency: A <- B <- C <- A");

    ConceptDependencyGraph graph;
    REQUIRE_THROWS_AS(graph.build_graph(sema_ptr), std::runtime_error);
}

TEST_CASE("Empty graph produces empty result", "[concept_dependency_graph]")
{
    const auto emptySema = std::make_unique<Sema>(false);
    INFO("Created empty Sema");

    ConceptDependencyGraph graph;
    graph.build_graph(emptySema.get());

    const auto& sorted = graph.sorted_concepts();
    REQUIRE(sorted.size() == 0);
}

TEST_CASE("Access before build throws exception", "[concept_dependency_graph]")
{
    const ConceptDependencyGraph graph;
    REQUIRE_THROWS_AS(graph.sorted_concepts(), std::runtime_error);
}