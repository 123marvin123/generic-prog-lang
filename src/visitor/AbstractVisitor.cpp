#include "visitor/AbstractVisitor.h"

AbstractVisitor::AbstractVisitor(Sema* sema, const bool createNamespaces) :
    sema(sema), createNamespaces(createNamespaces)
{
    namespaces.emplace(sema);
}

std::any AbstractVisitor::visitNamespaceStmnt(CongParser::NamespaceStmntContext* context)
{
    opt<Namespace*> ns;
    if (const auto& the_ns = get_current_namespace()->find_namespace(context->IDENTIFIER()->getText());
        the_ns.has_value())
    {
        ns = the_ns;
    }
    else if (createNamespaces)
    {
        if (const auto& res = Sema::create_namespace(context->IDENTIFIER()->getText(), sema, get_current_namespace());
            res.has_value())
        {
            ns = res;
        }
        else
            throw SemaError(
                std::format("Could not create namespace {}", context->IDENTIFIER()->getText()),
                context);
    }

    if (!ns)
        throw SemaError(std::format("Could not find namespace {}", context->IDENTIFIER()->getText()), context);

    // Push the current namespace onto the stack
    namespaces.push(ns.value());

    // Visit the statements within the namespace
    std::any result = visitChildren(context);

    // Pop the namespace from the stack
    namespaces.pop();

    return result;
}
