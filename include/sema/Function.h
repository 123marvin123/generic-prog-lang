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

#include "sema/SemaIdentifier.h"
#include "sema/SemaContext.h"
#include "Decls.h"
#include "FunctionParameter.h"
#include "Expression.h"
#include "Utils.h"
#include "Debug.h"

template<class T, class C>
concept IsFunction = IsIdentifier<T> && IsConcept<C> && requires(T& t, std::string name, Namespace* ns)
{
    { t.get_parameters() } -> std::convertible_to<vec<FunctionParameter*>>;
    { t.get_result() } -> std::convertible_to<std::variant<const C*, PlaceholderFunctionParameter*>>;
    { t.is_dependent() } -> std::same_as<bool>;
    { t.add_generic_implementation(nullptr) };
};

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
    vec<s_ptr<Expression>> requirements() const
    {
        return exp_requires;
    }

    void add_requirement(s_ptr<Expression>);

    [[nodiscard]]
    virtual bool is_dependent() const = 0;

    [[nodiscard]]
    virtual std::variant<const Concept*, PlaceholderFunctionParameter*>
    get_result() const = 0;

    explicit virtual operator inja::json() const
    {
        const vec<FunctionParameter*> params = get_parameters();
        auto params_json = inja::json::array();

        for (FunctionParameter* p : params)
            params_json.push_back(p->operator inja::json());
        /* TODO: Export reqs, desc and generic impls */
        return inja::json{
            {"name", get_identifier()},
            {"full_name", get_full_name()},
            {"parameter", params_json}
        };
    };

    struct DebugVisitor;

private:
    opt<std::string> description;
    vec<s_ptr<Expression>> generic_implementations;
    vec<s_ptr<Expression>> exp_requires;
};

static_assert(IsFunction<Function, Concept>, "ConcreteFunction should satisfy the Function concept");

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

    explicit operator inja::json() const override
    {
        if (!resulting_concept) throw std::runtime_error("Resulting concept must not be empty");

        auto base = Function::operator inja::json();
        base["type"] = "concrete_function";
        base["result_concept"] = resulting_concept->operator inja::json();

        return base;
    }

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

    [[nodiscard]]
    explicit operator inja::json() const override
    {
        if (!dependency) throw std::runtime_error("Dependency is empty");

        auto base = Function::operator inja::json();
        base["type"] = "dependent_function";
        base["result_dependency"] = dependency->operator inja::json();
        return base;
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

#endif //FUNCTION_H
