//
// Created by Marvin Haschker on 12.03.25.
//

#ifndef CONCEPTVISITOR_H
#define CONCEPTVISITOR_H

#include <utility>
#include <format>
#include <visitor/AbstractVisitor.h>

#include "CongBaseVisitor.h"
#include "Exception.h"
#include "Utils.h"
#include "sema/Concept.h"
#include "sema/Sema.h"

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
; // namespace instantiation

#endif // CONCEPTVISITOR_H
