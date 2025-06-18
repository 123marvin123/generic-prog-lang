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
        {"%", Operator::MOD},
        {"^", Operator::POW}
    };

    if (op_map.contains(s))
        return op_map.at(s);
    return std::nullopt;
}

const Function* utils::get_function_for_operator(const Sema* sema, const Operator op)
{
    switch (op)
    {
    case Operator::ADD:
        return sema->builtin_function<Operator::ADD>();
    case Operator::SUB:
        return sema->builtin_function<Operator::SUB>();
    case Operator::MUL:
        return sema->builtin_function<Operator::MUL>();
    case Operator::DIV:
        return sema->builtin_function<Operator::DIV>();
    case Operator::MOD:
        return sema->builtin_function<Operator::MOD>();
    case Operator::POW:
        return sema->builtin_function<Operator::POW>();
    default:
        throw std::runtime_error("Invalid operator");
    }
}

void utils::print_jinja2_error(const jinja2::ErrorInfo& info, const std::string& msg)
{
    if (!msg.empty())
        std::cerr << msg << std::endl;

    std::cerr << "  Code: " << static_cast<int>(info.GetCode()) << "\n";
    std::cerr << "  File: " << info.GetErrorLocation().fileName << "\n";
    std::cerr << "  Line: " << info.GetErrorLocation().line << "\n";
    std::cerr << "  Column: " << info.GetErrorLocation().col << "\n";
    std::cerr << "  Description:\n" << info.GetLocationDescr() << "\n";
    std::cerr << "  Full Message:\n" << info << std::endl;
}


std::string_view utils::get_string_for_operator(const Operator op)
{
    switch (op)
    {
    case Operator::ADD: return "+";
    case Operator::SUB: return "-";
    case Operator::MUL: return "*";
    case Operator::DIV: return "/";
    case Operator::MOD: return "%";
    case Operator::POW: return "^";
    default: throw std::runtime_error("Invalid operator");
    }
}

template <>
opt<Namespace*>
utils::resolve_fully_qualified_identifier<Namespace>(const FQIInfo& fqi, Namespace* curr_ns,
                                                  bool search_parent)
{
    if (!curr_ns) return std::nullopt;

    const auto& [namespaces, id, top_level] = fqi;

    opt<Namespace*> current_search_ns = top_level ? curr_ns->get_sema() : curr_ns;

    for (const auto& ns_name : namespaces)
    {
        if (!current_search_ns) return std::nullopt;
        current_search_ns = (*current_search_ns)->find_namespace(ns_name);
    }

    if (current_search_ns && !id.empty())
    {
        if (const auto found_ns = (*current_search_ns)->find_namespace(id)) return found_ns;
    }
    else if (current_search_ns && id.empty())
    {
        return current_search_ns;
    }

    if (!top_level && search_parent && curr_ns->get_parent())
    {
        return resolve_fully_qualified_identifier<Namespace>(fqi, curr_ns->get_parent(), search_parent);
    }

    return std::nullopt;
}

opt<Namespace*> resolve_namespace_for_identifier(const FQIInfo& fqi, Namespace* curr_ns)
{
    if (fqi.namespaces.empty())
    {
        return curr_ns;
    }

    Namespace* search_start_ns = fqi.topLevel ? curr_ns->get_sema() : curr_ns;

    opt<Namespace*> target_namespace = search_start_ns;

    for (const auto& ns_name : fqi.namespaces)
    {
        if (!target_namespace) return std::nullopt;
        target_namespace = (*target_namespace)->find_namespace(ns_name);
    }
    return target_namespace;
}

template <class T>
opt<T*> resolve_identifier_in_namespace_or_parents(const std::string& identifier, Namespace* current_ns)
{
    if (!current_ns) return std::nullopt;

    opt<T*> found_item = std::nullopt;
    if constexpr (std::is_same_v<T, Concept>)
    {
        found_item = current_ns->find_concept(identifier);
    }
    else if constexpr (std::is_same_v<T, Function>)
    {
        found_item = current_ns->find_function(identifier);
    }

    if (found_item) return found_item;

    if (current_ns->get_parent())
    {
        return resolve_identifier_in_namespace_or_parents<T>(identifier, current_ns->get_parent());
    }

    return std::nullopt;
}

template <>
opt<Concept*>
utils::resolve_fully_qualified_identifier<Concept>(const FQIInfo& fqi, Namespace* curr_ns, bool search_parent)
{
    if (!curr_ns) return std::nullopt;

    if (fqi.topLevel)
    {
        Namespace* global_ns = curr_ns->get_sema();
        opt<Namespace*> target_ns = global_ns;
        for (const auto& ns_name : fqi.namespaces)
        {
            if (!target_ns) return std::nullopt;
            target_ns = (*target_ns)->find_namespace(ns_name);
        }
        if (target_ns)
            return (*target_ns)->find_concept(fqi.identifier);
        return std::nullopt;
    }

    opt<Namespace*> target_namespace = curr_ns;
    bool search_in_current_ns_first = true;

    if (!fqi.namespaces.empty())
    {
        opt<Namespace*> resolved_ns_from_current = curr_ns;
        for (const auto& ns_name : fqi.namespaces)
        {
            if (!resolved_ns_from_current) break;
            resolved_ns_from_current = (*resolved_ns_from_current)->find_namespace(ns_name);
        }

        if (resolved_ns_from_current)
        {
            target_namespace = resolved_ns_from_current;
            search_in_current_ns_first = false;
        }
        else if (search_parent && curr_ns->get_parent())
        {
            return resolve_fully_qualified_identifier<Concept>(fqi, curr_ns->get_parent(), true);
        }
        else
        {
            return std::nullopt;
        }
    }

    if (target_namespace)
    {
        if (search_in_current_ns_first)
        {
            return resolve_identifier_in_namespace_or_parents<Concept>(fqi.identifier, curr_ns);
        }

        return (*target_namespace)->find_concept(fqi.identifier);
    }

    return std::nullopt;
}


template <> 
opt<Function*>
utils::resolve_fully_qualified_identifier<Function>(const FQIInfo& fqi, Namespace* curr_ns, bool search_parent)
{
    if (!curr_ns) return std::nullopt;

    if (fqi.topLevel)
    {
        Namespace* global_ns = curr_ns->get_sema();
        opt<Namespace*> target_ns = global_ns;
        for (const auto& ns_name : fqi.namespaces)
        {
            if (!target_ns) return std::nullopt;
            target_ns = (*target_ns)->find_namespace(ns_name);
        }
        if (target_ns)
            return (*target_ns)->find_function(fqi.identifier);
        return std::nullopt;
    }

    opt<Namespace*> target_namespace = curr_ns;
    bool search_in_current_ns_first = true;

    if (!fqi.namespaces.empty())
    {
        opt<Namespace*> resolved_ns_from_current = curr_ns;
        for (const auto& ns_name : fqi.namespaces)
        {
            if (!resolved_ns_from_current) break;
            resolved_ns_from_current = (*resolved_ns_from_current)->find_namespace(ns_name);
        }

        if (resolved_ns_from_current)
        {
            target_namespace = resolved_ns_from_current;
            search_in_current_ns_first = false;
        }
        else if (search_parent && curr_ns->get_parent())
        {
            return resolve_fully_qualified_identifier<Function>(fqi, curr_ns->get_parent(), true);
        }
        else
        {
            return std::nullopt;
        }
    }

    if (target_namespace)
    {
        if (search_in_current_ns_first)
        {
            return resolve_identifier_in_namespace_or_parents<Function>(fqi.identifier, curr_ns);
        }

        return (*target_namespace)->find_function(fqi.identifier);
    }
    return std::nullopt;
}

DirValidator::DirValidator(const bool& allow_overwrite) : Validator("DIR")
{
    func_ = [&allow_overwrite](const std::string& path)
    {
        if (const std::filesystem::path dir_path(path); exists(dir_path))
        {
            if (!is_directory(dir_path))
            {
                return "Output path exists but is not a directory";
            }

            if (!is_empty(dir_path) && !allow_overwrite)
            {
                return "Output directory exists but is not empty. Use --purge to replace its contents";
            }
        }
        else
        {
            std::filesystem::path parent_path = dir_path.parent_path();
            if (!parent_path.empty() && !exists(parent_path))
            {
                return "Parent directory of output path does not exist";
            }
        }

        return ""; // Empty string means validation passed
    };
}

std::string utils::sanitize_cpp_identifier(const std::string_view identifier)
{
    if (const auto it = cpp_keyword_map.find(identifier);
        it != cpp_keyword_map.end())
    {
        return std::string(it->second);
    }

   return std::string(identifier);
}

std::string utils::sanitize_python_identifier(std::string_view identifier)
{
    if (const auto it = python_keyword_map.find(identifier);
        it != python_keyword_map.end())
    {
        return std::string(it->second);
    }

    return std::string(identifier);
}