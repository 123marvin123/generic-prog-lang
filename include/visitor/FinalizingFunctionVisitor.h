#pragma once

#include <format>

#include "AbstractVisitor.h"
#include "Utils.h"
#include "visitor/ExpressionVisitor.h"
#include "sema/GenericImplementation.h"
#include <unordered_map>

struct FinalizingFunctionVisitor final : AbstractVisitor
{
    explicit FinalizingFunctionVisitor(Sema* sema) : AbstractVisitor(sema, false) {}

    void createImplicitRequirements() const;

    std::any visitFunctionStmnt(CongParser::FunctionStmntContext* ctx) override;

    std::any visitFunctionDescription(CongParser::FunctionDescriptionContext* ctx) override;

    std::any visitFunctionExpRequires(CongParser::FunctionExpRequiresContext* ctx) override;

    std::any visitRequirementDetail(CongParser::RequirementDetailContext* ctx) override;

    std::any visitRequirementDetails(CongParser::RequirementDetailsContext* ctx) override;

    std::any visitGenericImplDetails(CongParser::GenericImplDetailsContext* ctx) override;

    std::any visitGenericImplDetail(CongParser::GenericImplDetailContext* ctx) override;

    std::any visitFunctionGenericImpl(CongParser::FunctionGenericImplContext* ctx) override;

private:
    Function* current_function;
};
