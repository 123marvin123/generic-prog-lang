//
// Created by Marvin Haschker on 24.03.25.
//

#ifndef JINJAPYTHONEXPORT_H
#define JINJAPYTHONEXPORT_H

#include "../LangExport.h"
#include "jinja2cpp/template.h"

struct JinjaPythonExport final : LangExport
{
    explicit JinjaPythonExport(Sema* sema, const std::filesystem::path& template_folder,
                                std::filesystem::path out,
                               const vec<const Concept*>& c,
                               const vec<const Function*>& f);

    vec<std::filesystem::path> process() override;

private:
    void register_concept_functions() override;
    void register_function_functions() override;
    static void ensure_python_module(const std::filesystem::path& dir_path);

    vec<std::filesystem::path> output_files;

    jinja2::Template function_tpl;
    jinja2::Template concept_tpl;
};

#endif //JINJAPYTHONEXPORT_H
