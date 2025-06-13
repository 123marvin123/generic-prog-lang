#include "sema/Sema.h"

#include <sema/Expression.h>
#include <visitor/AbstractVisitor.h>

opt<Concept*> Sema::create_concept(Namespace* ns, const std::string& name,
                                  opt<std::set<const Concept*>> bases)
{
    auto c = bases
        ? std::make_unique<Concept>(name, ns, bases.value())
        : std::make_unique<Concept>(name, ns);
    const auto ptr = c.get();
    if (!ns->register_concept(std::move(c)))
        return std::nullopt;
    // ReSharper disable once CppDFALocalValueEscapesFunction
    return ptr;
}

opt<Namespace*> Sema::create_namespace(const std::string& name, Sema* sema,
                                      Namespace* parent)
{
    auto ns = std::make_unique<Namespace>(name, sema, parent);
    const auto ptr = ns.get();
    if (!parent->register_namespace(std::move(ns)))
        return std::nullopt;
    return ptr;
}

void Sema::register_builtin_concepts()
{
    object_concept = create_concept(get_sema(), "Object").value();
    boolean_concept = create_concept(get_sema(), "Boolean", std::set{object_concept}).value();
    number_concept = create_concept(get_sema(), "Number", std::set{object_concept}).value();
    real_concept = create_concept(get_sema(), "Real", std::set{number_concept}).value();
    string_concept = create_concept(get_sema(), "String", std::set{object_concept}).value();
}

void Sema::register_builtin_functions()
{
    /*
        add_function = create_function<ConcreteFunction>(this, "add", this, object_concept).value();
    sub_function = create_function<ConcreteFunction>(this, "sub", this, object_concept).value();
    mul_function = create_function<ConcreteFunction>(this, "mul", this, object_concept).value();
    div_function = create_function<ConcreteFunction>(this, "div", this, object_concept).value();
    mod_function = create_function<ConcreteFunction>(this, "mod", this, object_concept).value();
    */
}

void Sema::register_builtin_operators()
{
    auto& table = Concept::get_operation_table();

    auto apply = [&table](Operator op)
    {
        return [&table,op](const std::tuple<const Concept*, const Concept*, const Concept*>& t)
        {
            auto [left, right, result] = t;
            table[op][left][right] = Concept::OperationResult::valid(result);
            table[op][right][left] = Concept::OperationResult::valid(result);
        };
    };

    vec<std::tuple<const Concept*, const Concept*, const Concept*>> results = {
        {boolean_concept, boolean_concept, boolean_concept},
        {number_concept, boolean_concept, boolean_concept},
        {number_concept, number_concept, number_concept},
        {real_concept, number_concept, real_concept},
        {real_concept, real_concept, real_concept},
        {string_concept, string_concept, string_concept}
    };

    std::array ops = {
        Operator::ADD,
        Operator::SUB,
        Operator::MUL,
        Operator::DIV,
        Operator::MOD
    };

    std::ranges::for_each(ops, [&results,&apply](auto op)
    {
        std::ranges::for_each(results, apply(op));
    });
}

template <>
const Concept* Sema::builtin_concept<Object>() const
{
    if (!object_concept) throw SemaError("Object concept not registered");
    return object_concept;
}


template <>
const Concept* Sema::builtin_concept<std::string>() const
{
    if (!string_concept) throw SemaError("String concept not registered");
    return string_concept;
}

template <>
const Concept* Sema::builtin_concept<bool>() const
{
    if (!boolean_concept) throw SemaError("Boolean concept not registered");
    return boolean_concept;
}

template <>
const Concept* Sema::builtin_concept<long>() const
{
    if (!number_concept) throw SemaError("Number concept not registered");
    return number_concept;
}

template <>
const Concept* Sema::builtin_concept<double>() const
{
    if (!real_concept) throw SemaError("Real concept not registered");
    return real_concept;
}

template <>
const Function* Sema::builtin_function<Operator::ADD>() const
{
    if (!add_function) throw SemaError("Add function not registered");
    return add_function;
}

template <>
const Function* Sema::builtin_function<Operator::SUB>() const
{
    if (!sub_function) throw SemaError("Sub function not registered");
    return sub_function;
}

template <>
const Function* Sema::builtin_function<Operator::MUL>() const
{
    if (!mul_function) throw SemaError("Mul function not registered");
    return mul_function;
}

template <>
const Function* Sema::builtin_function<Operator::DIV>() const
{
    if (!div_function) throw SemaError("Div function not registered");
    return div_function;
}

template <>
const Function* Sema::builtin_function<Operator::MOD>() const
{
    if (!mod_function) throw SemaError("Mod function not registered");
    return mod_function;
}