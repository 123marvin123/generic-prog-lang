#pragma once

#include <CLI/CLI.hpp>
#include "Decls.h"
#include "jinja2cpp/error_info.h"

namespace utils
{
    struct FQIInfo
    {
        vec<std::string> namespaces;
        std::string identifier;
        bool topLevel;
    };

    constexpr auto ptr_transform = [](const auto& param) { return param.get(); };

    FQIInfo split_fully_qualified_identifier(const std::string& fqi);

    inline std::string cleanup_string_literal(const std::string& s)
    {
        // Check if s starts with " and ends with "
        if (s.size() < 2 || s.front() != '"' || s.back() != '"')
            return s;

        std::string copy = s;
        copy.erase(0, 1); // Remove the first "
        copy.erase(copy.size() - 1); // Remove the last "

        return copy;
    }

    template <class T>
    opt<std::add_pointer_t<T>> resolve_fully_qualified_identifier(const FQIInfo&,
        Namespace*, bool search_parent = true);

    template <class T>
    [[nodiscard]]
    T* dyn_cast(auto* a)
    {
        return dynamic_cast<T*>(a);
    }

    template <class T>
    [[nodiscard]]
    const T* dyn_cast(const auto* a)
    {
        return dynamic_cast<const T*>(a);
    }

    template <class T, class K>
    [[nodiscard]]
    s_ptr<T> dyn_ptr_cast(s_ptr<K> ptr)
    {
        return std::dynamic_pointer_cast<T>(std::move(ptr));
    }

    template <class T>
    [[nodiscard]]
    bool is(const auto* a) { return dyn_cast<T>(a) != nullptr; }

    template <class T, class K>
    [[nodiscard]]
    bool is(const s_ptr<K>& a) { return dyn_ptr_cast<T>(a) != nullptr; }

    opt<Operator> get_operator_for_string(std::string_view s);

    std::string_view get_string_for_operator(Operator op);

    std::string_view get_function_for_operator(const Sema* sema, Operator op);

    void print_jinja2_error(const jinja2::ErrorInfo& info, const std::string& msg = "");

    const std::map<std::string_view, std::string_view> cpp_keyword_map = {
        {"alignas", "alignas_"},
        {"alignof", "alignof_"},
        {"and", "and_"},
        {"and_eq", "and_eq_"},
        {"asm", "asm_"},
        {"atomic_cancel", "atomic_cancel_"}, // C++20 Transactional Memory TS
        {"atomic_commit", "atomic_commit_"}, // C++20 Transactional Memory TS
        {"atomic_noexcept", "atomic_noexcept_"}, // C++20 Transactional Memory TS
        {"auto", "auto_"},
        {"bitand", "bitand_"},
        {"bitor", "bitor_"},
        {"bool", "bool_"},
        {"break", "break_"},
        {"case", "case_"},
        {"catch", "catch_"},
        {"char", "char_"},
        {"char8_t", "char8_t_"}, // C++20
        {"char16_t", "char16_t_"},
        {"char32_t", "char32_t_"},
        {"class", "class_"},
        {"compl", "compl_"},
        {"concept", "concept_"}, // C++20
        {"const", "const_"},
        {"consteval", "consteval_"}, // C++20
        {"constexpr", "constexpr_"},
        {"constinit", "constinit_"}, // C++20
        {"const_cast", "const_cast_"},
        {"continue", "continue_"},
        {"co_await", "co_await_"}, // C++20
        {"co_return", "co_return_"}, // C++20
        {"co_yield", "co_yield_"}, // C++20
        {"decltype", "decltype_"},
        {"default", "default_"},
        {"delete", "delete_"},
        {"do", "do_"},
        {"double", "double_"},
        {"dynamic_cast", "dynamic_cast_"},
        {"else", "else_"},
        {"enum", "enum_"},
        {"explicit", "explicit_"},
        {"export", "export_"}, // Wieder eingeführt in C++20 (Modules)
        {"extern", "extern_"},
        {"false", "false_"},
        {"float", "float_"},
        {"for", "for_"},
        {"friend", "friend_"},
        {"goto", "goto_"},
        {"if", "if_"},
        {"inline", "inline_"},
        {"int", "int_"},
        {"long", "long_"},
        {"mutable", "mutable_"},
        {"namespace", "namespace_"},
        {"new", "new_"},
        {"noexcept", "noexcept_"},
        {"not", "not_"},
        {"not_eq", "not_eq_"},
        {"nullptr", "nullptr_"},
        {"operator", "operator_"},
        {"or", "or_"},
        {"or_eq", "or_eq_"},
        {"private", "private_"},
        {"protected", "protected_"},
        {"public", "public_"},
        {"reflexpr", "reflexpr_"}, // C++ TS for Reflection
        {"register", "register_"}, // Veraltet, aber reserviert
        {"reinterpret_cast", "reinterpret_cast_"},
        {"requires", "requires_"}, // C++20
        {"return", "return_"},
        {"short", "short_"},
        {"signed", "signed_"},
        {"sizeof", "sizeof_"},
        {"static", "static_"},
        {"static_assert", "static_assert_"},
        {"static_cast", "static_cast_"},
        {"struct", "struct_"},
        {"switch", "switch_"},
        {"synchronized", "synchronized_"}, // C++20 Transactional Memory TS
        {"template", "template_"},
        {"this", "this_"},
        {"thread_local", "thread_local_"},
        {"throw", "throw_"},
        {"true", "true_"},
        {"try", "try_"},
        {"typedef", "typedef_"},
        {"typeid", "typeid_"},
        {"typename", "typename_"},
        {"union", "union_"},
        {"unsigned", "unsigned_"},
        {"using", "using_"},
        {"virtual", "virtual_"},
        {"void", "void_"},
        {"volatile", "volatile_"},
        {"wchar_t", "wchar_t_"},
        {"while", "while_"},
        {"xor", "xor_"},
        {"xor_eq", "xor_eq_"}
        /* ... */
    };

    const std::map<std::string_view, std::string_view> python_keyword_map = {
        {"and", "and_"}, {"as", "as_"}, {"assert", "assert_"}, {"async", "async_"},
        {"await", "await_"}, {"break", "break_"}, {"class", "class_"}, {"continue", "continue_"},
        {"def", "def_"}, {"del", "del_"}, {"elif", "elif_"}, {"else", "else_"},
        {"except", "except_"}, {"False", "False_"}, {"finally", "finally_"}, {"for", "for_"},
        {"from", "from_"}, {"global", "global_"}, {"if", "if_"}, {"import", "import_"},
        {"in", "in_"}, {"is", "is_"}, {"lambda", "lambda_"}, {"None", "None_"},
        {"nonlocal", "nonlocal_"}, {"not", "not_"}, {"or", "or_"}, {"pass", "pass_"},
        {"raise", "raise_"}, {"return", "return_"}, {"True", "True_"}, {"try", "try_"},
        {"while", "while_"}, {"with", "with_"}, {"yield", "yield_"}
    };

    std::string sanitize_cpp_identifier(std::string_view identifier);
    std::string sanitize_python_identifier(std::string_view identifier);
}


class DirValidator : public CLI::Validator
{
public:
    explicit DirValidator(const bool& allow_overwrite);
};
