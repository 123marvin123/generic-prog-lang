//
// Created by Marvin Haschker on 24.03.25.
//

#include "export/c++/JinjaCppExport.h"

#include <unordered_set>

#include "Utils.h"
#include "jinja2cpp/reflected_value.h"
#include "jinja2cpp/template.h"
#include "jinja2cpp/template_env.h"
#include "jinja2cpp/user_callable.h"
#include "jinja2cpp/value.h"
#include "sema/Expression.h"
#include "sema/GenericImplementation.h"

// Helper function to ensure a directory exists
void ensure_directory_exists(const std::filesystem::path& dir_path)
{
    if (!exists(dir_path))
    {
        if (!create_directories(dir_path))
        {
            const auto error_code = std::error_code(errno, std::generic_category());
            throw std::runtime_error(std::format("Failed to create directory {}: {}",
                                      dir_path.string(), error_code.message()));
        }
    }
}

void JinjaCppExport::create_function_declaration_file(const Function* f, jinja2::ValuesList& needed_files)
{
    std::filesystem::path current_path = get_output_folder();
    // Namespace-Ordner erstellen
    for (const auto& ns_part : f->get_namespace()->namespace_chain())
    {
        current_path /= utils::sanitize_cpp_identifier(ns_part->get_identifier());
        ensure_directory_exists(current_path);
    }

    std::filesystem::path out =
        current_path / std::format("{}_dec.hh", utils::sanitize_cpp_identifier(f->get_identifier()));

    if (const auto res = function_dec_tpl.RenderAsString(
            {{"fun", jinja2::Reflect(FunctionView{f})}, {"needed_files", needed_files}});
        res.has_value())
    {
        const std::string& contents = res.value();

        std::ofstream out_file(out);
        if (!out_file)
        {
            auto error_code = std::error_code(errno, std::generic_category());
            throw std::runtime_error(std::format("Failed to create {}: {}",
                                      out.filename().string(), error_code.message()));
        }
        out_file << contents;

        output_files.push_back(out);
    }
    else
    {
        utils::print_jinja2_error(
            res.error(), std::format("Failed to render template for function declaration {}", f->get_full_name()));
    }
}

void JinjaCppExport::create_function_definition_file(const Function* f, jinja2::ValuesList& needed_files)
{
    std::filesystem::path current_path = get_output_folder();
    // Namespace-Ordner erstellen
    for (const auto& ns_part : f->get_namespace()->namespace_chain())
    {
        current_path /= utils::sanitize_cpp_identifier(ns_part->get_identifier());
        ensure_directory_exists(current_path);
    }

    std::filesystem::path out =
        current_path / std::format("{}.hh", utils::sanitize_cpp_identifier(f->get_identifier()));

    if (const auto res =
            function_tpl.RenderAsString({{"fun", jinja2::Reflect(FunctionView{f})}, {"needed_files", needed_files}});
        res.has_value())
    {
        const std::string& contents = res.value();

        std::ofstream out_file(out);
        if (!out_file)
        {
            auto error_code = std::error_code(errno, std::generic_category());
            throw std::runtime_error(std::format("Failed to create {}: {}",
                                      out.filename().string(), error_code.message()));
        }
        out_file << contents;

        output_files.push_back(out);
    }
    else
    {
        utils::print_jinja2_error(
            res.error(), std::format("Failed to render template for function definition {}", f->get_full_name()));
    }
}

vec<std::filesystem::path> JinjaCppExport::process()
{
    output_files.clear(); // Clear at the beginning of processing

    for (const Concept* c : get_concepts())
    {
        std::filesystem::path current_path = get_output_folder();
        // Namespace-Ordner erstellen
        for (const auto& ns_part : c->get_namespace()->namespace_chain())
        {
            current_path /= utils::sanitize_cpp_identifier(ns_part->get_identifier());
            ensure_directory_exists(current_path);
        }

        std::filesystem::path out =
            current_path / std::format("{}.hh", utils::sanitize_cpp_identifier(c->get_identifier()));
        if (const auto res = concept_tpl.RenderAsString({{"concept", jinja2::Reflect(c)}}); res.has_value())
        {
            const std::string& contents = res.value();

            std::ofstream out_file(out);
            if (!out_file)
            {
                auto error_code = std::error_code(errno, std::generic_category());
                throw std::runtime_error(std::format("Failed to create {}: {}",
                                          out.filename().string(), error_code.message()));
            }
            out_file << contents;

            output_files.push_back(out);
        }
        else
        {
            utils::print_jinja2_error(res.error(),
                                      std::format("Failed to render template for concept {}", c->get_full_name()));
        }
    }

    for (const Function* f : get_functions())
    {
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
            needed_files_set.insert(funs.begin(), funs.end());
        }

        for(const auto& impl : f->get_implementations())
        {
            if (!impl.get_language().empty() && impl.get_language() != "c++") continue;

            const auto& funs = impl.get_expression()->get_depending_functions();
            needed_files_set.insert(funs.begin(), funs.end());

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

        /* TODO: handle usage of booleans, numbers, etc. for the
            corresponding cong::lang::core type */

        // Convert the set to a jinja2::ValuesList:
        jinja2::ValuesList needed_files;
        needed_files.reserve(needed_files_set.size());
        std::ranges::transform(needed_files_set, std::back_inserter(needed_files),
                               [](const auto& p)
                               {
                                   if (std::holds_alternative<const Concept*>(p))
                                       return jinja2::Reflect(std::get<const Concept*>(p));
                                   if (std::holds_alternative<const Function*>(p))
                                       return jinja2::Reflect(FunctionView{std::get<const Function*>(p)});
                                   throw std::runtime_error("Invalid sema type");
                               });

        create_function_declaration_file(f, needed_files);
        create_function_definition_file(f, needed_files);
    }

    return output_files;
}

void JinjaCppExport::register_concept_functions() { LangExport::register_concept_functions(); }

void JinjaCppExport::register_function_functions()
{
    LangExport::register_function_functions();

    const auto& func_reqs = jinja2::MakeCallable(
        [this](const std::string& fqi)
        {
            const utils::FQIInfo info = utils::split_fully_qualified_identifier(fqi);
            const opt<Function*> result = utils::resolve_fully_qualified_identifier<Function>(info, get_sema());
            jinja2::ValuesList ret{};

            if (!result.has_value())
            {
                std::cerr << "C++: no result for " << fqi << "." << std::endl;
                return ret;
            }

            std::ranges::transform(result.value()->requirements(), std::back_inserter(ret),
                                   [](const RequiresStatement& exp)
                                   {
                                       jinja2::ValuesMap m{};
                                       m["name"] = utils::sanitize_cpp_identifier(exp.get_name().value_or(""));
                                       m["expression"] = exp.get_expression()->to_cpp();
                                       return m;
                                   });

            return ret;
        },
        jinja2::ArgInfo{"fqi", true});

    const auto& func_generic = jinja2::MakeCallable(
        [this](const std::string& fqi)
        {
            const utils::FQIInfo info = utils::split_fully_qualified_identifier(fqi);
            const opt<Function*> result = utils::resolve_fully_qualified_identifier<Function>(info, get_sema());
            jinja2::ValuesList ret{};

            if (!result.has_value())
            {
                std::cerr << "C++: no result for " << fqi << "." << std::endl;
                return ret;
            }

            for (const auto& impl : result.value()->get_implementations())
            {
                if (!impl.get_language().empty() && impl.get_language() != "c++")
                    continue;

                jinja2::ValuesMap m;

                if (impl.get_language().empty())
                    m["expression"] = std::format("return {};", impl.get_expression()->to_cpp());
                else
                    m["expression"] = impl.get_native_implementation();

                m["time_complexity"] =
                    impl.get_time_complexity() ? impl.get_time_complexity()->to_cpp() : jinja2::EmptyValue{};
                m["space_complexity"] =
                    impl.get_space_complexity() ? impl.get_space_complexity()->to_cpp() : jinja2::EmptyValue{};
                ret.emplace_back(m);
            }


            return ret;
        },
        jinja2::ArgInfo{"fqi", true});

    const auto& sanitize = jinja2::MakeCallable(
        [this](const std::string& id) { return utils::sanitize_cpp_identifier(id); }, jinja2::ArgInfo{"id", true});

    get_template_env().AddGlobal("function_requirements", func_reqs);

    get_template_env().AddGlobal("function_generic_impls", func_generic);

    get_template_env().AddGlobal("sanitize", sanitize);
}
