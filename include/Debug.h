#pragma once

#include <iostream>
#include <termcolor/termcolor.hpp>
#include <sstream>
#include "Decls.h"

struct BaseDebugVisitor
{
    virtual ~BaseDebugVisitor() = default;
    explicit BaseDebugVisitor(const int tabsize) : tabsize(tabsize) { ss << termcolor::colorize; }

    virtual void visitNamespace(const Namespace&)
    {
    };

    virtual void visitExpression(const Expression&)
    {
    };

    virtual void visitConcept(const Concept&)
    {
    };

    virtual void visitFunction(const Function&)
    {
    };

    virtual void visitFunctionParameter(const FunctionParameter&)
    {
    };

    std::string result() const { return ss.str(); }
    std::string spaces() const { return std::string(tabsize, ' '); }

protected:
    std::stringstream ss;
    int tabsize = 0;
};

template <typename T>
struct Introspection
{
    [[nodiscard]]
    std::string to_string(int tabsize = 0) const
    {
        const T* instance = static_cast<const T*>(this);
        typename T::DebugVisitor visit{tabsize};
        visit.visit(*instance);
        return visit.result();
    }
};
