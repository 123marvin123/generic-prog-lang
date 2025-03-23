//
// Created by Marvin Haschker on 14.03.25.
//
#include "visitor/AbstractVisitor.h"

AbstractVisitor::AbstractVisitor(Sema* sema, const bool createNamespaces) :
    sema(sema), createNamespaces(createNamespaces)
{
    namespaces.emplace(sema);
}

std::any AbstractVisitor::visitNamespaceStmnt(CongParser::NamespaceStmntContext* context)
{
    Namespace* ns;
    if (createNamespaces)
    {
        if (const auto& res = Sema::create_namespace(context->IDENTIFIER()->getText(), sema, get_current_namespace()); res.has_value())
            ns = res.value();
        else throw std::runtime_error(std::format("Could not create namespace {} because it already exist", context->IDENTIFIER()->getText()));
    } else
        ns = get_current_namespace()->find_namespace(context->IDENTIFIER()->getText()).value();

    if (!ns)
        throw std::runtime_error("Could not find namespace");

    // Push the current namespace onto the stack
    namespaces.push(ns);

    // Visit the statements within the namespace
    std::any result = visitChildren(context);

    // Pop the namespace from the stack
    namespaces.pop();

    return result;
}
