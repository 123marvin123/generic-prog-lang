#pragma once

#include <Debug.h>
#include <string>
#include <optional>
#include <ranges>

#include "Concept.h"
#include "Function.h"
#include "Debug.h"
#include "SemaContext.h"
#include "SemaIdentifier.h"
#include "SemaError.h"
#include "Decls.h"

struct Namespace : SemaIdentifier, SemaContext<Namespace>, SemaContext<Concept>, SemaContext<Function>,
                   Introspection<Namespace>
{
    explicit Namespace(std::string name, Sema* sema,
                        Namespace* parent = nullptr) :
        SemaIdentifier(std::move(name), parent), parent(parent), sema(sema)
    {
        if (!is_global() && get_identifier().empty()) throw SemaError("Name must not be empty");
    }

    ~Namespace() override = default;

    [[nodiscard]]
    Namespace* get_parent() const
    {
        return parent;
    }

    void set_parent(Namespace* parent) { this->parent = parent; }

    [[nodiscard]]
    std::string get_full_name() const override;

    [[nodiscard]]
    bool is_global() const
    {
        return parent == nullptr;
    }

    [[nodiscard]]
    opt<Namespace*> find_namespace(std::string_view identifier) const;

    [[nodiscard]]
    opt<Concept*> find_concept(std::string_view identifier) const;

    [[nodiscard]]
    opt<Function*> find_function(std::string_view identifier) const;

    bool register_namespace(u_ptr<Namespace> ns);

    bool register_concept(u_ptr<Concept> c);

    bool register_function(u_ptr<Function> f);

    bool remove_namespace(const Namespace* ns) { return SemaContext<Namespace>::remove_element(ns); }

    bool remove_concept(const Concept* c) { return SemaContext<Concept>::remove_element(c); }

    bool remove_function(const Function* f) { return SemaContext<Function>::remove_element(f); }

    [[nodiscard]]
    vec<Concept*> concepts() const
    {
        vec<Concept*> result;
        result.reserve(SemaContext<Concept>::data.size());

        std::ranges::transform(SemaContext<Concept>::data, std::back_inserter(result), utils::ptr_transform);
        return result;
    }

    [[nodiscard]]
    vec<Namespace*> namespaces() const
    {
        vec<Namespace*> result;
        result.reserve(SemaContext<Namespace>::data.size());

        std::ranges::transform(SemaContext<Namespace>::data, std::back_inserter(result), utils::ptr_transform);
        return result;
    }

    [[nodiscard]]
    vec<Function*> functions() const
    {
        vec<Function*> result;
        result.reserve(SemaContext<Function>::data.size());

        std::ranges::transform(SemaContext<Function>::data, std::back_inserter(result), utils::ptr_transform);
        return result;
    }

    [[nodiscard]]
    vec<const Namespace*> namespace_chain() const
    {
        vec<const Namespace*> result;
        const Namespace* current = this;

        while (current)
        {
            result.push_back(current);
            current = current->get_parent();
        }

        std::reverse(result.begin(), result.end());
        return result;
    }

    [[nodiscard]]
    Sema* get_sema() const { return sema; }

    struct DebugVisitor;

protected:
    Namespace* parent;
    Sema* sema;
};

struct Namespace::DebugVisitor final : BaseDebugVisitor
{
    explicit DebugVisitor(const int tabsize)
        : BaseDebugVisitor(tabsize)
    {
    }

    void visit(const Namespace& ns) { visitNamespace(ns); }

    void visitNamespace(const Namespace& ns) override;
};

// DefaultNamespace is a special case of Namespace that has no parent and an empty name
struct DefaultNamespace : Namespace
{
    explicit DefaultNamespace(Sema* sema) : Namespace("", sema)
    {
    }
};
