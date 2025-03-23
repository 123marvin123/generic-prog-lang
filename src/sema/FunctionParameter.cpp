//
// Created by Marvin Haschker on 11.03.25.
//
#include "sema/FunctionParameter.h"

#include <Utils.h>

void FunctionParameter::DebugVisitor::visitFunctionParameter(const FunctionParameter& p)
{
    ss << spaces() << termcolor::blue << p.get_identifier() << termcolor::reset << ": ";
}

void ConcreteFunctionParameter::DebugVisitor::visitFunctionParameter(const FunctionParameter& p)
{
    FunctionParameter::DebugVisitor::visitFunctionParameter(p);
    ss << termcolor::yellow << utils::dyn_cast<ConcreteFunctionParameter>(&p)->get_type()->get_identifier() << termcolor::reset;
}

void PlaceholderFunctionParameter::DebugVisitor::visitFunctionParameter(const FunctionParameter& p)
{
    FunctionParameter::DebugVisitor::visitFunctionParameter(p);
    ss << "<" << termcolor::yellow << utils::dyn_cast<PlaceholderFunctionParameter>(&p)->get_type_placeholder_name() <<
        termcolor::reset << ">";
}

void DependentFunctionParameter::DebugVisitor::visitFunctionParameter(const FunctionParameter& p)
{
    FunctionParameter::DebugVisitor::visitFunctionParameter(p);
    ss << termcolor::yellow << utils::dyn_cast<DependentFunctionParameter>(&p)->get_placeholder()->get_type_placeholder_name() <<
        termcolor::reset;
}
