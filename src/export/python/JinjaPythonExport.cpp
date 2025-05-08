//
// Created by Marvin Haschker on 24.03.25.
//
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
            std::cerr << "Failed to load Python template '" << p.string() << "': " << res.error().ToString()
                      << std::endl;
            throw std::runtime_error(std::format("Failed to load Python template {}", p.string()));
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
    const auto init_py = dir_path / "__init__.py";
    if (!exists(init_py))
    {
        std::ofstream init_file(init_py); // Leere Datei erstellen
        if (!init_file)
        {
            std::cerr << "Failed to create __init__.py in " << dir_path << std::endl;
            // Fehlerbehandlung nach Bedarf
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
            std::ofstream out_file(out_path);
            if (!out_file)
            {
                std::cerr << "Failed to open output file: " << out_path << std::endl;
                continue; // Oder Fehler werfen
            }
            out_file << res.value();
            output_files.push_back(out_path);
        }
        else
        {
            utils::print_jinja2_error(res.error(), std::format("Failed to render template for concept {}", c->get_full_name()));
        }
    }

    // Funktionen exportieren
    for (const Function* f : get_functions())
    {
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

        if (const auto res = function_tpl.RenderAsString(context); res.has_value())
        {
            std::ofstream out_file(out_path);
            if (!out_file)
            {
                std::cerr << "Failed to open output file: " << out_path << std::endl;
                continue; // Oder Fehler werfen
            }
            out_file << res.value();
            output_files.push_back(out_path);
        }
        else
        {
            utils::print_jinja2_error(res.error(), std::format("Failed to render template for function {}", f->get_full_name()));
        }
    }

    return output_files;
}

// Jinja-Funktionen für Konzepte registrieren
void JinjaPythonExport::register_concept_functions()
{
    LangExport::register_concept_functions(); // Basis-Funktionen (z.B. Namespace)

    // Python-spezifische Sanitize-Funktion
    const auto& sanitize = jinja2::MakeCallable(
        [](const std::string& id) { return utils::sanitize_python_identifier(id); }, jinja2::ArgInfo{"id", true});

    get_template_env().AddGlobal("sanitize", sanitize);

    const auto& python_import_path = jinja2::MakeCallable(
        [](const std::string& sema_object)
        {
            return jinja2::Value("some_module.some_item");
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
                std::cerr << "no result for " << fqi << "." << std::endl;
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
            jinja2::ValuesList ret{}; // Gibt eine Liste von reflektierten Expressions zurück

            if (!result.has_value())
            {
                std::cerr << "no result for " << fqi << "." << std::endl;
                return ret;
            }

            std::ranges::transform(result.value()->get_implementations(), std::back_inserter(ret),
                                   [](const GenericImplementation& impl)
                                   {
                                       jinja2::ValuesMap m;
                                       m["exp"] = impl.get_expression()->to_python();
                                       m["timecomplexity"] = impl.get_time_complexity()
                                           ? impl.get_time_complexity()->to_python()
                                           : jinja2::EmptyValue{};
                                       m["spacecomplexity"] = impl.get_space_complexity()
                                           ? impl.get_space_complexity()->to_python()
                                           : jinja2::EmptyValue{};

                                       return m;
                                   });

            return ret;
        },
        jinja2::ArgInfo{"fqi", true});

    get_template_env().AddGlobal("function_generic_impls", func_generic_python);
}
