#ifndef CONCEPT_H
#define CONCEPT_H

#include <CongBaseVisitor.h>
#include <set>
#include <string>

#include "Debug.h"
#include "sema/SemaIdentifier.h"
#include "jinja2cpp/reflected_value.h"
#include "Utils.h"

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

protected:
    std::set<const Concept*> bases;
    opt<std::string> description = std::nullopt;
    static OperationTable operation_table;
};

struct Concept::DebugVisitor final : BaseDebugVisitor
{
    explicit DebugVisitor(const int tabsize)
        : BaseDebugVisitor(tabsize)
    {
    }

    void visit(const Concept& c) { visitConcept(c); }

    void visitConcept(const Concept& c) override;
};

template<>
struct jinja2::TypeReflection<Concept> : TypeReflected<Concept>
{
    static auto& GetAccessors()
    {
        static std::unordered_map<std::string, FieldAccessor> accessors = {
            {"name", [](const Concept& c) {return c.get_identifier(); }},
            {"full_name", [](const Concept& c) { return c.get_full_name(); }},
            {"description", [](const Concept& c) { return c.get_description().value_or(""); }},
            {"bases", [](const Concept& c)
            {
                ValuesList l{};
                l.reserve(c.get_bases().size());

                std::ranges::transform(c.get_bases(), std::back_inserter(l), [](const auto* b) { return Reflect(b); });

                return l;
            }},
            {"ns", [](const Concept& c)
            {
                const utils::FQIInfo info = utils::split_fully_qualified_identifier(c.get_full_name());
                ValuesList l(info.namespaces.begin(), info.namespaces.end());
                return l;
            }}
        };

        return accessors;
    }
};

#endif // CONCEPT_H
