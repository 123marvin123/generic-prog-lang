//
// Created by Marvin Haschker on 18.03.25.
//
#include "export/JinjaEngine.h"

JinjaEngine::JinjaEngine(Sema* sema) : sema(sema)
{
    concept_graph.build_graph(sema);
    function_graph.build_graph(sema);
}

std::string JinjaEngine::process(const LanguageMode lang, const std::filesystem::path& interface_path) const
{
    if (lang == LanguageMode::Cpp)
    {
        JinjaCppExport cpp_export{sema, concept_graph.sorted_concepts(), function_graph.sorted_functions()};
        return cpp_export.process(interface_path);
    }
    else if (lang == LanguageMode::Python)
    {
        JinjaPythonExport python_export{sema, concept_graph.sorted_concepts(), function_graph.sorted_functions()};
        return python_export.process(interface_path);
    }

    throw std::runtime_error("Unknown language mode");
}
