#include "sema/Concept.h"

#include <utility>
#include "sema/Namespace.h"

Concept::Concept(std::string name, Namespace* ns) :
    SemaIdentifier(std::move(name), ns)
{
    if (get_identifier().empty()) throw SemaError("Name must not be empty");
}

Concept::Concept(std::string name, Namespace* ns, const std::set<const Concept*>& bases) :
    Concept(std::move(name), ns)
{
    this->bases = bases;
}

void Concept::extend_bases(const std::set<const Concept*>& newBases)
{
    bases.insert(newBases.begin(), newBases.end());
}

bool Concept::is_base_of(const Concept* c) const
{
    return is_base_of(c, {this});
}

bool Concept::is_base_of(const Concept* c, std::set<const Concept*> visited) const
{
    // If we've already checked this concept in this path, we have a cycle
    if (visited.contains(c))
        return false;

    visited.insert(c);

    return std::ranges::any_of(c->bases,
                              [this, &visited](auto* i) { return this == i || this->is_base_of(i, visited); });
}

bool Concept::is_legal_base(const Concept* potential_base) const
{
    // A concept cannot be its own base
    if (this == potential_base)
        return false;

    // Check if adding the potential base would create a cycle
    // If potential_base already has this concept as its base (directly or indirectly),
    // then adding it would create a cycle
    return !potential_base->is_base_of(this);
}

bool Concept::matches_concept(const Concept* c) const
{
    return this == c || c->is_base_of(this);
}

Concept::OperationResult Concept::get_operation_result(const Operator op, const Concept* other) const
{
    if (!operation_table.contains(op)) return OperationResult::invalid();
    if (!operation_table[op].contains(this)) return OperationResult::invalid();
    if (!operation_table[op][this].contains(other)) return OperationResult::invalid();
    return operation_table[op][this][other];
}

void Concept::DebugVisitor::visitConcept(const Concept& c)
{
    ss << spaces() << termcolor::blue << "Concept" << termcolor::reset;
    ss << "(name: " << termcolor::green << c.get_identifier() << termcolor::reset << ")";
    const auto length = c.get_bases().size();

    if (!length) return;

    ss << " : " << termcolor::yellow;

    decltype(c.get_bases().size()) count = 0;
    for (auto it = c.get_bases().begin(); it != c.get_bases().end(); ++it, ++count)
    {
        ss << (*it)->get_identifier() << termcolor::reset;
        if (count + 1 < length)
            ss << ", " << termcolor::yellow;
    }
}