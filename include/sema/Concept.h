#ifndef CONCEPT_H
#define CONCEPT_H

#include <CongBaseVisitor.h>
#include <set>
#include <string>

#include "Debug.h"
#include "sema/SemaIdentifier.h"
#include "inja/json.hpp"

template <class T>
concept IsConcept = IsIdentifier<T> && requires(const T& t, std::string name, Namespace* ns)
{
    { T(name, ns) };
    { t.is_base_of(nullptr) } -> std::same_as<bool>;
    { t.matches_concept(nullptr) } -> std::same_as<bool>;
    { t.get_bases() } -> std::same_as<const std::set<const T*>&>;
    { t.get_full_name() } -> std::convertible_to<std::string_view>;
};

struct Concept final : SemaIdentifier, Introspection<Concept>
{
    // Operation result type for a given operator and two concepts
    struct OperationResult {
        const Concept* result_concept;
        bool is_valid;

        static OperationResult invalid() { return {nullptr, false}; }
        static OperationResult valid(const Concept* result) { return {result, true}; }
    };

    using OperationTable = std::map<Operator, std::map<const Concept*, std::map<const Concept*, OperationResult>>>;

    Concept(std::string, Namespace*);
    Concept(std::string, Namespace*, const std::set<const Concept*>&);

    void extend_bases(const std::set<const Concept*>&);

    [[nodiscard]]
    const std::set<const Concept*>& get_bases() const { return bases; }

    [[nodiscard]]
    bool is_base_of(const Concept*) const;

    bool is_base_of(const Concept* c, std::set<const Concept*> visited) const;

    bool is_legal_base(const Concept* potential_base) const;

    void set_description(std::string desc)
    {
        this->description = std::move(desc);
    }

    [[nodiscard]]
    opt<std::string_view> get_description() const
    {
        return description;
    }

    [[nodiscard]]
    bool matches_concept(const Concept*) const;

    OperationResult get_operation_result(Operator op, const Concept* other) const;

    static OperationTable& get_operation_table() { return operation_table; }

    struct DebugVisitor;

    explicit operator inja::json() const;

protected:
    std::set<const Concept*> bases;
    opt<std::string> description = std::nullopt;
    static OperationTable operation_table;
};

static_assert(IsConcept<Concept>, "Concept must satisfy the IsConcept concept");

struct Concept::DebugVisitor final : BaseDebugVisitor
{
    explicit DebugVisitor(const int tabsize)
        : BaseDebugVisitor(tabsize)
    {
    }

    void visit(const Concept& c) { visitConcept(c); }

    void visitConcept(const Concept& c) override;
};

#endif // CONCEPT_H
