//
// Created by Marvin Haschker on 08.03.25.
//

#ifndef ABSTRACTVISITOR_H
#define ABSTRACTVISITOR_H

#include "CongBaseVisitor.h"
#include "sema/Sema.h"

struct AbstractVisitor : CongBaseVisitor
{
    explicit AbstractVisitor(Sema* sema, bool createNamespaces);

    [[nodiscard]] Sema* get_sema() const { return sema; }

    std::any visitNamespaceStmnt(CongParser::NamespaceStmntContext* context) override;

    [[nodiscard]] Namespace* get_current_namespace() const { return namespaces.top(); }

    std::any visit(antlr4::tree::ParseTree* tree) override
    {
        if (!tree) return std::nullopt;
        return tree->accept(this);
    }

protected:
    Sema* sema;
    std::stack<Namespace*> namespaces;
    bool createNamespaces = false;
};

#endif // ABSTRACTVISITOR_H
