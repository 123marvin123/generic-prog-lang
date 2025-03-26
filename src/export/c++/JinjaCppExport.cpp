//
// Created by Marvin Haschker on 24.03.25.
//

#include "export/c++/JinjaCppExport.h"
#include "jinja2cpp/template.h"
#include "jinja2cpp/template_env.h"

std::string JinjaCppExport::process(const std::filesystem::path& interface_path)
{
    auto result = get_template_env().LoadTemplate("function.h.j2");
    if (!result.has_value())
    {
        std::cerr << result.error().ToString() << std::endl;
        throw std::runtime_error("Could not load template");
    }

    jinja2::Template tpl = result.value();
    const auto render_result = tpl.RenderAsString({});
    if (!render_result.has_value())
    {
        std::cerr << render_result.error().ToString() << std::endl;
        throw std::runtime_error("Could not render template");
    }

    return render_result.value();
}

void JinjaCppExport::register_concept_functions()
{
    LangExport::register_concept_functions();

}

void JinjaCppExport::register_function_functions()
{
    LangExport::register_function_functions();
}

