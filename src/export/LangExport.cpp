#include "export/LangExport.h"

void LangExport::register_concept_functions()
{
    get_template_env().AddGlobal("get_concept_ids", jinja2::MakeCallable(
                                     [this]
                                     {
                                         return get_concept_names();
                                     })
    );

    get_template_env().AddGlobal("get_concept", MakeCallable(
    [this](const std::string& fqi)
    {
        const utils::FQIInfo info = utils::split_fully_qualified_identifier(fqi);
        const opt<Concept*> res = utils::resolve_fully_qualified_identifier<Concept>(info, get_sema());
        if (!res.has_value())
            return jinja2::Value(jinja2::EmptyValue{});

        return jinja2::Reflect(*res.value());
    }, jinja2::ArgInfo{"fqi", true}
    ));
}

void LangExport::register_function_functions()
{
    get_template_env().AddGlobal("get_function_ids", jinja2::MakeCallable(
                                     [this]
                                     {
                                         return get_function_names();
                                     })
    );

    get_template_env().AddGlobal("get_function", jinja2::MakeCallable(
        [this](const std::string& fqi)
        {
            const utils::FQIInfo info = utils::split_fully_qualified_identifier(fqi);
            const opt<Function*> result = utils::resolve_fully_qualified_identifier<Function>(info, get_sema());
            if (!result.has_value())
                return jinja2::Value(jinja2::EmptyValue{});

            return jinja2::Reflect(FunctionView{result.value()});
        }, jinja2::ArgInfo{"fqi", true}
        ));
}

void LangExport::setup_environment()
{
    env.AddFilesystemHandler(std::string(), std::make_unique<jinja2::RealFileSystem>("templates"));
    env.GetSettings().lstripBlocks = true;
    env.GetSettings().trimBlocks = true;
    env.GetSettings().extensions.Do = true;

    env.AddGlobal("prefix", MakeCallable(
                      [](const std::string& str1, const std::string& str2)
                      {
                          return std::format("{}{}", str2, str1);
                      },
                      jinja2::ArgInfo{"str1", true},
                      jinja2::ArgInfo{"str2", true}));

    env.AddGlobal("prefix_concept", jinja2::MakeCallable(
        [this](const std::string& fqi, const std::string& prefix)
        {
            auto fqi_info = utils::split_fully_qualified_identifier(fqi);
            if (const auto& res = utils::resolve_fully_qualified_identifier<Concept>(fqi_info, get_sema()); res.has_value())
            {
                std::stringstream ss;
                ss << "";
                std::string separator;
                for (const auto& ns : (*res)->get_namespace()->namespace_chain())
                {
                    ss << separator << ns->get_identifier();
                    separator = "::";
                }

                if (!(*res)->get_namespace()->namespace_chain().empty())
                    ss << "::";
                ss << prefix << (*res)->get_identifier();
                return ss.str();
            }

            throw std::runtime_error(std::format("FQI {} not found", fqi));
        },
        jinja2::ArgInfo{"fqi", true},
        jinja2::ArgInfo{"prefix", true}));
}
