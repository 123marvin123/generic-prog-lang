#include "export/ConceptDependencyGraph.h"
#include "sema/Sema.h"
#include "sema/Concept.h"
#include "sema/Namespace.h"

void ConceptDependencyGraph::build_graph(const Sema* sema)
{
    build_graph(collect_all_conepts(sema));
}

void ConceptDependencyGraph::build_graph(const std::vector<const Concept*>& concepts)
{
    clear();

    for (const auto* c : concepts) {
        if (!dependencies.contains(c)) {
            dependencies[c] = {};
        }

        for (const auto* base : c->get_bases()) {
            dependencies[c].insert(base);

            if (!dependencies.contains(base)) {
                dependencies[base] = {};
            }
        }
    }

    // Perform topological sort
    topological_sort();
    is_built = true;
}

std::vector<const Concept*> ConceptDependencyGraph::collect_all_conepts(const Sema* sema)
{
    std::vector<const Concept*> result;
    collect_concepts_from_namespace(sema, result);
    return result;
}

void ConceptDependencyGraph::collect_concepts_from_namespace(const Namespace* ns, std::vector<const Concept*>& result)
{
    for (const auto c : ns->concepts()) {
        result.push_back(c);
    }

    // Recurse into child namespaces
    for (const auto ns_item : ns->namespaces()) {
        collect_concepts_from_namespace(ns_item, result);
    }
}

void ConceptDependencyGraph::topological_sort()
{
    sortedConcepts.clear();
    std::set<const Concept*> visited;
    std::set<const Concept*> inProgress;

    for (const auto& c : dependencies | std::views::keys) {
        if (!visited.contains(c)) {
            visit_node(c, visited, inProgress);
        }
    }
}

void ConceptDependencyGraph::visit_node(const Concept* c, std::set<const Concept*>& visited,
    std::set<const Concept*>& inProgress)
{
    visited.insert(c);
    inProgress.insert(c);

    for (const auto* dep : dependencies[c]) {
        if (inProgress.contains(dep))
            throw SemaError(std::format("Circular dependency detected between concepts {} and {}", c->get_full_name(), dep->get_full_name()));

        if (!visited.contains(dep))
            visit_node(dep, visited, inProgress);
    }

    inProgress.erase(c);
    sortedConcepts.push_back(c);
}

void ConceptDependencyGraph::clear()
{
    is_built = false;
    sortedConcepts.clear();
    dependencies.clear();
}
