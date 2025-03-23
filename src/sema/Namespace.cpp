//
// Created by Marvin Haschker on 08.03.25.
//

#include "sema/Namespace.h"
#include "sema/Concept.h"
#include "sema/Function.h"

std::string Namespace::get_full_name() const
{
    auto identifier = std::string{get_identifier()};
    if (parent)
        return parent->get_full_name() + "::" + identifier;

    return identifier;
}

opt<Namespace*> Namespace::find_namespace(std::string_view identifier) const
{
    return SemaContext<Namespace>::find([identifier](const auto& a)
    {
        return identifier == a->get_identifier();
    });
}

opt<Concept*> Namespace::find_concept(std::string_view identifier) const
{
    return SemaContext<Concept>::find([identifier](const auto& a)
    {
        return identifier == a->get_identifier();
    });
}

opt<Function*> Namespace::find_function(std::string_view identifier) const
{
    return SemaContext<Function>::find([identifier](const auto& a)
    {
        return identifier == a->get_identifier();
    });
}

bool Namespace::register_namespace(u_ptr<Namespace> ns)
{
    if (find_namespace(ns->get_identifier()).has_value()) return false;

    SemaContext<Namespace>::register_element(std::move(ns));
    return true;
}

bool Namespace::register_concept(u_ptr<Concept> c)
{
    if (find_concept(c->get_identifier()).has_value()) return false;

    SemaContext<Concept>::register_element(std::move(c));
    return true;
}

bool Namespace::register_function(u_ptr<Function> f)
{
    if (find_function(f->get_identifier()).has_value()) return false;

    SemaContext<Function>::register_element(std::move(f));
    return true;
}

void Namespace::DebugVisitor::visitNamespace(const Namespace& ns)
{
    ss << spaces() << termcolor::blue << "Namespace" << termcolor::reset;
    ss << "(name: " << termcolor::green << ns.get_identifier() << termcolor::reset << ", toplevel: " << termcolor::red
        << std::boolalpha << ns.is_global() << std::noboolalpha << termcolor::reset << ")\n";

    for (const auto& concepts = ns.concepts();
         const auto& c : concepts)
    {
        ss << c->to_string(tabsize + 2) << "\n";
    }

    for (const auto& functions = ns.functions();
         const auto& f : functions)
    {
        ss << f->to_string(tabsize + 2) << "\n";
    }

    for (const auto& namespaces = ns.namespaces();
         const auto& n : namespaces)
    {
        ss << n->to_string(tabsize + 2) << "\n";
    }

    ss << termcolor::reset;
}
