//
// Created by Marvin Haschker on 24.03.25.
//

#ifndef LANGEXPORT_H
#define LANGEXPORT_H

#include "jinja2cpp/template_env.h"
#include "jinja2cpp/filesystem_handler.h"
#include "sema/Sema.h"
#include <filesystem>

#include "ConceptDependencyGraph.h"
#include "FunctionDependencyGraph.h"
#include "jinja2cpp/user_callable.h"

struct LangExport {
    virtual ~LangExport() = default;

    explicit LangExport(Sema* sema, const vec<const Concept*>& c, const vec<const Function*>& f) : sema(sema), concepts(c), functions(f)
    {
        if (!sema) throw std::runtime_error("Sema must not be null");

        setup_environment();

        std::ranges::transform(concepts, std::back_inserter(concept_ids), [](const Concept* c_it)
        {
           return c_it->get_full_name();
        });

        std::ranges::transform(functions, std::back_inserter(function_ids), [](const Function* f_it)
        {
            return f_it->get_full_name();
        });
    }

    [[nodiscard]]
    virtual std::string process(const std::filesystem::path&) = 0;

    [[nodiscard]]
    Sema* get_sema() const { return sema; }

    [[nodiscard]]
    jinja2::TemplateEnv& get_template_env() { return env; }

    [[nodiscard]]
    const vec<const Concept*>& get_concepts() const { return concepts; }

    [[nodiscard]]
    const jinja2::ValuesList& get_concept_names() const { return concept_ids; }

    [[nodiscard]]
    const vec<const Function*>& get_functions() const { return functions; }

    [[nodiscard]]
    const jinja2::ValuesList& get_function_names() const { return function_ids; }

protected:
    virtual void register_concept_functions();
    virtual void register_function_functions();

private:
    Sema* sema;
    jinja2::TemplateEnv env{};

    vec<const Concept*> concepts;
    vec<const Function*> functions;

    jinja2::ValuesList concept_ids;
    jinja2::ValuesList function_ids;

    void setup_environment();
};

#endif //LANGEXPORT_H
