//
// Created by Marvin Haschker on 12.03.25.
//

#ifndef UTILS_H
#define UTILS_H

#include <memory>
#include <optional>

#include <CLI/CLI.hpp>
#include "Decls.h"
#include "CongParser.h"

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
        Namespace*);

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

}


class DirValidator : public CLI::Validator
{
public:
    explicit DirValidator(const bool& allow_overwrite);
};

#endif // UTILS_H
