//
// Created by Marvin Haschker on 12.03.25.
//

#ifndef FUNCTIONINSTANTIATOR_H
#define FUNCTIONINSTANTIATOR_H

#include <CongBaseVisitor.h>
#include <format>
#include <visitor/AbstractVisitor.h>

#include "Exception.h"
#include "Utils.h"
#include "sema/Function.h"
#include "sema/FunctionParameter.h"
#include "sema/Namespace.h"
#include "sema/Sema.h"

struct FunctionInstantiator
{
    FunctionInstantiator() = delete;

    static Function* instantiate(CongParser::FunctionStmntContext* ctx,
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

        std::any visitFunctionStmnt(CongParser::FunctionStmntContext* ctx) override;

        std::any visitParameterList(CongParser::ParameterListContext* ctx) override;

        std::any visitParameter(CongParser::ParameterContext* ctx) override;

        std::any visitQualifiedIdentifier(CongParser::QualifiedIdentifierContext* ctx) override;

        std::any visitConceptPlaceholder(CongParser::ConceptPlaceholderContext* ctx) override;

    private:
        Namespace* ns;
        bool declarationOnly = false;
        Function* current_function;
        vec<PlaceholderFunctionParameter*> placeholders; /* TODO: find proper ownership model so it doesn't leak memory */

        struct Placeholder
        {
            std::string name;
        };
    };
};

#endif // FUNCTIONINSTANTIATOR_H
