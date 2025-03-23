//
// Created by Marvin Haschker on 12.03.25.
//
#include "Utils.h"
#include "sema/Namespace.h"
#include "sema/Sema.h"

using namespace utils;

FQIInfo utils::split_fully_qualified_identifier(const std::string& fqi)
{
    const bool topLevel = fqi.starts_with("::");

    // Split fqi by "::"
    vec<std::string> namespaces;
    size_t start = topLevel ? 2 : 0;
    size_t end = fqi.find("::", start);
    while (end != std::string::npos)
    {
        namespaces.push_back(fqi.substr(start, end - start));
        start = end + 2; // Skip "::"
        end = fqi.find("::", start);
    }

    const std::string id = fqi.substr(start); // Add the remaining part
    return {namespaces, id, topLevel};
}

opt<Operator> utils::get_operator_for_string(std::string_view s)
{
    static std::map<std::string_view, Operator> op_map = {
        {"+", Operator::ADD},
        {"-", Operator::SUB},
        {"*", Operator::MUL},
        {"/", Operator::DIV},
        {"%", Operator::MOD}
    };

    if (op_map.contains(s))
        return op_map.at(s);
    return std::nullopt;
}

std::string_view utils::get_string_for_operator(Operator op)
{
    switch (op)
    {
    case Operator::ADD: return "+";
    case Operator::SUB: return "-";
    case Operator::MUL: return "*";
    case Operator::DIV: return "/";
    case Operator::MOD: return "%";
    default: throw std::runtime_error("Invalid operator");
    }
}

template <>
opt<Namespace*>
utils::resolve_fully_qualified_identifier<Namespace>(const FQIInfo& fqi, Namespace* curr_ns)
{
    if (!curr_ns) return std::nullopt;

    const auto& [namespaces, id, top_level] = fqi;

    opt<Namespace*> it_ns = top_level ? curr_ns->get_sema() : curr_ns;

    if (namespaces.empty()) {
        // No namespaces to traverse, find identifier directly
        if (it_ns && !id.empty())
            return (*it_ns)->find_namespace(id);
        return it_ns;
    }

    it_ns = (*it_ns)->find_namespace(*namespaces.begin()).value();
    if (!it_ns) return std::nullopt;

    for (auto it = namespaces.begin() + 1; it != namespaces.end(); ++it) {
        it_ns = it_ns ? it_ns.value()->find_namespace(*it) : std::nullopt;
        if (!it_ns) return std::nullopt;
    }

    // Find the final identifier
    return (it_ns && !id.empty()) ? (*it_ns)->find_namespace(id) : it_ns;
}

opt<Namespace*> resolve_namespace_for_identifier(const FQIInfo& fqi, Namespace* curr_ns)
{
    opt<Namespace*> target_namespace = curr_ns;

    if (fqi.namespaces.size() == 1)
    {
        // Special case for exactly one element
        target_namespace = fqi.topLevel
            ? curr_ns->get_sema()->find_namespace(*fqi.namespaces.begin())
            : curr_ns->find_namespace(*fqi.namespaces.begin());
    }
    else if (fqi.namespaces.size() > 1)
    {
        // Multiple namespaces - use recursive resolution
        target_namespace = resolve_fully_qualified_identifier<Namespace>(
            {vec<std::string>(fqi.namespaces.begin(), fqi.namespaces.end() - 1),
             fqi.namespaces.back(),
             fqi.topLevel},
            curr_ns);
    }

    return target_namespace;
}

template <>
opt<Concept*>
utils::resolve_fully_qualified_identifier<Concept>(const FQIInfo& fqi, Namespace* curr_ns)
{
    if (!curr_ns) return std::nullopt;

    if (!fqi.namespaces.empty())
    {
        if (const auto& target_namespace = resolve_namespace_for_identifier(fqi, curr_ns))
            return (*target_namespace)->find_concept(fqi.identifier);
        return std::nullopt;
    }

    return curr_ns->find_concept(fqi.identifier).or_else([&fqi,&curr_ns] { return curr_ns->get_parent() ? utils::resolve_fully_qualified_identifier<Concept>(fqi, curr_ns->get_parent()) : std::nullopt; });
}

template <>
opt<Function*>
utils::resolve_fully_qualified_identifier<Function>(const FQIInfo& fqi, Namespace* curr_ns)
{
    if (!curr_ns) return std::nullopt;

    if (!fqi.namespaces.empty())
    {
        if (const auto& target_namespace = resolve_namespace_for_identifier(fqi, curr_ns))
            return (*target_namespace)->find_function(fqi.identifier);
        return std::nullopt;
    }

    return curr_ns->find_function(fqi.identifier).or_else([&fqi,&curr_ns] { return curr_ns->get_parent() ? utils::resolve_fully_qualified_identifier<Function>(fqi, curr_ns->get_parent()) : std::nullopt; });
}
