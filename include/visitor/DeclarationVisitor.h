//
// Created by Marvin Haschker on 08.03.25.
//

#ifndef DECLARATIONVISITOR_H
#define DECLARATIONVISITOR_H

#include "instantiation/ConceptInstantiator.h"
#include "instantiation/FunctionInstantiator.h"
#include "visitor/AbstractVisitor.h"

#include "sema/Sema.h"

struct DeclarationVisitor final : AbstractVisitor
{
    enum class Mode { Concepts, Functions };

    explicit DeclarationVisitor(Sema* sema, const Mode mode, bool createNamespaces = true) : AbstractVisitor(sema, createNamespaces),
        mode(mode)
    {
    }

    std::any visitConceptDefinitionStmnt(CongParser::ConceptDefinitionStmntContext* context) override
    {
        if (mode != Mode::Concepts) return {};

        return ConceptInstantiator::instantiate(context, get_current_namespace(), true);
    }

    std::any visitFunctionStmnt(CongParser::FunctionStmntContext* context) override
    {
        if (mode != Mode::Functions) return {};

        return FunctionInstantiator::instantiate(context, get_current_namespace(), true);
    }
private:
    Mode mode;
};

#endif //DECLARATIONVISITOR_H
