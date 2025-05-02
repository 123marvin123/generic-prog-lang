//
// Created by Marvin Haschker on 11.03.25.
//

#ifndef FUNCTION_H
#define FUNCTION_H

#include <utility>
#include <unordered_map>
#include <format>
#include <variant>
#include <ranges>

#include "Debug.h"
#include "Decls.h"
#include "Expression.h"
#include "FunctionParameter.h"
#include "Namespace.h"
#include "RequiresStatement.h"
#include "Utils.h"
#include "jinja2cpp/reflected_value.h"
#include "sema/SemaContext.h"
#include "sema/SemaIdentifier.h"

struct Function : SemaIdentifier, SemaContext<FunctionParameter>, Introspection<Function>
{
    Function(std::string name,
             const Namespace* parent)
        : SemaIdentifier(std::move(name), parent)
    {
        if (get_identifier().empty()) throw std::runtime_error("Name must not be empty");
        if (!parent) throw std::runtime_error("Parent must not be empty");
    }

    [[nodiscard]]
    opt<FunctionParameter*> find_function_parameter(std::string_view) const;

    FunctionParameter* register_function_parameter(u_ptr<FunctionParameter>);

    template<class T, typename... Args> requires std::is_base_of_v<FunctionParameter, T>
    T* register_function_parameter(Args&&... args)
    {
        auto* ptr = register_function_parameter(std::make_unique<T>(std::forward<Args>(args)...));
        return utils::dyn_cast<T>(ptr);
    }

    [[nodiscard]]
    opt<PlaceholderFunctionParameter*> find_placeholder(std::string_view) const;

    [[nodiscard]]
    vec<FunctionParameter*> get_parameters() const
    {
        vec<FunctionParameter*> result;
        result.reserve(data.size());

        std::ranges::transform(data, std::back_inserter(result), utils::ptr_transform);

        return result;
    }

    void set_description(const std::string& desc)
    {
        description = desc;
    }

    [[nodiscard]]
    opt<std::string> get_description() const
    {
        return description;
    }

    [[nodiscard]]
    bool has_description() const
    {
        return description.has_value() && !description.value().empty();
    }

    void add_generic_implementation(s_ptr<Expression> exp);

    [[nodiscard]]
    vec<s_ptr<Expression>> get_implementations() const
    {
        return generic_implementations;
    }

    [[nodiscard]]
    vec<RequiresStatement> requirements() const
    {
        return exp_requires;
    }

    void add_requirement(s_ptr<Expression>, opt<std::string> = std::nullopt);

    [[nodiscard]]
    virtual bool is_dependent() const { throw std::runtime_error("Not implemented."); };

    [[nodiscard]]
    virtual std::variant<const Concept*, PlaceholderFunctionParameter*>
    get_result() const { throw std::runtime_error("Not implemented."); };

    struct DebugVisitor;

private:
    opt<std::string> description;
    vec<s_ptr<Expression>> generic_implementations;
    vec<RequiresStatement> exp_requires;
};

struct ConcreteFunction final : Function, Introspection<ConcreteFunction>
{
    ConcreteFunction(std::string name,
                    const Namespace* parent,
                     const Concept* resulting_concept) : Function(std::move(name), parent),
                                                              resulting_concept(resulting_concept)
    {
        if (!resulting_concept) throw std::runtime_error("Resulting concept must not be empty");
    }

    [[nodiscard]]
    std::variant<const Concept*, PlaceholderFunctionParameter*>
    get_result() const override
    {
        return resulting_concept;
    }

    void set_resulting_concept(const Concept* c)
    {
        resulting_concept = c;
    }

    [[nodiscard]] bool is_dependent() const override { return false; }

    struct DebugVisitor;

private:
    const Concept* resulting_concept;
};

struct DependentFunction final : Function, Introspection<DependentFunction>
{
    DependentFunction(std::string name,
                      const Namespace* parent) :
        Function(std::move(name), parent), dependency(nullptr)
    {
    }

    [[nodiscard]]
    bool is_dependent() const override { return true; }

    PlaceholderFunctionParameter* set_dependency(PlaceholderFunctionParameter* dependency)
    {
        this->dependency = dependency;
        return dependency;
    }

    [[nodiscard]] std::variant<const Concept*, PlaceholderFunctionParameter*>
    get_result() const override
    {
        if (!dependency) throw std::runtime_error("Dependency is empty");
        return dependency;
    }

    struct DebugVisitor;

private:
    PlaceholderFunctionParameter* dependency;
};


struct Function::DebugVisitor final : BaseDebugVisitor
{
    explicit DebugVisitor(const int tabsize)
        : BaseDebugVisitor(tabsize)
    {
    }

    void visit(const Function& f) { visitFunction(f); }

    void visitFunction(const Function& f) override;
};

class FunctionView {
    const Function* func;
public:
    explicit FunctionView(const Function* f) : func(f) {}

    friend struct jinja2::TypeReflection<FunctionView>;
};

/*
template<> struct jinja2::TypeReflection<ConcreteFunction> : TypeReflected<ConcreteFunction>
{
    static auto& GetAccessors()
    {
        static auto parent = TypeReflection<FunctionView>::GetAccessors();
        static std::unordered_map<std::string, FieldAccessor> accessors(parent.begin(), parent.end());

        accessors.insert({
            {"type", [](const ConcreteFunction&) { return "concrete_function"; }},
            {"result_concept", [](const ConcreteFunction& f) { return Reflect(*std::get<const Concept*>(f.get_result())); }}
        });

        return accessors;
    }
};

template<> struct jinja2::TypeReflection<DependentFunction> : TypeReflected<DependentFunction>
{
    static auto& GetAccessors()
    {
        static auto parent = TypeReflection<FunctionView>::GetAccessors();
        static std::unordered_map<std::string, FieldAccessor> accessors(parent.begin(), parent.end());

        accessors.insert({
            {"type", [](const Function&) { return "dependent_function"; }},
            {"result_dependency", [](const DependentFunction& f) { return Reflect(*std::get<PlaceholderFunctionParameter*>(f.get_result())); }}
        });

        return accessors;
    }
};
*/

const Concept* get_object(const Function* f);

template<> struct jinja2::TypeReflection<FunctionView> : TypeReflected<FunctionView>
{
    static auto& GetAccessors()
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

                return Reflect(*get_object(f.func));
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
};

#endif //FUNCTION_H
