#include "visitor/AbstractVisitor.h"

AbstractVisitor::AbstractVisitor(Sema* sema, const bool createNamespaces) :
    sema(sema), createNamespaces(createNamespaces)
{
    namespaces.emplace(sema);
}

std::any AbstractVisitor::visitNamespaceStmnt(CongParser::NamespaceStmntContext* context)
{
    opt<Namespace*> ns;
    if (createNamespaces)
    {
        if (const auto& res = Sema::create_namespace(context->IDENTIFIER()->getText(), sema, get_current_namespace());
            res.has_value())
            ns = res;
        else
            throw SemaError(
                std::format("Could not create namespace {} because it already exist", context->IDENTIFIER()->getText()),
                context);
    }
    else
    {
        ns = get_current_namespace()->find_namespace(context->IDENTIFIER()->getText());
    }

    if (!ns)
        throw SemaError("Could not find namespace", context);

    // Push the current namespace onto the stack
    namespaces.push(ns.value());

    // Visit the statements within the namespace
    std::any result = visitChildren(context);

    // Pop the namespace from the stack
    namespaces.pop();

    return result;
}
