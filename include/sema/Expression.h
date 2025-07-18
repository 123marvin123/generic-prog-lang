#pragma once

#include <format>
#include "Debug.h"
#include "Decls.h"
#include "Function.h"
#include "FunctionParameter.h"
#include "OpenBinding.h"
#include "RequiresStatement.h"
#include "SemaError.h"
#include "Utils.h"

struct Expression : SemaElement, Introspection<Expression>
{
    explicit Expression(Sema* sema) : sema(sema) {}

    Expression(const Expression& other) : SemaElement(other), sema(other.sema) {}

    ~Expression() override = default;

    [[nodiscard]]
    virtual bool is_constant() const
    {
        return false;
    }

    [[nodiscard]]
    virtual std::variant<const Concept*, const PlaceholderFunctionParameter*, OpenBinding> get_result() const = 0;

    [[nodiscard]]
    Sema* get_sema() const
    {
        return sema;
    }

    // Base template for creating expressions
    template <typename Derived, typename... Args>
    static s_ptr<Derived> create(Sema* sema, Args&&... args)
    {
        return std::make_shared<Derived>(sema, std::forward<Args>(args)...);
    }

    [[nodiscard]]
    virtual std::string to_cpp() const noexcept = 0;

    [[nodiscard]]
    virtual std::string to_python() const noexcept = 0;

    [[nodiscard]]
    std::set<const Function*> get_depending_functions() const;

    [[nodiscard]]
    std::set<const Concept*> get_depending_concepts() const;

    struct DebugVisitor;

private:
    Sema* sema;
};

struct BaseConstantExpression : Expression, Introspection<BaseConstantExpression>
{
    BaseConstantExpression(Sema* sema, const Concept* resulting_concept) :
        Expression(sema), resulting_concept(resulting_concept)
    {
    }

    BaseConstantExpression(const BaseConstantExpression& other) :
        Expression(other), resulting_concept(other.resulting_concept)
    {
    }

    [[nodiscard]]
    std::variant<const Concept*, const PlaceholderFunctionParameter*, OpenBinding> get_result() const override
    {
        return resulting_concept;
    }

    [[nodiscard]] bool is_constant() const override { return true; }

    struct DebugVisitor;

private:
    const Concept* resulting_concept;
};

template <class T>
struct ConstantExpression : BaseConstantExpression
{
    ConstantExpression(Sema* sema, const Concept* resulting_concept, T value, bool is_dynamic) :
        BaseConstantExpression(sema, resulting_concept), value(std::move(value)), is_dynamic_(is_dynamic)
    {
        if (!resulting_concept)
            throw SemaError("Resulting concept must not be empty");
    }

    using value_type = T;

    ConstantExpression(const ConstantExpression& other) :
        BaseConstantExpression(other), value(other.value), is_dynamic_(other.is_dynamic)
    {
    }

    [[nodiscard]]
    const T& eval() const
    {
        return value;
    }

    [[nodiscard]]
    T& eval()
    {
        return value;
    }

    [[nodiscard]]
    bool is_dynamic() const
    {
        return is_dynamic_;
    }

    [[nodiscard]]
    std::string to_cpp() const noexcept override
    {
        std::ostringstream oss;
        oss << eval();
        return oss.str();
    }

    [[nodiscard]]
    std::string to_python() const noexcept override
    {
        // TODO: are there differences in python and c++
        //  syntax for literals?
        return to_cpp();
    }

private:
    T value;
    bool is_dynamic_;
};

struct StringExpression final : ConstantExpression<std::string>
{
    StringExpression(Sema* sema, const std::string& value);

    static s_ptr<StringExpression> create(Sema* sema, const std::string& value)
    {
        return Expression::create<StringExpression>(sema, value);
    }
};

struct RealExpression final : ConstantExpression<double>
{
    RealExpression(Sema* sema, double value, bool is_dynamic);

    static s_ptr<RealExpression> create(Sema* sema, double value, bool is_dynamic)
    {
        return Expression::create<RealExpression>(sema, value, is_dynamic);
    }

    [[nodiscard]] std::string to_cpp() const noexcept override
    {
        if (is_dynamic())
            return std::format("::cong::lang::RealDynamic{{{}}}", eval());
        return std::format("::cong::lang::RealStatic<{}>{{}}", eval());
    }

    [[nodiscard]]
    std::string to_python() const noexcept override
    {
        return std::format("Real({})", eval());
    }
};

struct IntegerExpression final : ConstantExpression<long>
{
    IntegerExpression(Sema* sema, long value, bool is_dynamic);

    static s_ptr<IntegerExpression> create(Sema* sema, long value, bool is_dynamic)
    {
        return Expression::create<IntegerExpression>(sema, value, is_dynamic);
    }

    [[nodiscard]] std::string to_cpp() const noexcept override
    {
        auto val = eval();
        if (val >= 0)
        {
            if (is_dynamic())
                return std::format("::cong::lang::NaturalDynamic{{{}ul}}", val);
            return std::format("::cong::lang::NaturalStatic<{}>{{}}", val);
        }
        if (is_dynamic())
            return std::format("::cong::lang::IntegerDynamic{{{}l}}", val);
        return std::format("::cong::lang::IntegerStatic<{}>{{}}", val);
    }

    [[nodiscard]]
    std::string to_python() const noexcept override
    {
        return std::format("Number({})", eval());
    };
};

struct BooleanExpression final : ConstantExpression<bool>
{
    BooleanExpression(Sema* sema, bool value, bool is_dynamic);

    static s_ptr<BooleanExpression> create(Sema* sema, bool value, bool is_dynamic)
    {
        return Expression::create<BooleanExpression>(sema, value, is_dynamic);
    }

    [[nodiscard]] std::string to_cpp() const noexcept override
    {
        const auto val_ = eval() ? "true" : "false";
        if (is_dynamic())
            return std::format("::cong::lang::BooleanDynamic{{{}}}", val_);
        return std::format("::cong::lang::BooleanStatic<{}>{{}}", val_);
    }

    [[nodiscard]]
    std::string to_python() const noexcept override
    {
        return std::format("Boolean({})", eval() ? "True" : "False");
    };
};

struct BoundFunctionParameterExpression;

struct FunctionParameterExpression : Expression, Introspection<FunctionParameterExpression>
{
    FunctionParameterExpression(Sema* sema, const FunctionParameter* param) : Expression(sema), param(param) {}

    FunctionParameterExpression(const FunctionParameterExpression& other) : Expression(other), param(other.param) {}

    [[nodiscard]]
    std::variant<const Concept*, const PlaceholderFunctionParameter*, OpenBinding> get_result() const override;

    [[nodiscard]]
    const FunctionParameter* get_param() const
    {
        return param;
    }

    s_ptr<BoundFunctionParameterExpression> bind(const Concept* c) const;

    static s_ptr<FunctionParameterExpression> create(Sema* sema, const FunctionParameter* value)
    {
        return Expression::create<FunctionParameterExpression>(sema, value);
    }

    [[nodiscard]] std::string to_cpp() const noexcept override
    {
        return utils::sanitize_cpp_identifier(param->get_identifier());
    }

    [[nodiscard]] std::string to_python() const noexcept override
    {
        return utils::sanitize_python_identifier(param->get_identifier());
    }

    struct DebugVisitor;

private:
    const FunctionParameter* param;
};

struct BoundFunctionParameterExpression final : FunctionParameterExpression,
                                                Introspection<BoundFunctionParameterExpression>
{
    friend s_ptr<BoundFunctionParameterExpression> FunctionParameterExpression::bind(const Concept* c) const;

private:
    BoundFunctionParameterExpression(Sema* sema, const FunctionParameterExpression* param, const Concept* c) :
        FunctionParameterExpression(sema, param->get_param()), c(c)
    {
    }

public:
    BoundFunctionParameterExpression(const BoundFunctionParameterExpression& other) :
        FunctionParameterExpression(other.get_sema(), other.get_param()), c(other.c)
    {
    }

    [[nodiscard]]
    std::variant<const Concept*, const PlaceholderFunctionParameter*, OpenBinding> get_result() const override
    {
        return get_concept();
    }

    [[nodiscard]]
    const Concept* get_concept() const
    {
        return c;
    }

    struct DebugVisitor;

private:
    const Concept* c;
};

struct CallExpression final : Expression, Introspection<CallExpression>
{
    CallExpression(Sema* sema, const Function* fun, vec<s_ptr<Expression>> args);

    CallExpression(const CallExpression& other) : Expression(other), fun(other.fun), args(other.args) {}

    [[nodiscard]]
    const Function* get_function() const
    {
        return fun;
    }

    [[nodiscard]]
    const vec<s_ptr<Expression>>& get_arguments() const
    {
        return args;
    }

    [[nodiscard]]
    std::variant<const Concept*, const PlaceholderFunctionParameter*, OpenBinding> get_result() const override;

    static s_ptr<CallExpression> create(Sema* sema, const Function* fun, vec<s_ptr<Expression>> args)
    {
        return Expression::create<CallExpression>(sema, fun, std::move(args));
    }

    [[nodiscard]] std::string to_cpp() const noexcept override;

    [[nodiscard]] std::string to_python() const noexcept override;

    struct DebugVisitor;

private:
    const Function* fun;
    vec<s_ptr<Expression>> args;
};

struct ArithmeticExpression final : Expression, Introspection<ArithmeticExpression>
{
    ArithmeticExpression(Sema* sema, s_ptr<Expression> left, s_ptr<Expression> right, Operator op);

    static s_ptr<ArithmeticExpression> create(Sema* sema, const s_ptr<Expression>& left, const s_ptr<Expression>& right,
                                              const Operator& op)
    {
        return Expression::create<ArithmeticExpression>(sema, left, right, op);
    }

    std::variant<const Concept*, const PlaceholderFunctionParameter*, OpenBinding> get_result() const override;

    [[nodiscard]]
    Operator get_op() const
    {
        return op;
    }

    [[nodiscard]]
    s_ptr<Expression> get_left() const
    {
        return left;
    }

    [[nodiscard]]
    s_ptr<Expression> get_right() const
    {
        return right;
    }

    [[nodiscard]] std::string to_cpp() const noexcept override;

    [[nodiscard]] std::string to_python() const noexcept override;

    struct DebugVisitor;

private:
    s_ptr<Expression> left, right;
    Operator op;
};

struct LetExpression final : Expression, Introspection<LetExpression>
{
    LetExpression(Sema* sema, const vec<LetBinding>& bindings, vec<s_ptr<Expression>> body);

    LetExpression(const LetExpression& other) : Expression(other), bindings(other.bindings), body(other.body) {}

    [[nodiscard]]
    const vec<LetBinding>& get_bindings() const
    {
        return bindings;
    }

    [[nodiscard]]
    const vec<s_ptr<Expression>>& get_body() const
    {
        return body;
    }

    [[nodiscard]]
    std::variant<const Concept*, const PlaceholderFunctionParameter*, OpenBinding> get_result() const override;

    static s_ptr<LetExpression> create(Sema* sema, const vec<LetBinding>& bindings, const vec<s_ptr<Expression>>& body)
    {
        return Expression::create<LetExpression>(sema, bindings, body);
    }

    [[nodiscard]] std::string to_cpp() const noexcept override;

    [[nodiscard]] std::string to_python() const noexcept override;

    struct DebugVisitor;

private:
    vec<LetBinding> bindings;
    vec<s_ptr<Expression>> body;
};

// Expression for referencing a let-bound variable
struct LetVariableReferenceExpression final : Expression, Introspection<LetVariableReferenceExpression>
{
    LetVariableReferenceExpression(Sema* sema, const std::string& identifier, s_ptr<Expression> bound_value);

    LetVariableReferenceExpression(const LetVariableReferenceExpression& other) :
        Expression(other), identifier(other.identifier), bound_value(other.bound_value)
    {
    }

    [[nodiscard]]
    const std::string& get_identifier() const
    {
        return identifier;
    }

    [[nodiscard]]
    s_ptr<Expression> get_bound_value() const
    {
        return bound_value;
    }

    [[nodiscard]]
    std::variant<const Concept*, const PlaceholderFunctionParameter*, OpenBinding> get_result() const override;

    static s_ptr<LetVariableReferenceExpression> create(Sema* sema, const std::string& identifier,
                                                        s_ptr<Expression> bound_value)
    {
        return Expression::create<LetVariableReferenceExpression>(sema, identifier, bound_value);
    }

    [[nodiscard]] std::string to_cpp() const noexcept override;

    [[nodiscard]] std::string to_python() const noexcept override;

    struct DebugVisitor;

private:
    std::string identifier;
    s_ptr<Expression> bound_value;
};

struct RequiresCallExpression final : Expression, Introspection<RequiresCallExpression>
{
    RequiresCallExpression(Sema* sema, const RequiresStatement& r, const Function* f) :
        Expression(sema), stmnt(r), f(f) {};

    RequiresCallExpression(const RequiresCallExpression& other) : Expression(other), stmnt(other.stmnt), f(other.f) {}

    [[nodiscard]]
    const RequiresStatement& get_stmnt() const
    {
        return stmnt;
    }

    [[nodiscard]]
    std::variant<const Concept*, const PlaceholderFunctionParameter*, OpenBinding> get_result() const override;

    static s_ptr<RequiresCallExpression> create(Sema* sema, const RequiresStatement& r, const Function* f)
    {
        return Expression::create<RequiresCallExpression>(sema, r, f);
    }

    [[nodiscard]] std::string to_cpp() const noexcept override;

    [[nodiscard]] std::string to_python() const noexcept override;

    struct DebugVisitor;

private:
    RequiresStatement stmnt;
    const Function* f;
};

struct ConceptReferenceExpression final : Expression, Introspection<ConceptReferenceExpression>
{
    ConceptReferenceExpression(Sema* sema, const Concept* c) : Expression(sema), concept_(c)
    {
        if (!concept_)
            throw SemaError("Concept must not be empty");
    }

    ConceptReferenceExpression(const ConceptReferenceExpression& other) : Expression(other), concept_(other.concept_) {}

    [[nodiscard]]
    const Concept* get_concept() const
    {
        return concept_;
    }

    [[nodiscard]]
    std::variant<const Concept*, const PlaceholderFunctionParameter*, OpenBinding> get_result() const override
    {
        return get_concept();
    };

    static s_ptr<ConceptReferenceExpression> create(Sema* sema, const Concept* c)
    {
        return Expression::create<ConceptReferenceExpression>(sema, c);
    }

    [[nodiscard]] std::string to_cpp() const noexcept override;

    [[nodiscard]] std::string to_python() const noexcept override;

    struct DebugVisitor;

private:
    const Concept* concept_;
};

struct OpenBindingExpression final : Expression, Introspection<OpenBindingExpression>
{
    OpenBindingExpression(Sema* sema, unsigned int N);
    OpenBindingExpression(const OpenBindingExpression& other);

    static s_ptr<OpenBindingExpression> create(Sema* sema, int N)
    {
        return Expression::create<OpenBindingExpression>(sema, N);
    }

    [[nodiscard]] std::string to_cpp() const noexcept override;

    [[nodiscard]] std::string to_python() const noexcept override;

    [[nodiscard]]
    bool is_constant() const override
    {
        return true;
    }

    [[nodiscard]]
    std::variant<const Concept*, const PlaceholderFunctionParameter*, OpenBinding> get_result() const override
    {
        return OpenBinding{N};
    };

    struct DebugVisitor;

private:
    const unsigned int N;
};

struct CallMetafunExpression : Expression, Introspection<CallMetafunExpression>
{
    CallMetafunExpression(Sema* sema, s_ptr<Expression> value) : Expression(sema), inner(std::move(value))
    {
        ;
        if (!inner)
            throw SemaError("Inner expression must not be empty");
    }

    CallMetafunExpression(const CallMetafunExpression& other) : Expression(other), inner(other.inner) {}

    [[nodiscard]]
    s_ptr<Expression> get_inner() const noexcept
    {
        return inner;
    }

    struct DebugVisitor;

private:
    s_ptr<Expression> inner;
};

struct QuoteExpression final : CallMetafunExpression
{
    QuoteExpression(Sema* sema, const s_ptr<Expression>& value) : CallMetafunExpression(sema, value) {}

    [[nodiscard]]
    std::variant<const Concept*, const PlaceholderFunctionParameter*, OpenBinding> get_result() const override;

    static s_ptr<QuoteExpression> create(Sema* sema, const s_ptr<Expression>& value)
    {
        return Expression::create<QuoteExpression>(sema, value);
    }

    [[nodiscard]] std::string to_cpp() const noexcept override;

    [[nodiscard]] std::string to_python() const noexcept override;

    struct DebugVisitor;
};

struct EvalExpression final : CallMetafunExpression
{
    EvalExpression(Sema* sema, const s_ptr<Expression>& value) : CallMetafunExpression(sema, value) {}


    [[nodiscard]]
    std::variant<const Concept*, const PlaceholderFunctionParameter*, OpenBinding> get_result() const override;

    static s_ptr<EvalExpression> create(Sema* sema, const s_ptr<Expression>& value)
    {
        return Expression::create<EvalExpression>(sema, value);
    }

    [[nodiscard]] std::string to_cpp() const noexcept override;

    [[nodiscard]] std::string to_python() const noexcept override;

    struct DebugVisitor;
};

struct LambdaExpression final : Expression
{
    LambdaExpression(Sema* sema,
        const vec<std::tuple<std::string, std::variant<PlaceholderFunctionParameter*, Concept*>>>& params,
        const s_ptr<Expression>& body) :
        Expression(sema), params(params), body(body)
    {
    }


    [[nodiscard]]
    std::variant<const Concept*, const PlaceholderFunctionParameter*, OpenBinding> get_result() const override;

    static s_ptr<EvalExpression> create(Sema* sema, const s_ptr<Expression>& value)
    {
        return Expression::create<EvalExpression>(sema, value);
    }

    [[nodiscard]] std::string to_cpp() const noexcept override;

    [[nodiscard]] std::string to_python() const noexcept override;

    [[nodiscard]]
    s_ptr<Expression> get_body() const noexcept
    {
        return body;
    }

    void set_body(s_ptr<Expression> value) noexcept
    {
        body = value;
    }

    [[nodiscard]]
    const vec<std::tuple<std::string, std::variant<PlaceholderFunctionParameter*, Concept*>>>& get_params() const noexcept
    {
        return params;
    }

    void set_params(const vec<std::tuple<std::string, std::variant<PlaceholderFunctionParameter*, Concept*>>>& p) noexcept
    {
        params = p;
    }

    struct DebugVisitor;

private:
    vec<std::tuple<std::string, std::variant<PlaceholderFunctionParameter*, Concept*>>> params;
    s_ptr<Expression> body;
};

struct LambdaVariableReferenceExpression final : Expression, Introspection<LambdaVariableReferenceExpression>
{
    LambdaVariableReferenceExpression(Sema* sema, LambdaExpression* lambdaExp, std::size_t idx) : Expression(sema), lambdaExp(lambdaExp), idx(idx) {};

    LambdaVariableReferenceExpression(const LambdaVariableReferenceExpression& other) :
        Expression(other), lambdaExp(other.lambdaExp), idx(other.idx)
    {
    }

    [[nodiscard]] std::variant<const Concept*, const PlaceholderFunctionParameter*, OpenBinding>
    get_result() const override;

    [[nodiscard]] std::string to_cpp() const noexcept override;

    [[nodiscard]] std::string to_python() const noexcept override;

private:
    LambdaExpression* lambdaExp;
    std::size_t idx;
};

//@section DebugVisitor

struct Expression::DebugVisitor final : BaseDebugVisitor
{
    explicit DebugVisitor(const int tabsize) : BaseDebugVisitor(tabsize) {}

    void visit(const Expression& e) { visitExpression(e); }

    void visitExpression(const Expression& e) override;
};

struct BaseConstantExpression::DebugVisitor final : BaseDebugVisitor
{
    explicit DebugVisitor(const int tabsize) : BaseDebugVisitor(tabsize) {}

    void visit(const Expression& e) { visitExpression(e); }

    void visitExpression(const Expression& e) override
    {
        ss << spaces();

        if (const auto string_exp = utils::dyn_cast<ConstantExpression<std::string>>(&e))
            ss << termcolor::red << string_exp->eval() << termcolor::reset;
        else if (const auto bool_exp = utils::dyn_cast<ConstantExpression<bool>>(&e))
            ss << termcolor::blue << std::boolalpha << bool_exp->eval() << std::noboolalpha << termcolor::reset;
        else if (const auto real_exp = utils::dyn_cast<ConstantExpression<double>>(&e))
            ss << real_exp->eval();
        else if (const auto number_exp = utils::dyn_cast<ConstantExpression<long>>(&e))
            ss << number_exp->eval();
        else
            ss << termcolor::blue << dynamic_cast<const BaseConstantExpression&>(e).resulting_concept->get_identifier()
               << termcolor::reset;
    }
};

struct FunctionParameterExpression::DebugVisitor final : BaseDebugVisitor
{
    explicit DebugVisitor(const int tabsize) : BaseDebugVisitor(tabsize) {}

    void visit(const Expression& e) { visitExpression(e); }

    void visitExpression(const Expression& e) override;
};

struct CallExpression::DebugVisitor final : BaseDebugVisitor
{
    explicit DebugVisitor(const int tabsize) : BaseDebugVisitor(tabsize) {}

    void visit(const Expression& e) { visitExpression(e); }

    void visitExpression(const Expression& e) override;
};

struct BoundFunctionParameterExpression::DebugVisitor final : BaseDebugVisitor
{
    explicit DebugVisitor(const int tabsize) : BaseDebugVisitor(tabsize) {}

    void visit(const Expression& e) { visitExpression(e); }

    void visitExpression(const Expression& e) override;
};

struct ArithmeticExpression::DebugVisitor final : BaseDebugVisitor
{
    explicit DebugVisitor(const int tabsize) : BaseDebugVisitor(tabsize) {}

    void visit(const Expression& e) { visitExpression(e); }

    void visitExpression(const Expression& e) override;
};

struct LetExpression::DebugVisitor final : BaseDebugVisitor
{
    explicit DebugVisitor(const int tabsize) : BaseDebugVisitor(tabsize) {}

    void visit(const Expression& e) { visitExpression(e); }

    void visitExpression(const Expression& e) override;
};

struct LetVariableReferenceExpression::DebugVisitor final : BaseDebugVisitor
{
    explicit DebugVisitor(const int tabsize) : BaseDebugVisitor(tabsize) {}

    void visit(const Expression& e) { visitExpression(e); }

    void visitExpression(const Expression& e) override;
};

struct OpenBindingExpression::DebugVisitor final : BaseDebugVisitor
{
    explicit DebugVisitor(const int tabsize) : BaseDebugVisitor(tabsize) {}

    void visit(const Expression& e) { visitExpression(e); }

    void visitExpression(const Expression& e) override;
};
