//
// Created by Marvin Haschker on 24.03.25.
//

#include "export/c++/JinjaCppExport.h"

#include "../../../cmake-build-debug-local/_deps/jinja2cpp-src/include/jinja2cpp/value.h"
#include "jinja2cpp/template.h"
#include "jinja2cpp/template_env.h"

vec<std::filesystem::path> JinjaCppExport::process()
{
    vec<std::filesystem::path> output_files;
    output_files.reserve(get_concepts().size() + get_functions().size());
    for (const Concept* c : get_concepts())
    {
        std::filesystem::path out = get_output_folder() / std::format("{}.hh", c->get_identifier());
        if (const auto res = concept_tpl.RenderAsString({{"concept", jinja2::Reflect(c)}}); res.has_value())
        {
            const std::string& contents = res.value();

            std::ofstream out_file(out);
            if (!out_file)
            {
                std::cerr << "Failed to open output file: " << out << std::endl;
                throw std::runtime_error(std::format("Failed to open output file: {}", out.string()));
            }
            out_file << contents;

            output_files.push_back(out);
        }
        else
        {
            std::cerr << res.error().ToString() << std::endl;
            throw std::runtime_error(std::format("Failed to render template for concept {}", c->get_full_name()));
        }
    }

    for (const Function* f : get_functions())
    {
        std::filesystem::path out = get_output_folder() / std::format("{}.hh", f->get_identifier());

        std::unordered_set<const Concept*> needed_files_set = {};
        for (FunctionParameter* param : f->get_parameters()) {
            if (const auto cast = utils::dyn_cast<ConcreteFunctionParameter>(param); cast)
                needed_files_set.emplace(cast->get_type());
        }

        // Convert the set to a jinja2::ValuesList:
        jinja2::ValuesList needed_files;
        needed_files.reserve(needed_files_set.size());
        std::ranges::transform(needed_files_set, std::back_inserter(needed_files), [](const auto* p) {
            return jinja2::Reflect(*p);
        });

        if (const auto res = function_tpl.RenderAsString({
            {"fun", jinja2::Reflect(FunctionView{f})},
            {"needed_files", needed_files}}); res.has_value())
        {
            const std::string& contents = res.value();

            std::ofstream out_file(out);
            if (!out_file)
            {
                std::cerr << "Failed to open output file: " << out << std::endl;
                throw std::runtime_error(std::format("Failed to open output file: {}", out.string()));
            }
            out_file << contents;

            output_files.push_back(out);
        }
        else
        {
            std::cerr << res.error().ToString() << std::endl;
            throw std::runtime_error(std::format("Failed to render template for function {}", f->get_full_name()));
        }
    }

    return output_files;
}

void JinjaCppExport::register_concept_functions()
{
    LangExport::register_concept_functions();

}

void JinjaCppExport::register_function_functions()
{
    LangExport::register_function_functions();

}

