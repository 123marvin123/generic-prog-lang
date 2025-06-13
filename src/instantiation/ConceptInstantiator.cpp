#include "instantiation/ConceptInstantiator.h"

Concept* ConceptInstantiator::instantiate(CongParser::ConceptDefinitionStmntContext* ctx,
                                              Namespace* ns,
                                              bool declarationOnly)
{
    Visitor v{ns, declarationOnly};

    if (const std::any result = v.visit(ctx);
        result.has_value() && result.type() == typeid(Concept*))
        return std::any_cast<Concept*>(result);

    throw std::runtime_error("Could not instantiate concept");
}

std::any ConceptInstantiator::Visitor::visitConceptDefinitionStmnt(CongParser::ConceptDefinitionStmntContext* ctx)
{
    const std::string name = ctx->IDENTIFIER()->getText();

    if (declarationOnly)
    {
        if (const auto& res = Sema::create_concept(ns, name); res.has_value())
            return res.value();
        throw SemaError(std::format("Could not create concept {} because it already exist", name), ctx);
    }

    const auto c = ns->find_concept(name);
    if (!c) throw SemaError(std::format("Concept {} not found", name), ctx);

    current_concept = c.value();
    if (ctx->desc)
        current_concept->set_description(utils::cleanup_string_literal(ctx->desc->getText()));

    visit(ctx->conceptDefinitionBases());
    return current_concept;
}

std::any ConceptInstantiator::Visitor::visitConceptDefinitionBases(CongParser::ConceptDefinitionBasesContext* ctx)
{
    std::set<const Concept*> concepts{};

    for (const auto& fqiContext : ctx->qualifiedIdentifier())
    {
        const utils::FQIInfo& info = utils::split_fully_qualified_identifier(fqiContext->getText());

        if (opt<Concept*> c = utils::resolve_fully_qualified_identifier<Concept>(info, ns);
            c.has_value() && c.value())
            concepts.emplace(c.value());
        else
            throw SemaError(std::format("Could not find concept {}", fqiContext->getText()), ctx);
    }

    if (std::ranges::any_of(concepts, [this](const auto& i) { return current_concept == i; }))
        throw SemaError("A concept cannot extend itself", ctx);

    current_concept->extend_bases(concepts);

    return concepts;
}
