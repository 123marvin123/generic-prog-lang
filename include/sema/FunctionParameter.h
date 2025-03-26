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
#include "jinja2cpp/reflected_value.h"

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

    struct DebugVisitor;

private:
    std::string name;
    const Function* function;
};

template<> struct jinja2::TypeReflection<FunctionParameter> : TypeReflected<FunctionParameter>
{
    static auto& GetAccessors()
    {
        static std::unordered_map<std::string, FieldAccessor> accessors = {
            {"name", [](const FunctionParameter& p) { return p.get_identifier(); }}
        };
        return accessors;
    }
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

    struct DebugVisitor;

private:
    const Concept* type;
};

template<> struct jinja2::TypeReflection<ConcreteFunctionParameter> : TypeReflected<ConcreteFunctionParameter>
{
    static auto& GetAccessors()
    {
        static auto parent = TypeReflection<FunctionParameter>::GetAccessors();

        static std::unordered_map<std::string, FieldAccessor> accessors(parent.begin(), parent.end());

        accessors.insert({
            {"type", [](const ConcreteFunctionParameter&) { return "concrete_function_parameter"; }},
            {"concept", [](const ConcreteFunctionParameter& p) { return Reflect(*p.get_type()); }},
        });

        return accessors;
    }
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

    struct DebugVisitor;

private:
    const std::string type_placeholder;
};

template<> struct jinja2::TypeReflection<PlaceholderFunctionParameter> : TypeReflected<PlaceholderFunctionParameter>
{
    static auto& GetAccessors()
    {
        static auto parent = TypeReflection<FunctionParameter>::GetAccessors();

        static std::unordered_map<std::string, FieldAccessor> accessors(parent.begin(), parent.end());

        accessors.insert({
            {"type", [](const PlaceholderFunctionParameter&) { return "placeholder_function_parameter"; }},
            {"placeholder_id", [](const PlaceholderFunctionParameter& p) { return p.get_type_placeholder_name(); }},
        });

        return accessors;
    }
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

    struct DebugVisitor;

private:
    const PlaceholderFunctionParameter* placeholder;
};


template<> struct jinja2::TypeReflection<DependentFunctionParameter> : TypeReflected<DependentFunctionParameter>
{
    static auto& GetAccessors()
    {
        static auto parent = TypeReflection<FunctionParameter>::GetAccessors();

        static std::unordered_map<std::string, FieldAccessor> accessors(parent.begin(), parent.end());

        accessors.insert({
            {"type", [](const DependentFunctionParameter&) { return "dependent_function_parameter"; }},
            {"dependency", [](const DependentFunctionParameter& p) { return Reflect(*p.get_placeholder()); }},
        });

        return accessors;
    }
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
