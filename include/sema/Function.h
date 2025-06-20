#pragma once

#include <utility>
#include <unordered_map>
#include <variant>

#include "Debug.h"
#include "Decls.h"
#include "Expression.h"
#include "FunctionParameter.h"
#include "Namespace.h"
#include "RequiresStatement.h"
#include "Utils.h"
#include "jinja2cpp/reflected_value.h"
#include "SemaContext.h"
#include "SemaIdentifier.h"
#include "SemaError.h"

struct Function : SemaIdentifier, SemaContext<FunctionParameter>, Introspection<Function>
{
    Function(std::string name,
             const Namespace* parent,
            bool export_ = true);

    ~Function();

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

    void add_generic_implementation(const GenericImplementation& exp);

    [[nodiscard]]
    const vec<GenericImplementation>& get_implementations() const
    {
        return generic_implementations;
    }

    [[nodiscard]]
    const vec<RequiresStatement>& requirements() const
    {
        return exp_requires;
    }

    [[nodiscard]]
    bool export_enabled() const { return export_; }

    const RequiresStatement& add_requirement(s_ptr<Expression>, opt<std::string> = std::nullopt, opt<std::string> =
    std::nullopt);

    [[nodiscard]]
    virtual bool is_dependent() const
    {
        throw std::runtime_error("Not implemented.");
    }

    [[nodiscard]]
    opt<const RequiresStatement*> find_requirement(std::string_view string) const
    {
        for (const auto& r : exp_requires)
        {
            if (r.get_name() == string)
            {
                return &r;
            }
        }

        return std::nullopt;
    }

    void set_time_complexity(s_ptr<Expression> exp) { time_complexity = std::move(exp); }

    [[nodiscard]]
    s_ptr<Expression> get_time_complexity() const { return time_complexity; }

    void set_space_complexity(s_ptr<Expression> exp) { space_complexity = std::move(exp); }

    [[nodiscard]]
    s_ptr<Expression> get_space_complexity() const { return space_complexity; }

    [[nodiscard]]
    virtual std::variant<const Concept*, PlaceholderFunctionParameter*>
    get_result() const { throw std::runtime_error("Not implemented."); };

    struct DebugVisitor;

private:
    opt<std::string> description;
    vec<GenericImplementation> generic_implementations;
    vec<RequiresStatement> exp_requires;
    s_ptr<Expression> time_complexity, space_complexity;
    bool export_;
};

struct ConcreteFunction final : Function, Introspection<ConcreteFunction>
{
    ConcreteFunction(std::string name,
                    const Namespace* parent,
                    const Concept* resulting_concept,
                    bool export_ = true) : Function(std::move(name), parent, export_),
                                                              resulting_concept(resulting_concept)
    {
        if (!resulting_concept) throw SemaError("Resulting concept must not be empty");
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
                      const Namespace* parent,
                      bool export_ = true) :
        Function(std::move(name), parent, export_), dependency(nullptr)
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
        if (!dependency)
            throw SemaError("Dependency is empty");
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

template<> struct jinja2::TypeReflection<FunctionView> : TypeReflected<FunctionView>
{
    static std::unordered_map<std::string, FieldAccessor>& GetAccessors();
};
