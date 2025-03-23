//
// Created by Marvin Haschker on 17.03.25.
//

#ifndef CONCEPTDEPENDENCYGRAPH_H
#define CONCEPTDEPENDENCYGRAPH_H

#include "Decls.h"
#include <unordered_map>
#include <vector>

struct ConceptDependencyGraph
{
    void build_graph(const Sema* sema);
    void build_graph(const std::vector<const Concept*>& concepts);
private:
    std::vector<const Concept*> collect_all_conepts(const Sema* sema);

    void collect_concepts_from_namespace(const Namespace* ns, std::vector<const Concept*>& result);

    void topological_sort();

    void visit_node(const Concept* c, std::set<const Concept*>& visited, std::set<const Concept*>& inProgress);

    void clear();

public:
    [[nodiscard]]
    const std::vector<const Concept*>& sorted_concepts() const {
        if (!is_built) throw std::runtime_error("Call build_graph(const Sema*) before accessing sorted_concepts()!");
        return sortedConcepts;
    }

private:
    std::unordered_map<const Concept*, std::set<const Concept*>> dependencies;
    std::vector<const Concept*> sortedConcepts;
    bool is_built = false;
};

#endif //CONCEPTDEPENDENCYGRAPH_H
