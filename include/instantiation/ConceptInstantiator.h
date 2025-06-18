#pragma once

#include <utility>
#include <format>
#include <visitor/AbstractVisitor.h>

#include "CongParserBaseVisitor.h"
#include "Utils.h"
#include "sema/Concept.h"
#include "sema/Sema.h"
#include "sema/SemaError.h"

struct ConceptInstantiator
{
    ConceptInstantiator() = delete;

    static Concept* instantiate(CongParser::ConceptDefinitionStmntContext* ctx,
                                    Namespace* ns,
                                    bool declarationOnly = false);

private:
    struct Visitor final : AbstractVisitor
    {
        explicit Visitor(Namespace* ns, bool declOnly) : AbstractVisitor(ns->get_sema(), false),
                                                             ns(ns),
                                                             declarationOnly(declOnly)
        {
        }

        std::any visitConceptDefinitionStmnt(CongParser::ConceptDefinitionStmntContext* ctx) override;

        std::any visitConceptDefinitionBases(CongParser::ConceptDefinitionBasesContext* ctx) override;

    private:
        Namespace* ns;
        bool declarationOnly = false;
        Concept* current_concept;
    };
};