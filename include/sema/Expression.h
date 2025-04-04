//
// Created by Marvin Haschker on 12.03.25.
//

#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <memory>
#include <utility>
#include <ranges>
#include "Debug.h"
#include "Decls.h"
#include "Function.h"
#include "FunctionParameter.h"
#include "Utils.h"

struct Expression : SemaElement, Introspection<Expression>
{
    explicit Expression(Sema* sema) : sema(sema)
    {
    }

    Expression(const Expression& other) : SemaElement(other), sema(other.sema)
    {
    }

    ~Expression() override = default;

    [[nodiscard]]
    virtual bool is_constant() const
    {
        return false;
    }

    [[nodiscard]]
    virtual std::variant<const Concept*, const PlaceholderFunctionParameter*> get_result() const = 0;

    [[nodiscard]]
    Sema* get_sema() const { return sema; }

    // Base template for creating expressions
    template<typename Derived, typename... Args>
    static s_ptr<Derived> create(Sema* sema, Args&&... args) {
        return std::make_shared<Derived>(sema, std::forward<Args>(args)...);
    }

    struct DebugVisitor;

private:
    Sema* sema;
};

struct BaseConstantExpression : Expression, Introspection<BaseConstantExpression>
{
    BaseConstantExpression(Sema* sema,
                           const Concept* resulting_concept) : Expression(sema),
                                                               resulting_concept(resulting_concept)
    {
    }

    BaseConstantExpression(const BaseConstantExpression& other) :
        Expression(other), resulting_concept(other.resulting_concept)
    {
    }

    [[nodiscard]]
    std::variant<const Concept*, const PlaceholderFunctionParameter*> get_result() const override
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
    ConstantExpression(Sema* sema, const Concept* resulting_concept, T value) :
        BaseConstantExpression(sema, resulting_concept), value(std::move(value))
    {
        if (!resulting_concept) throw std::runtime_error("Resulting concept must not be empty");
    }

    using value_type = T;

    //Generate copy constructor
    ConstantExpression(const ConstantExpression& other) :
        BaseConstantExpression(other), value(other.value)
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

private:
    T value;
};

struct StringExpression final : ConstantExpression<std::string>
{
    StringExpression(Sema* sema, const std::string& value);

    static s_ptr<StringExpression> create(Sema* sema, const std::string& value) {
        return Expression::create<StringExpression>(sema, value);
    }
};

struct RealExpression final : ConstantExpression<double>
{
    RealExpression(Sema* sema, double value);

    static s_ptr<RealExpression> create(Sema* sema, double value) {
        return Expression::create<RealExpression>(sema, value);
    }
};

struct NumberExpression final : ConstantExpression<long>
{
    NumberExpression(Sema* sema, long value);

    static s_ptr<NumberExpression> create(Sema* sema, long value) {
        return Expression::create<NumberExpression>(sema, value);
    }
};

struct BooleanExpression final : ConstantExpression<bool>
{
    BooleanExpression(Sema* sema, bool value);

    static s_ptr<BooleanExpression> create(Sema* sema, bool value) {
        return Expression::create<BooleanExpression>(sema, value);
    }
};

struct BoundFunctionParameterExpression;

struct FunctionParameterExpression : Expression, Introspection<FunctionParameterExpression>
{
    FunctionParameterExpression(Sema* sema, const FunctionParameter* param) :
        Expression(sema), param(param)
    {
    }

    FunctionParameterExpression(const FunctionParameterExpression& other) :
        Expression(other), param(other.param)
    {
    }

    [[nodiscard]]
    std::variant<const Concept*, const PlaceholderFunctionParameter*> get_result() const override;

    [[nodiscard]]
    const FunctionParameter* get_param() const { return param; }

    s_ptr<BoundFunctionParameterExpression> bind(const Concept* c) const;

    static s_ptr<FunctionParameterExpression> create(Sema* sema, const FunctionParameter* value) {
        return Expression::create<FunctionParameterExpression>(sema, value);
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
    BoundFunctionParameterExpression(Sema* sema,
                                     const FunctionParameterExpression* param,
                                     const Concept* c) :
        FunctionParameterExpression(sema, param->get_param()), c(c)
    {
    }
public:
    BoundFunctionParameterExpression(const BoundFunctionParameterExpression& other) :
        FunctionParameterExpression(other.get_sema(), other.get_param()), c(other.c)
    {
    }

    [[nodiscard]]
    std::variant<const Concept*, const PlaceholderFunctionParameter*> get_result() const override
    {
        return get_concept();
    }

    [[nodiscard]]
    const Concept* get_concept() const { return c; }

    struct DebugVisitor;

private:
    const Concept* c;
};

struct CallExpression final : Expression, Introspection<CallExpression>
{
    CallExpression(Sema* sema, const Function* fun,
                   vec<s_ptr<Expression>> args);

    CallExpression(const CallExpression& other) :
        Expression(other), fun(other.fun), args(other.args)
    {
    }

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
    std::variant<const Concept*, const PlaceholderFunctionParameter*> get_result() const override;

    static s_ptr<CallExpression> create(Sema* sema, const Function* fun, vec<s_ptr<Expression>> args) {
        return Expression::create<CallExpression>(sema, fun, std::move(args));
    }

    struct DebugVisitor;

private:
    const Function* fun;
    vec<s_ptr<Expression>> args;
};

struct ArithmeticExpression final : Expression, Introspection<ArithmeticExpression>
{
    ArithmeticExpression(Sema* sema, s_ptr<Expression> left,
                         s_ptr<Expression> right, Operator op);

    static s_ptr<ArithmeticExpression> create(Sema* sema, const s_ptr<Expression>& left, const s_ptr<Expression>& right,
                                              const Operator& op)
    {
        return Expression::create<ArithmeticExpression>(sema, left, right, op);
    }

    std::variant<const Concept*, const PlaceholderFunctionParameter*> get_result() const override;

    [[nodiscard]]
    Operator get_op() const { return op; }

    [[nodiscard]]
    s_ptr<Expression> get_left() const { return left; }

    [[nodiscard]]
    s_ptr<Expression> get_right() const { return right; }

    struct DebugVisitor;

private:
    s_ptr<Expression> left, right;
    Operator op;
};

struct Expression::DebugVisitor final : BaseDebugVisitor
{
    explicit DebugVisitor(const int tabsize) : BaseDebugVisitor(tabsize)
    {
    }

    void visit(const Expression& e) { visitExpression(e); }

    void visitExpression(const Expression& e) override;
};

struct BaseConstantExpression::DebugVisitor final : BaseDebugVisitor
{
    explicit DebugVisitor(const int tabsize) : BaseDebugVisitor(tabsize)
    {
    }

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
            ss << termcolor::blue << dynamic_cast<const BaseConstantExpression&>(e).resulting_concept->get_identifier() << termcolor::reset;
    }
};

struct FunctionParameterExpression::DebugVisitor final : BaseDebugVisitor
{
    explicit DebugVisitor(const int tabsize) : BaseDebugVisitor(tabsize)
    {
    }

    void visit(const Expression& e) { visitExpression(e); }

    void visitExpression(const Expression& e) override;
};

struct CallExpression::DebugVisitor final : BaseDebugVisitor
{
    explicit DebugVisitor(const int tabsize) : BaseDebugVisitor(tabsize)
    {
    }

    void visit(const Expression& e) { visitExpression(e); }

    void visitExpression(const Expression& e) override;
};

struct BoundFunctionParameterExpression::DebugVisitor final : BaseDebugVisitor
{
    explicit DebugVisitor(const int tabsize) : BaseDebugVisitor(tabsize)
    {
    }

    void visit(const Expression& e) { visitExpression(e); }

    void visitExpression(const Expression& e) override;
};

struct ArithmeticExpression::DebugVisitor final : BaseDebugVisitor
{
    explicit DebugVisitor(const int tabsize) : BaseDebugVisitor(tabsize)
    {
    }

    void visit(const Expression& e) { visitExpression(e); }

    void visitExpression(const Expression& e) override;
};

#endif // EXPRESSION_H
