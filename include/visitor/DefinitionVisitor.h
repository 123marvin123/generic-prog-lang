//
// Created by Marvin Haschker on 10.03.25.
//

#ifndef DEFINITIONVISITOR_H
#define DEFINITIONVISITOR_H

#include "sema/Sema.h"
#include "visitor/AbstractVisitor.h"

struct DefinitionVisitor final : AbstractVisitor
{
    explicit DefinitionVisitor(Sema* sema) : AbstractVisitor(sema, false)
    {
    }

    std::any visitConceptDefinitionStmnt(CongParser::ConceptDefinitionStmntContext* context) override
    {
        return ConceptInstantiator::instantiate(context, get_current_namespace(), false);
    }

    std::any visitFunctionStmnt(CongParser::FunctionStmntContext* context) override
    {
        return FunctionInstantiator::instantiate(context, get_current_namespace(), false);
    }
};

#endif //DEFINITIONVISITOR_H
