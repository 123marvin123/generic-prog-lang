#pragma once

#include "SemaElement.h"
#include <string>
#include <memory>

#include "Decls.h"

struct Namespace;

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
    virtual std::string get_full_name() const;

private:
    const std::string identifier;
    const Namespace* ns;
};
