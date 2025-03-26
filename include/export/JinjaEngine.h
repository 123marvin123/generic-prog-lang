//
// Created by Marvin Haschker on 18.03.25.
//

#ifndef JINJAENGINE_H
#define JINJAENGINE_H

#include <filesystem>

#include "sema/Sema.h"
#include "export/ConceptDependencyGraph.h"
#include "export/FunctionDependencyGraph.h"
#include <jinja2cpp/template.h>

#include "export/python/JinjaPythonExport.h"
#include "export/c++/JinjaCppExport.h"

enum class LanguageMode
{
    Cpp,
    Python
};

struct JinjaEngine final
{
    explicit JinjaEngine(Sema* sema);

    [[nodiscard]]
    const Sema* get_sema() const { return sema; }

    [[nodiscard]]
    std::string process(LanguageMode, const std::filesystem::path& interface_path) const;

private:
    Sema* sema;

    ConceptDependencyGraph concept_graph;
    FunctionDependencyGraph function_graph;
};

#endif //JINJAENGINE_H
