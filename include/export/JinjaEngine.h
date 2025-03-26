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
    JinjaEngine(Sema* sema, std::filesystem::path output_folder, std::filesystem::path template_folder, bool purge_output);

    [[nodiscard]]
    const Sema* get_sema() const { return sema; }

    [[nodiscard]]
    vec<std::filesystem::path> process(LanguageMode) const;

private:
    Sema* sema;
    std::filesystem::path output_folder, template_folder;
    bool purge_output;

    ConceptDependencyGraph concept_graph;
    FunctionDependencyGraph function_graph;
};

#endif //JINJAENGINE_H
