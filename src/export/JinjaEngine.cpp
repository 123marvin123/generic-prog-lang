#include "export/JinjaEngine.h"

#include <utility>

JinjaEngine::JinjaEngine(Sema* sema, std::filesystem::path output_folder, std::filesystem::path template_folder,
                         const bool purge_output)
    : sema(sema), output_folder(std::move(output_folder)),
        template_folder(std::move(template_folder)), purge_output(purge_output)
{
    concept_graph.build_graph(sema);
    function_graph.build_graph(sema);
}

vec<std::filesystem::path> JinjaEngine::process(const LanguageMode lang)
const
{
    // Purge_output==false and directory exists cannot occur because that is checked by the CLI validator
    if (exists(output_folder) && purge_output)
    {
        for (const auto& entry : std::filesystem::directory_iterator(output_folder))
        {
            remove_all(entry.path());
        }
    }
    else
    {
        create_directory(output_folder);
    }

    switch (lang)
    {
    case LanguageMode::Cpp:
    {
        JinjaCppExport cpp_export{sema, template_folder, output_folder, concept_graph.sorted_concepts(),
                             function_graph.sorted_functions()};
        return cpp_export.process();
    }
    case LanguageMode::Python:
    {
        JinjaPythonExport python_export{sema, template_folder, output_folder, concept_graph.sorted_concepts(),
                                        function_graph.sorted_functions()};
        return python_export.process();
    }
    default:
        throw std::runtime_error("Unhandled language mode");
    }
}
