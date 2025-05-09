//
// Created by Marvin Haschker on 17.03.25.
//

#ifndef FUNCTIONDEPENDENCYGRAPH_H
#define FUNCTIONDEPENDENCYGRAPH_H

#include "Decls.h"
#include <unordered_map>
#include <vector>
#include <set>
#include "sema/GenericImplementation.h"

struct FunctionDependencyGraph
{
    void build_graph(const Sema* sema);
    void build_graph(const vec<Function*>& functions);

    [[nodiscard]]
    const vec<const Function*>& sorted_functions() const {
        if (!is_built) throw std::runtime_error("Call build_graph() before accessing sorted_functions()!");
        return sortedFunctions;
    }
private:
    vec<Function*> collect_all_functions(const Sema* sema);
    void collect_functions_from_namespace(const Namespace* ns, vec<Function*>& result);
    void analyze_function_dependencies(const Function* function);
    void analyze_expression_dependencies(const Expression* expr, std::set<const Function*>& callees);
    void topological_sort();
    void visit_node(const Function* f, std::set<const Function*>& visited, std::set<const Function*>& inProgress);
    void clear();

    std::unordered_map<const Function*, std::set<const Function*>> dependencies;
    vec<const Function*> sortedFunctions;
    bool is_built = false;
};

#endif //FUNCTIONDEPENDENCYGRAPH_H
