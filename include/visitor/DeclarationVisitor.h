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
    explicit DeclarationVisitor(Sema* sema) : AbstractVisitor(sema, true)
    {
    }

    std::any visitConceptDefinitionStmnt(CongParser::ConceptDefinitionStmntContext* context) override
    {
        return ConceptInstantiator::instantiate(context, get_current_namespace(), true);
    }

    std::any visitFunctionStmnt(CongParser::FunctionStmntContext* context) override
    {
        return FunctionInstantiator::instantiate(context, get_current_namespace(), true);
    }
};

#endif //DECLARATIONVISITOR_H
