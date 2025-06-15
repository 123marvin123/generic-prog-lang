//
// Created by Marvin Haschker on 11.03.25.
//
#include "sema/Function.h"

#include <Utils.h>
#include <sema/Expression.h>
#include <sema/Namespace.h>
#include <sema/Sema.h>
#include <sema/FunctionParameter.h>
#include <sema/GenericImplementation.h>

Function::Function(std::string name, const Namespace* parent)
    : SemaIdentifier(std::move(name), parent)
    {
        if (get_identifier().empty()) std::throw_with_nested(SemaError("Function name must not be empty"));
        if (!parent) std::throw_with_nested(SemaError("Parent namespace must not be empty"));
    }

Function::~Function() = default;

opt<FunctionParameter*> Function::find_function_parameter(std::string_view identifier) const
{
    return find([identifier](const auto& p)
    {
        return identifier == p->get_identifier();
    });
}

FunctionParameter* Function::register_function_parameter(u_ptr<FunctionParameter> fp)
{
    if (find_function_parameter(fp->get_identifier()))
        std::throw_with_nested(SemaError(std::format("Function parameter {} already registered", fp->get_identifier())));

    fp->set_function(this);
    auto* ptr = fp.get();
    register_element(std::move(fp));
    return ptr;
}

opt<PlaceholderFunctionParameter*> Function::find_placeholder(const std::string_view a) const
{
    for (const auto& param : data)
    {
        if (auto* p = utils::dyn_cast<PlaceholderFunctionParameter>(param.get());
            p->get_identifier() == a)
            return p;
    }

    return std::nullopt;
}

void Function::add_generic_implementation(const GenericImplementation& exp)
{
    if (exp.get_expression())
    {
        if (const auto& exp_result = exp.get_expression()->get_result();
           std::holds_alternative<const Concept*>(exp_result))
        {
            const auto& c = std::get<const Concept*>(exp_result);
            if (const auto& fun_result = get_result();
                std::holds_alternative<const Concept*>(fun_result))
            {
                if (const auto& target_concept = std::get<const Concept*>(fun_result);
                    !c->matches_concept(target_concept))
                    std::throw_with_nested(
                        SemaError(
                            std::format("Generic implementation ({}) does not match function return type ({})",
                        c->get_identifier(), target_concept->get_identifier())
                        ));
            }
        }
    }

    generic_implementations.push_back(exp);
}

void Function::add_requirement(s_ptr<Expression> exp, opt<std::string> name)
{
    static const auto boolean = get_namespace()->get_sema()->builtin_concept<bool>();

    if (!std::holds_alternative<const Concept*>(exp->get_result()))
        throw SemaError("Expression must return a concrete concept");
    if (const auto conceptResult = std::get<const Concept*>(exp->get_result());
        conceptResult != boolean)
        throw SemaError(
            std::format("Expression must return {}, not {}",
                boolean->get_identifier(), conceptResult->get_identifier()));

    exp_requires.emplace_back(std::move(exp), std::move(name));
}

void Function::DebugVisitor::visitFunction(const Function& f)
{
    ss << spaces() << termcolor::blue << "Function" << termcolor::reset;
    ss << "(name: " << termcolor::green << f.get_identifier() << termcolor::reset << ", args: [";

    auto function_parameters = f.get_parameters();
    for (auto it = function_parameters.begin(); it != function_parameters.end(); ++it)
    {
        const FunctionParameter* param = *it;

        if (const auto& cast = utils::dyn_cast<Introspection<ConcreteFunctionParameter>>(param))
            ss << cast->to_string();
        else if (const auto& cast = utils::dyn_cast<Introspection<PlaceholderFunctionParameter>>(param))
            ss << cast->to_string();
        else if (const auto& cast = utils::dyn_cast<Introspection<DependentFunctionParameter>>(param))
            ss << cast->to_string();

        if (it + 1 != function_parameters.end())
            ss << ", ";
    }

    ss << "]) -> " << termcolor::yellow;

    if (const auto& result = f.get_result(); std::holds_alternative<const Concept*>(result))
        ss << std::get<const Concept*>(result)->get_identifier();
    else if (std::holds_alternative<PlaceholderFunctionParameter*>(result))
        ss << std::get<PlaceholderFunctionParameter*>(result)->get_type_placeholder_name();

    ss << termcolor::reset << "\n";
    tabsize += 2;

    ss << spaces() << termcolor::blue << "Description" << termcolor::reset << ": ";
    if (!f.get_description().has_value())
        ss << termcolor::on_red << "<none>";
    else
        ss << termcolor::red << "\"" << f.get_description().value() << "\"";

    ss << termcolor::reset << "\n";
    if (const vec<GenericImplementation>& generic_impls = f.get_implementations(); !generic_impls.empty())
    {
        for (const GenericImplementation& exp : generic_impls)
        {
            ss << spaces() << termcolor::bold << "generic" << termcolor::reset << " {\n";
            ss << exp.get_expression()->to_string(tabsize + 2) << "\n" << spaces() << "}\n";
        }
    }

    ss << termcolor::reset;
    if (const vec<RequiresStatement>& reqs = f.requirements(); !reqs.empty())
    {
        for (const RequiresStatement& exp : reqs)
        {
            ss << spaces() << termcolor::bold << "requires";

            if (exp.is_named())
                ss << termcolor::reset << "(name: \"" << termcolor::red << exp.get_name().value() << "\")"
                   << termcolor::reset;

            ss << " {\n";
            ss << exp.get_expression()->to_string(tabsize + 2) << "\n" << spaces() << "}\n";
        }
    }

    if (f.get_space_complexity())
    {
        ss << spaces() << termcolor::bold << "space complexity" << termcolor::reset << " {\n";
        ss << f.get_space_complexity()->to_string(tabsize + 2) << "\n" << spaces() << "}\n";
    }

    if (f.get_time_complexity())
    {
        ss << spaces() << termcolor::bold << "time complexity" << termcolor::reset << " {\n";
        ss << f.get_time_complexity()->to_string(tabsize + 2) << "\n" << spaces() << "}\n";
    }


    ss << termcolor::reset;
}
const Concept* get_object(const Function* f)
{
    return f->get_namespace()->get_sema()->find_concept("Object").value();
}

std::unordered_map<std::string, jinja2::FieldAccessor<FunctionView>>&
jinja2::TypeReflection<FunctionView>::GetAccessors()
{
    static std::unordered_map<std::string, FieldAccessor> accessors = {
        {"name", [](const FunctionView& f) { return f.func->get_identifier(); }},
        {"full_name", [](const FunctionView& f) { return f.func->get_full_name(); }},
        {"description", [](const FunctionView& f) { return f.func->get_description().value_or(""); }},
        {"result", [](const FunctionView& f)
        {
            if (std::holds_alternative<const Concept*>(f.func->get_result()))
            {
                return Reflect(*std::get<const Concept*>(f.func->get_result()));
            }

            return Reflect(*f.func->get_namespace()->get_sema()->builtin_concept<Object>());
        }},
        {"ns", [](const FunctionView& f)
        {
            const utils::FQIInfo info = utils::split_fully_qualified_identifier(f.func->get_full_name());
            ValuesList l(info.namespaces.begin(), info.namespaces.end());
            return l;
        }},
        {"params", [](const FunctionView& f)
        {
            const auto& params = f.func->get_parameters();
            ValuesList l{};
            l.reserve(params.size());

            std::ranges::transform(params, std::back_inserter(l), [](const auto* p) {
                if (const auto *concrete =
                          utils::dyn_cast<ConcreteFunctionParameter>(p))
                    return Reflect(*concrete);

                  if (const auto *placeholder =
                        utils::dyn_cast<PlaceholderFunctionParameter>(p))
                      return Reflect(*placeholder);

                    if (const auto *dependent =
                              utils::dyn_cast<DependentFunctionParameter>(p))
                        return Reflect(*dependent);

                    return Reflect(*p);
                });

            return l;
        }}
    };

    return accessors;
}