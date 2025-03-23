//
// Created by Marvin Haschker on 18.03.25.
//
#include "export/InjaEngine.h"

InjaEngine::InjaEngine(Sema* sema) : env{"./templates/"}, sema(sema)
{
    concept_graph.build_graph(sema);
    function_graph.build_graph(sema);

    env.set_trim_blocks(true);
    env.set_lstrip_blocks(true);

    install_callbacks();

    std::cout << env.render_file("concept.h", inja::json{{"project", "cong"}}) << std::endl;
}

void InjaEngine::install_callbacks()
{
    const auto affix = [this](AffixType op)
    {
        return [this,op](const inja::Arguments& a) { return apply_affix(op, a); };
    };

    env.add_callback("get_concepts", 0, [this](inja::Arguments&)
    {
        auto concepts = inja::json::array();
        std::ranges::for_each(concept_graph.sorted_concepts(), [&concepts](auto c) { concepts.push_back(c->operator inja::json()); });
        return concepts;
    });

    env.add_callback("get_functions", 0, [this](inja::Arguments&)
    {
        auto functions = inja::json::array();
        std::ranges::for_each(function_graph.sorted_functions(), [&functions](const auto f) { functions.push_back(f->operator inja::json()); });
        return functions;
    });

    env.add_callback("resolve_concept", 1, [this](inja::Arguments& a)
    {
        if (!a.front()->is_string()) throw std::runtime_error("Function only accepts strings");

        const auto fqi = utils::split_fully_qualified_identifier(a.front()->get<std::string>());
        const auto c = utils::resolve_fully_qualified_identifier<Concept>(fqi, sema);
        if (!c.has_value()) return ConceptResolveResult{false, nullptr};

        return ConceptResolveResult {true, static_cast<inja::json>(*c.value())};
    });

    env.add_callback("prefix", 2, affix(AffixType::PREFIX));
    env.add_callback("postfix", 2, affix(AffixType::POSTFIX));
}

inja::json InjaEngine::apply_affix(const AffixType op, const inja::Arguments& a)
{
    if (a[0]->is_string() && a[1]->is_string())
    {
        if (op == AffixType::PREFIX)
            return a[1]->get<std::string>() + std::string(a[0]->get<std::string>());
        else if (op == AffixType::POSTFIX)
            return a[0]->get<std::string>() + std::string(a[1]->get<std::string>());
    }

    if (a[0]->is_array() && a[1]->is_string())
    {
        auto result = inja::json::array();
        for (const auto& item : a[0]->get<inja::json>())
        {
            if (item.is_string())
            {
                if (op == AffixType::PREFIX)
                    result.push_back(a[1]->get<std::string>() + std::string(item.get<std::string>()));
                else if (op == AffixType::POSTFIX)
                    result.push_back( std::string(item.get<std::string>()) + a[1]->get<std::string>());
            }
        }
        return result;
    }

    throw std::runtime_error("Invalid arguments; 1st argument must be a string or array and 2nd argument a string.");
}
