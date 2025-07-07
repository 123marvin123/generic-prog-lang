#include "export/python/JinjaPythonExport.h"
#include "Utils.h"
#include "jinja2cpp/template_env.h"
#include "jinja2cpp/user_callable.h"
#include "sema/Expression.h"
#include "sema/RequiresStatement.h"

#include <filesystem>
#include <format>
#include <unordered_map>
#include <variant>

#include <fstream>
#include <iostream>
#include <ranges>

// Konstruktor: Templates laden und Funktionen registrieren
JinjaPythonExport::JinjaPythonExport(Sema* sema, const std::filesystem::path& template_folder,
                                     std::filesystem::path out, const vec<const Concept*>& c,
                                     const vec<const Function*>& f) : LangExport(sema, std::move(out), c, f)
{
    // Templates laden
    std::unordered_map<jinja2::Template*, std::filesystem::path> template_paths{{&function_tpl, "function.py.j2"},
                                                                                {&concept_tpl, "concept.py.j2"}};

    for (const auto& [tpl, p] : template_paths)
    {
        const auto res = get_template_env().LoadTemplate(p);
        if (!res.has_value())
        {
            throw std::runtime_error(
                std::format("Failed to load Python template {}: {}", p.string(), res.error().ToString()));
        }
        *tpl = res.value();
    }

    register_concept_functions();
    register_function_functions();
}

// Hilfsfunktion zum Erstellen von __init__.py
void JinjaPythonExport::ensure_python_module(const std::filesystem::path& dir_path)
{
    if (!exists(dir_path))
    {
        create_directories(dir_path);
    }
    if (const auto init_py = dir_path / "__init__.py"; !exists(init_py))
    {
        if (const std::ofstream init_file(init_py); !init_file)
        {
            const auto error_code = std::error_code(errno, std::generic_category());
            throw std::runtime_error(std::format("Failed to create __init__.py in {}: {}",
                                      dir_path.string(), error_code.message()));
        }
    }
}


vec<std::filesystem::path> JinjaPythonExport::process()
{
    output_files.clear();
    const std::filesystem::path base_output_folder = get_output_folder();

    // Sicherstellen, dass das Haupt-Ausgabeverzeichnis existiert und ein Modul ist
    ensure_python_module(base_output_folder);

    // Konzepte exportieren
    for (const Concept* c : get_concepts())
    {
        if(!c->export_enabled()) continue;

        std::filesystem::path current_path = base_output_folder;
        // Namespace-Ordner erstellen
        for (const auto& ns_part : c->get_namespace()->namespace_chain())
        {
            current_path /= utils::sanitize_python_identifier(ns_part->get_identifier());
            ensure_python_module(current_path);
        }

        std::filesystem::path out_path =
            current_path / std::format("{}.py", utils::sanitize_python_identifier(c->get_identifier()));

        jinja2::ValuesMap context{};
        context["concept"] = jinja2::Reflect(c);

        if (const auto& res = concept_tpl.RenderAsString(context))
        {
            std::ofstream out_file(out_path, std::ios::app);
            if (!out_file)
            {
                auto error_code = std::error_code(errno, std::generic_category());
                throw std::runtime_error(std::format("Failed to create {}: {}",
                                          out_path.filename().string(), error_code.message()));
            }
            out_file << res.value();
            output_files.push_back(out_path);
        }
        else
        {
            utils::print_jinja2_error(res.error(),
                                      std::format("Failed to render template for concept {}", c->get_full_name()));
        }
    }

    // Funktionen exportieren
    for (const Function* f : get_functions())
    {
        if(!f->export_enabled()) continue;

        std::filesystem::path current_path = base_output_folder;
        // Namespace-Ordner erstellen
        for (const auto& ns_part : f->get_namespace()->namespace_chain())
        {
            current_path /= utils::sanitize_python_identifier(ns_part->get_identifier());
            ensure_python_module(current_path);
        }

        std::filesystem::path out_path =
            current_path / std::format("{}.py", utils::sanitize_python_identifier(f->get_identifier()));

        jinja2::ValuesMap context{};
        context["function"] = jinja2::Reflect(FunctionView{f});

        std::unordered_set<std::variant<const Concept*, const Function*>> needed_files_set = {};

        if (std::holds_alternative<const Concept*>(f->get_result()))
            needed_files_set.emplace(std::get<const Concept*>(f->get_result()));
        else
            needed_files_set.emplace(f->get_namespace()->get_sema()->builtin_concept<Object>());

        for (FunctionParameter* param : f->get_parameters())
        {
            if (const auto cast = utils::dyn_cast<ConcreteFunctionParameter>(param); cast)
                needed_files_set.emplace(cast->get_type());
        }

        for (const auto& exp : f->requirements())
        {
            const auto& funs = exp.get_expression()->get_depending_functions();
            const auto& concepts = exp.get_expression()->get_depending_concepts();
            needed_files_set.insert(funs.begin(), funs.end());
            needed_files_set.insert(concepts.begin(), concepts.end());
        }

        for(const auto& impl : f->get_implementations())
        {
            if (!impl.get_language().empty() && impl.get_language() != "python") continue;

            const auto& funs = impl.get_expression()->get_depending_functions();
            const auto& concepts = impl.get_expression()->get_depending_concepts();
            needed_files_set.insert(funs.begin(), funs.end());
            needed_files_set.insert(concepts.begin(), concepts.end());

            if (impl.get_space_complexity())
            {
                const auto& funs = impl.get_space_complexity()->get_depending_functions();
                needed_files_set.insert(funs.begin(), funs.end());
            }
            if (impl.get_time_complexity())
            {
                const auto& funs = impl.get_time_complexity()->get_depending_functions();
                needed_files_set.insert(funs.begin(), funs.end());
            }
        }

        jinja2::ValuesMap file_map;

        // Convert the set to a jinja2::ValuesList:
        jinja2::ValuesList concept_list;
        jinja2::ValuesList function_list;

        for (const auto& v : needed_files_set)
        {
            if (std::holds_alternative<const Concept*>(v))
                concept_list.push_back(jinja2::Reflect(std::get<const Concept*>(v)));
            else if (std::holds_alternative<const Function*>(v))
                function_list.push_back(jinja2::Reflect(FunctionView{std::get<const Function*>(v)}));
            else
                throw std::runtime_error("Unknown sema type");
        }

        file_map["concepts"] = concept_list;
        file_map["functions"] = function_list;

        context["needed_files"] = file_map;

        if (const auto res = function_tpl.RenderAsString(context); res.has_value())
        {
            std::ofstream out_file(out_path, std::ios::app);
            if (!out_file)
            {
                auto error_code = std::error_code(errno, std::generic_category());
                throw std::runtime_error(std::format("Failed to create {}: {}",
                                          out_path.filename().string(), error_code.message()));
            }
            out_file << res.value();
            output_files.push_back(out_path);
        }
        else
        {
            utils::print_jinja2_error(res.error(),
                                      std::format("Failed to render template for function {}", f->get_full_name()));
        }
    }

    return output_files;
}

// Jinja-Funktionen für Konzepte registrieren
void JinjaPythonExport::register_concept_functions()
{
    LangExport::register_concept_functions(); // Basis-Funktionen (z.B. Namespace)

    const auto& sanitize = jinja2::MakeCallable(
        [](const std::string& id)
        {
            return utils::sanitize_python_identifier(id);
        }, jinja2::ArgInfo{"id", true});

    get_template_env().AddGlobal("sanitize", sanitize);

    // TODO:
    const auto& python_import_path =
        jinja2::MakeCallable([](const std::string& sema_object)
        {
            std::cout << sema_object << std::endl;
            return std::string("some_module.some_item");
        },
        jinja2::ArgInfo{"sema_object", true});

    get_template_env().AddGlobal("python_import_path", python_import_path);
}

void JinjaPythonExport::register_function_functions()
{
    LangExport::register_function_functions();

    const auto& sanitize = jinja2::MakeCallable(
        [](const std::string& id) { return utils::sanitize_python_identifier(id); }, jinja2::ArgInfo{"id", true});
    get_template_env().AddGlobal("sanitize", sanitize);

    const auto& func_reqs_python = MakeCallable(
        [this](const std::string& fqi)
        {
            const utils::FQIInfo info = utils::split_fully_qualified_identifier(fqi);
            const opt<Function*> result = utils::resolve_fully_qualified_identifier<Function>(info, get_sema());
            jinja2::ValuesList ret{};

            if (!result.has_value())
            {
                std::cerr << "Python: no result for " << fqi << "." << std::endl;
                return ret;
            }

            std::ranges::transform(result.value()->requirements(), std::back_inserter(ret),
                                   [](const RequiresStatement& exp)
                                   {
                                       jinja2::ValuesMap m{};
                                       m["name"] = utils::sanitize_python_identifier(exp.get_name().value_or(""));
                                       m["expression"] = exp.get_expression()->to_python();
                                       return m;
                                   });

            return ret;
        },
        jinja2::ArgInfo{"fqi", true});

    get_template_env().AddGlobal("function_requirements", func_reqs_python);

    const auto& func_generic_python = MakeCallable(
        [this](const std::string& fqi)
        {
            const utils::FQIInfo info = utils::split_fully_qualified_identifier(fqi);
            const opt<Function*> result = utils::resolve_fully_qualified_identifier<Function>(info, get_sema());
            jinja2::ValuesList ret{};

            if (!result.has_value())
            {
                std::cerr << "Python: no result for " << fqi << "." << std::endl;
                return ret;
            }

            for (const auto& impl : result.value()->get_implementations())
            {
                if (!impl.get_language().empty() && impl.get_language() != "python")
                    continue;

                jinja2::ValuesMap m;

                if (impl.get_language().empty())
                    m["expression"] = impl.get_expression()->to_python();
                else
                    m["expression"] = impl.get_native_implementation();

                m["time_complexity"] =
                    impl.get_time_complexity() ? impl.get_time_complexity()->to_python() : jinja2::EmptyValue{};
                m["space_complexity"] =
                    impl.get_space_complexity() ? impl.get_space_complexity()->to_python() : jinja2::EmptyValue{};
                ret.emplace_back(m);
            }

            return ret;
        },
        jinja2::ArgInfo{"fqi", true});

    get_template_env().AddGlobal("function_generic_impls", func_generic_python);
}
