//
// Created by Marvin Haschker on 11.03.25.
//

#ifndef FUNCTIONPARAMETER_H
#define FUNCTIONPARAMETER_H

#include <utility>
#include <memory>
#include "Decls.h"
#include "Debug.h"
#include "sema/Concept.h"

struct FunctionParameter : SemaElement, Introspection<FunctionParameter>
{
    ~FunctionParameter() override = default;

    explicit FunctionParameter(std::string name) : name(std::move(name))
    {
        if (get_identifier().empty()) throw std::runtime_error("Name must not be empty");
    }

    [[nodiscard]]
    std::string_view get_identifier() const { return name; }

    [[nodiscard]]
    const Function* get_function() const
    {
        if (!function) throw std::runtime_error("Function is not yet set");
        return function;
    }

    void set_function(const Function* fn) { function = fn; }

    [[nodiscard]]
    virtual explicit operator inja::json() const
    {
        return inja::json{{"name", get_identifier()}};
    }

    struct DebugVisitor;

private:
    std::string name;
    const Function* function;
};

struct FunctionParameter::DebugVisitor : BaseDebugVisitor
{
    explicit DebugVisitor(const int tabsize)
        : BaseDebugVisitor(tabsize)
    {
    }

    void visit(const FunctionParameter& p) { visitFunctionParameter(p); }

    void visitFunctionParameter(const FunctionParameter& p) override;
};

struct ConcreteFunctionParameter final : FunctionParameter, Introspection<ConcreteFunctionParameter>
{
    ConcreteFunctionParameter(const std::string& name,
                              const Concept* type) :
        FunctionParameter(name), type(type)
    {
        if (!type) throw std::runtime_error("Type must not be empty");
    }

    [[nodiscard]]
    const Concept* get_type() const { return type; }

    [[nodiscard]]
    explicit operator inja::json() const override
    {
        auto json = FunctionParameter::operator inja::json();
        json["type"] = "concrete_function_parameter";
        json["concept"] = type->operator inja::json();

        return json;
    };

    struct DebugVisitor;

private:
    const Concept* type;
};

struct ConcreteFunctionParameter::DebugVisitor final : FunctionParameter::DebugVisitor
{
    explicit DebugVisitor(const int tabsize)
        : FunctionParameter::DebugVisitor(tabsize)
    {
    }

    void visitFunctionParameter(const FunctionParameter& p) override;
};

struct PlaceholderFunctionParameter final : FunctionParameter, Introspection<PlaceholderFunctionParameter>
{
    PlaceholderFunctionParameter(const std::string& name,
                                    std::string type_placeholder) :
        FunctionParameter(name), type_placeholder(std::move(type_placeholder))
    {
        if (get_type_placeholder_name().empty()) throw std::runtime_error("Placeholder name must not be empty");
    }

    [[nodiscard]]
    const std::string& get_type_placeholder_name() const
    {
        return type_placeholder;
    }

    [[nodiscard]]
    explicit operator inja::json() const override
    {
        auto base = FunctionParameter::operator inja::json();
        base["type"] = "placeholder_function_parameter";
        base["placeholder_id"] = type_placeholder;
        return base;
    };

    struct DebugVisitor;

private:
    const std::string type_placeholder;
};

struct PlaceholderFunctionParameter::DebugVisitor final : FunctionParameter::DebugVisitor
{
    explicit DebugVisitor(const int tabsize)
        : FunctionParameter::DebugVisitor(tabsize)
    {
    }

    void visitFunctionParameter(const FunctionParameter& p) override;
};

struct DependentFunctionParameter final : FunctionParameter, Introspection<DependentFunctionParameter>
{
    DependentFunctionParameter(const std::string& name,
                               const PlaceholderFunctionParameter* placeholder) :
        FunctionParameter(name), placeholder(placeholder)
    {
        if (!get_placeholder()) throw std::runtime_error("Placeholder must not be empty");
    }

    [[nodiscard]]
    const PlaceholderFunctionParameter* get_placeholder() const { return placeholder; }

    [[nodiscard]] explicit operator inja::json() const override
    {
        auto base = FunctionParameter::operator inja::json();
        base["type"] = "dependent_function_parameter";
        base["dependency"] = placeholder->operator inja::json();
        return base;
    };

    struct DebugVisitor;

private:
    const PlaceholderFunctionParameter* placeholder;
};

struct DependentFunctionParameter::DebugVisitor final : FunctionParameter::DebugVisitor
{
    explicit DebugVisitor(const int tabsize)
        : FunctionParameter::DebugVisitor(tabsize)
    {
    }

    void visitFunctionParameter(const FunctionParameter& p) override;
};

#endif //FUNCTIONPARAMETER_H
