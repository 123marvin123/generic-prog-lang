//
// Created by Marvin Haschker on 18.03.25.
//

#ifndef JINJAENGINE_H
#define JINJAENGINE_H

#include "sema/Sema.h"
#include "export/ConceptDependencyGraph.h"
#include "export/FunctionDependencyGraph.h"
#include <jinja2cpp/template.h>

struct JinjaEngine
{
    explicit JinjaEngine(Sema* sema);

    [[nodiscard]]
    const Sema* get_sema() const { return sema; }

private:
    Sema* sema;

    ConceptDependencyGraph concept_graph;
    FunctionDependencyGraph function_graph;
};

#endif //INJAENGINE_H
