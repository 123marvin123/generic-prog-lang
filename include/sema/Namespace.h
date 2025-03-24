//
// Created by Marvin Haschker on 08.03.25.
//

#ifndef NAMESPACE_H
#define NAMESPACE_H

#include <Debug.h>
#include <set>
#include <string>
#include <optional>
#include <ranges>

#include "Concept.h"
#include "Function.h"
#include "Debug.h"
#include "sema/SemaContext.h"
#include "sema/SemaIdentifier.h"
#include "Decls.h"

template <typename T, typename C, typename F>
concept IsNamespace = IsIdentifier<T> && IsConcept<C> && IsFunction<F, C> && requires(T& t)
{
    { t.get_parent() } -> std::convertible_to<T*>;
    { t.is_global() } -> std::same_as<bool>;
    { t.get_full_name() } -> std::convertible_to<std::string_view>;

    { t.find_concept(std::string_view{}) } -> std::same_as<opt<C*>>;
    { t.find_function(std::string_view{}) } -> std::same_as<opt<F*>>;
    { t.find_namespace(std::string_view{}) } -> std::same_as<opt<T*>>;

    { t.register_namespace(std::make_unique<T>("", nullptr)) } -> std::same_as<bool>;
    { t.register_concept(std::make_unique<C>("", nullptr)) } -> std::same_as<bool>;
    { t.register_function(std::make_unique<F>("", nullptr)) } -> std::same_as<bool>;

    { t.concepts() } -> std::convertible_to<vec<C*>>;
    { t.namespaces() } -> std::convertible_to<vec<T*>>;
    { t.functions() } -> std::convertible_to<vec<F*>>;
};

struct Namespace : SemaIdentifier, SemaContext<Namespace>, SemaContext<Concept>, SemaContext<Function>,
                   Introspection<Namespace>
{
    explicit Namespace(std::string name, Sema* sema,
                        Namespace* parent = nullptr) :
        SemaIdentifier(std::move(name), parent), parent(parent), sema(sema)
    {
        if (!is_global() && get_identifier().empty()) throw std::runtime_error("Name must not be empty");
    }

    ~Namespace() override = default;

    [[nodiscard]]
    Namespace* get_parent() const
    {
        return parent;
    }

    void set_parent(Namespace* parent) { this->parent = parent; }

    [[nodiscard]]
    std::string get_full_name() const;

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
    Sema* get_sema() const { return sema; }

    struct DebugVisitor;

protected:
    Namespace* parent;
    Sema* sema;
};

static_assert(IsNamespace<Namespace, Concept, Function>, "Namespace must satisfy the IsNamespace concept");

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
#endif // NAMESPACE_H
