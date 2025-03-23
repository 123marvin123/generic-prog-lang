//
// Created by Marvin Haschker on 18.03.25.
//

#ifndef INJAENGINE_H
#define INJAENGINE_H

#include "sema/Sema.h"
#include "export/ConceptDependencyGraph.h"
#include "export/FunctionDependencyGraph.h"
#include <inja/inja.hpp>

struct InjaEngine
{
    explicit InjaEngine(Sema* sema);

    [[nodiscard]]
    const Sema* get_sema() const { return sema; }

private:

    enum class AffixType { PREFIX, POSTFIX };
    struct ConceptResolveResult
    {
        bool resolved;
        const inja::json result;

        // ReSharper disable once CppNonExplicitConversionOperator
        operator inja::json() const { return {{"resolved", resolved}, {"result", result}}; } // NOLINT(*-explicit-constructor)
    };

    static inja::json apply_affix(AffixType op, const inja::Arguments& a);

    void install_callbacks();

    inja::Environment env;
    Sema* sema;

    ConceptDependencyGraph concept_graph;
    FunctionDependencyGraph function_graph;
};

#endif //INJAENGINE_H
