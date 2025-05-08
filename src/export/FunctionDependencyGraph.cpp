//
// Created by Marvin Haschker on 17.03.25.
//
#include "export/FunctionDependencyGraph.h"
#include "sema/Sema.h"
#include "sema/Function.h"
#include "sema/Expression.h"

void FunctionDependencyGraph::build_graph(const Sema* sema)
{
    const auto functions = collect_all_functions(sema);
    build_graph(functions);
}

void FunctionDependencyGraph::build_graph(const vec<Function*>& functions)
{
    clear();

    for (const auto* function : functions) {
        dependencies[function] = {};
    }

    for (const auto* function : functions) {
        analyze_function_dependencies(function);
    }

    topological_sort();
    is_built = true;
}

vec<Function*> FunctionDependencyGraph::collect_all_functions(const Sema* sema)
{
    vec<Function*> result;
    collect_functions_from_namespace(sema->get_sema(), result);
    return result;
}

void FunctionDependencyGraph::collect_functions_from_namespace(const Namespace* ns, vec<Function*>& result)
{
    for (const auto fun : ns->functions()) {
        result.push_back(fun);
    }

    for (const auto child_ns : ns->namespaces()) {
        collect_functions_from_namespace(child_ns, result);
    }
}

void FunctionDependencyGraph::analyze_function_dependencies(const Function* function)
{
    if (!function) return;

    std::set<const Function*> callees;

    for (const auto& impl : function->get_implementations()) {
        analyze_expression_dependencies(impl.get_expression().get(), callees);
    }

    for (const auto& req : function->requirements()) {
        analyze_expression_dependencies(req.get_expression().get(), callees);
    }

    dependencies[function].insert(callees.begin(), callees.end());
}

void FunctionDependencyGraph::analyze_expression_dependencies(const Expression* expr,
    std::set<const Function*>& callees)
{
    if (!expr) return;

    if (const auto* callExpr = utils::dyn_cast<CallExpression>(expr)) {
        callees.insert(callExpr->get_function());

        for (const auto& arg : callExpr->get_arguments()) {
            analyze_expression_dependencies(arg.get(), callees);
        }
    }

    else if (const auto* arithExpr = utils::dyn_cast<ArithmeticExpression>(expr)) {
        analyze_expression_dependencies(arithExpr->get_left().get(), callees);
        analyze_expression_dependencies(arithExpr->get_right().get(), callees);
    }
}

void FunctionDependencyGraph::topological_sort()
{
    sortedFunctions.clear();
    std::set<const Function*> visited;
    std::set<const Function*> inProgress;

    for (const auto& function : dependencies | std::views::keys) {
        if (!visited.contains(function)) {
            visit_node(function, visited, inProgress);
        }
    }

    //std::reverse(sortedFunctions.begin(), sortedFunctions.end());
}

void FunctionDependencyGraph::visit_node(const Function* f, std::set<const Function*>& visited,
    std::set<const Function*>& inProgress)
{
    visited.insert(f);
    inProgress.insert(f);

    for (const auto* dep : dependencies[f]) {
        if (inProgress.contains(dep)) {
            throw std::runtime_error("Circular dependency detected between functions");
        }

        if (!visited.contains(dep)) {
            visit_node(dep, visited, inProgress);
        }
    }

    inProgress.erase(f);
    sortedFunctions.push_back(f);
}

void FunctionDependencyGraph::clear()
{
    dependencies.clear();
    sortedFunctions.clear();
    is_built = false;
}
