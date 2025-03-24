//
// Created by Marvin Haschker on 18.03.25.
//
#include "export/JinjaEngine.h"

JinjaEngine::JinjaEngine(Sema* sema) : sema(sema)
{
    concept_graph.build_graph(sema);
    function_graph.build_graph(sema);
}

