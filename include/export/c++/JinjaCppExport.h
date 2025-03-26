//
// Created by Marvin Haschker on 24.03.25.
//

#ifndef JINJACPPEXPORT_H
#define JINJACPPEXPORT_H

#include "../LangExport.h"

struct JinjaCppExport final : LangExport
{
    JinjaCppExport(Sema* sema, const std::filesystem::path& template_folder, std::filesystem::path out,
        const vec<const Concept*>& c,
        const vec<const Function*>& f) :
        LangExport(sema, std::move(out), c, f)
    {
        register_concept_functions();
        register_function_functions();

        std::unordered_map<jinja2::Template*, std::filesystem::path> function_opts{
            {&function_tpl, "function.hh.j2"},
            {&concept_tpl, "concept.hh.j2"}
        };

        for (const auto& [tpl, p] : function_opts)
        {
            const auto res = get_template_env().LoadTemplate(p);
            if (!res.has_value())
            {
                std::cerr << res.error().ToString() << std::endl;
                throw std::runtime_error(std::format("Could not load template {}", p.string()));
            }

            *tpl = res.value();
        }
    };

    vec<std::filesystem::path> process() override;
private:
    void register_concept_functions() override;
    void register_function_functions() override;

    jinja2::Template function_tpl;
    jinja2::Template concept_tpl;
};

#endif //JINJACPPEXPORT_H
