//
// Created by Marvin Haschker on 09.03.25.
//

#ifndef SEMAIDENTIFIER_H
#define SEMAIDENTIFIER_H

#include "sema/SemaElement.h"
#include <string>
#include <memory>

#include "Decls.h"

struct Namespace;

template <class T>
concept IsIdentifier = requires(const T& t) {
    { t.get_identifier() } -> std::convertible_to<std::string_view>;
    { t.get_namespace() } -> std::convertible_to<const Namespace*>;
};

struct SemaIdentifier : SemaElement
{
    SemaIdentifier(std::string name, const Namespace* ns) : identifier(std::move(name)), ns(ns)
    {
    }

    [[nodiscard]] std::string_view get_identifier() const
    {
        return identifier;
    }

    [[nodiscard]] const Namespace* get_namespace() const
    {
        return ns;
    }


    [[nodiscard]]
    std::string get_full_name() const;

private:
    const std::string identifier;
    const Namespace* ns;
};

static_assert(IsIdentifier<SemaIdentifier>, "SemaIdentifier must satisfy the IsIdentifier concept");


#endif //SEMAIDENTIFIER_H
