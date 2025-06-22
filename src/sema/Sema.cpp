#include "sema/Sema.h"

#include <sema/Expression.h>
#include <sema/GenericImplementation.h>
#include <visitor/AbstractVisitor.h>

opt<Concept*> Sema::create_concept(Namespace* ns, const std::string& name,
                                  opt<std::set<const Concept*>> bases, bool export_)
{
    auto c = bases
        ? std::make_unique<Concept>(name, ns, bases.value(), export_)
        : std::make_unique<Concept>(name, ns, export_);
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
    if (const auto& obj_ns = create_namespace("Object", get_sema(), get_sema());
        obj_ns.has_value())
        object_concept = *create_concept(*obj_ns, "Object", {}, false);

    if(const auto& ordered_ns = create_namespace("Ordered", get_sema(), get_sema());
        ordered_ns.has_value()) 
    {
        ordered_concept = *create_concept(*ordered_ns, "Ordered", std::set{const_cast<const Concept*>(object_concept)},
        false);
        ordered_concept->set_description("element of totally ordered set");
    }

    if (const auto& bool_ns = create_namespace("Boolean", get_sema(), get_sema());
            bool_ns.has_value())
        boolean_concept = *create_concept(*bool_ns, "Boolean", std::set{const_cast<const Concept*>(object_concept)},
        false);

    if (const auto& number_ns = create_namespace("Number", get_sema(), get_sema());
            number_ns.has_value())
    {
        number_concept = *create_concept(*number_ns, "Number", std::set{const_cast<const Concept*>(object_concept)},
        false);
        
        natural_concept = *create_concept(*number_ns, "Natural", std::set{const_cast<const Concept*>(number_concept),
        const_cast<const Concept*>(ordered_concept)},
        false);
        natural_concept->set_description("natural number, possibly zero");

        cardinal_concept = *create_concept(*number_ns, "Cardinal", std::set{const_cast<const Concept*>(number_concept),
        const_cast<const Concept*>(ordered_concept)},
        false);
        cardinal_concept->set_description("cardinal number");

        integer_concept = *create_concept(*number_ns, "Integer", std::set{const_cast<const Concept*>(natural_concept),
        const_cast<const Concept*>(ordered_concept)},
        false);
        integer_concept->set_description("integer number");

        rational_concept = *create_concept(*number_ns, "Rational", std::set{const_cast<const Concept*>(number_concept),
        const_cast<const Concept*>(ordered_concept)},
        false);
        rational_concept->set_description("rational number");

        real_concept = *create_concept(*number_ns, "Real", std::set{const_cast<const Concept*>(number_concept)}, false);
        real_concept->set_description("real number");

        complex_concept = *create_concept(*number_ns, "Complex", std::set{const_cast<const Concept*>(number_concept),
        const_cast<const Concept*>(ordered_concept)}, false);
        complex_concept->set_description("complex number");
    }

    if (const auto& string_ns = create_namespace("String", get_sema(), get_sema());
            string_ns.has_value())
        string_concept = *create_concept(*string_ns, "String", std::set{const_cast<const Concept*>(object_concept)});

    if (const auto& map_ns = create_namespace("Map", get_sema(), get_sema()); map_ns.has_value())
    {
        map_concept = *create_concept(*map_ns, "Map", std::set{const_cast<const Concept*>(object_concept)});
    }
}

void Sema::register_builtin_functions()
{
    const auto& number_ns = find_namespace("Number");

    add_function = *create_function<ConcreteFunction>(*number_ns, "add", *number_ns, number_concept, false);
    {
        add_function->register_function_parameter<ConcreteFunctionParameter>("a", number_concept);
        add_function->register_function_parameter<ConcreteFunctionParameter>("b", number_concept);
    }

    sub_function = *create_function<ConcreteFunction>(*number_ns, "sub", *number_ns, number_concept, false);
    {
        sub_function->register_function_parameter<ConcreteFunctionParameter>("a", number_concept);
        sub_function->register_function_parameter<ConcreteFunctionParameter>("b", number_concept);
    }

    mul_function = *create_function<ConcreteFunction>(*number_ns, "mul", *number_ns, number_concept, false);
    {
        mul_function->register_function_parameter<ConcreteFunctionParameter>("a", number_concept);
        mul_function->register_function_parameter<ConcreteFunctionParameter>("b", number_concept);
    }

    div_function = *create_function<ConcreteFunction>(*number_ns, "div", *number_ns, number_concept, false);
    {
        div_function->register_function_parameter<ConcreteFunctionParameter>("a", number_concept);
        div_function->register_function_parameter<ConcreteFunctionParameter>("b", number_concept);
    }

    mod_function = *create_function<ConcreteFunction>(*number_ns, "mod", *number_ns, number_concept, false);
    {
        mod_function->register_function_parameter<ConcreteFunctionParameter>("a", number_concept);
        mod_function->register_function_parameter<ConcreteFunctionParameter>("b", number_concept);
    }

    succ_function = *create_function<ConcreteFunction>(*number_ns, "succ", *number_ns, integer_concept, false);
    {
        succ_function->register_function_parameter<ConcreteFunctionParameter>("n", natural_concept);
    }

    pred_function = *create_function<DependentFunction>(*number_ns, "pred", *number_ns, false);
    {
        const auto dep = pred_function->register_function_parameter<PlaceholderFunctionParameter>("n", "T");
        utils::dyn_cast<DependentFunction>(pred_function)->set_dependency(dep);
    }

    pow_function = *create_function<ConcreteFunction>(*number_ns, "pow", *number_ns, number_concept, false);
    {
        pow_function->register_function_parameter<ConcreteFunctionParameter>("base", number_concept);
        pow_function->register_function_parameter<ConcreteFunctionParameter>("exp", integer_concept);
    }

    const auto& bool_ns = find_namespace("Boolean");

    and_function = *create_function<ConcreteFunction>(*bool_ns, "and", *bool_ns, boolean_concept, false);
    {
        and_function->register_function_parameter<ConcreteFunctionParameter>("a", boolean_concept);
        and_function->register_function_parameter<ConcreteFunctionParameter>("b", boolean_concept);
    }

    or_function = *create_function<ConcreteFunction>(*bool_ns, "or", *bool_ns, boolean_concept, false);
    {
        or_function->register_function_parameter<ConcreteFunctionParameter>("a", boolean_concept);
        or_function->register_function_parameter<ConcreteFunctionParameter>("b", boolean_concept);
    }

    xor_function = *create_function<ConcreteFunction>(*bool_ns, "xor", *bool_ns, boolean_concept, false);
    {
        xor_function->register_function_parameter<ConcreteFunctionParameter>("a", boolean_concept);
        xor_function->register_function_parameter<ConcreteFunctionParameter>("b", boolean_concept);
        /*
         *        requires { Object::isNotEqual(p1, p2) }
         *        requires { or(and(p1, not(p2)), and(not(p1), p2)) }
         */
    }

    not_function = *create_function<ConcreteFunction>(*bool_ns, "not", *bool_ns, boolean_concept, false);
    {
        not_function->register_function_parameter<ConcreteFunctionParameter>("a", boolean_concept);
    }

    const auto& object_ns = find_namespace("Object");

    isEqual_function = *create_function<ConcreteFunction>(*object_ns, "isEqual", *object_ns, boolean_concept, false);
    {
        isEqual_function->register_function_parameter<ConcreteFunctionParameter>("a", object_concept);
        isEqual_function->register_function_parameter<ConcreteFunctionParameter>("b", object_concept);
    }

    isNotEqual_function =
        *create_function<ConcreteFunction>(*object_ns, "isNotEqual", *object_ns, boolean_concept, false);
    {
        auto a = isNotEqual_function->register_function_parameter<ConcreteFunctionParameter>("a", object_concept);
        auto b = isNotEqual_function->register_function_parameter<ConcreteFunctionParameter>("b", object_concept);

        auto inner = CallExpression::create(this, isEqual_function,
                                            {
                                                s_ptr<Expression>{FunctionParameterExpression::create(sema, a)},
                                                s_ptr<Expression>{FunctionParameterExpression::create(sema, b)},
                                            });

        isNotEqual_function->add_generic_implementation(
            GenericImplementation{CallExpression::create(this, not_function, {inner})});
    }

    id_function = *create_function<DependentFunction>(*object_ns, "id", *object_ns, false);
    {
        auto placeholder = id_function->register_function_parameter<PlaceholderFunctionParameter>("a", "T");
        utils::dyn_cast<DependentFunction>(id_function)->set_dependency(placeholder);

        id_function->add_generic_implementation(
            GenericImplementation{FunctionParameterExpression::create(sema, placeholder)});
    }

    isModelOf_function = *create_function<ConcreteFunction>(*object_ns, "isModelOf", *object_ns, boolean_concept, false);
    {
        isModelOf_function->set_description("does object p(1) model concept p(2)?");
        isModelOf_function->register_function_parameter<ConcreteFunctionParameter>("p1", object_concept);
        isModelOf_function->register_function_parameter<ConcreteFunctionParameter>("p2", object_concept);

        GenericImplementation g(nullptr, nullptr, nullptr, "c++");
        g.set_native_implementation(R"Impl(
            using Plain_ = typename cong::lang::core::Plain::Call<decltype(p2)>::Type;
            if constexpr (!std::is_base_of_v<cong::lang::ConceptTag, Plain_>)
            {
                return cong::lang::BooleanStatic<false>{}; // Not a concept
            }

            return cong::lang::BooleanStatic<
                cong::lang::core::IsModelOf::Call<decltype(p1), decltype(p2)>::Type::native()
            >{};
        )Impl");

        isModelOf_function->add_generic_implementation(g);
    }


    const auto& ordered_ns = find_namespace("Ordered");

    isLess_function = *create_function<ConcreteFunction>(*ordered_ns, "isLess", *ordered_ns, boolean_concept, false);
    {
        isLess_function->register_function_parameter<ConcreteFunctionParameter>("a", ordered_concept);
        isLess_function->register_function_parameter<ConcreteFunctionParameter>("b", ordered_concept);
    }

    isLessEqual_function =
        *create_function<ConcreteFunction>(*ordered_ns, "isLessEqual", *ordered_ns, boolean_concept, false);
    {
        isLessEqual_function->register_function_parameter<ConcreteFunctionParameter>("a", ordered_concept);
        isLessEqual_function->register_function_parameter<ConcreteFunctionParameter>("b", ordered_concept);
    }

    isGreater_function =
        *create_function<ConcreteFunction>(*ordered_ns, "isGreater", *ordered_ns, boolean_concept, false);
    {
        isGreater_function->register_function_parameter<ConcreteFunctionParameter>("a", ordered_concept);
        isGreater_function->register_function_parameter<ConcreteFunctionParameter>("b", ordered_concept);
    }

    isGreaterEqual_function =
        *create_function<ConcreteFunction>(*ordered_ns, "isGreaterEqual", *ordered_ns, boolean_concept, false);
    {
        isGreaterEqual_function->register_function_parameter<ConcreteFunctionParameter>("a", ordered_concept);
        isGreaterEqual_function->register_function_parameter<ConcreteFunctionParameter>("b", ordered_concept);
    }
}

void Sema::register_builtin_requirements()
{
    {
        const auto n = utils::dyn_cast<PlaceholderFunctionParameter>(*pred_function->find_function_parameter("n"));

        // Object::isModelOf(p1, Number::Number)
        const auto a = CallExpression::create(sema, isModelOf_function, { FunctionParameterExpression::create(sema, n),
        ConceptReferenceExpression::create(sema, number_concept) });

        RequiresStatement isNumber = pred_function->add_requirement(a, "IsNumber", "Argument is a number");

        /*
        * Boolean::or(
        *   Boolean::not(Object::isModelOf(p1, Number::Natural)),
        *   Ordered::isGreater(p1, 0)
        * )
        */
        pred_function->add_requirement(
        CallExpression::create(sema, or_function, {
            CallExpression::create(sema, not_function, {
                CallExpression::create(sema, isModelOf_function, { FunctionParameterExpression::create(sema, n), ConceptReferenceExpression::create(sema, natural_concept) })
            }),
            CallExpression::create(sema, isGreater_function, { FunctionParameterExpression::create(sema, n), IntegerExpression::create(sema, 0, false) })
        }), "IsValidNatural", "p1 > 0 if Natural");


    }


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
        {integer_concept, boolean_concept, boolean_concept},
        {integer_concept, integer_concept, integer_concept},
        {real_concept, integer_concept, real_concept},
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
const Concept* Sema::builtin_concept<Map>() const
{
    if (!map_concept) throw SemaError("Map concept not registered");
    return map_concept;
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
    if (!integer_concept) throw SemaError("Integer concept not registered");
    return integer_concept;
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

template <>
const Function* Sema::builtin_function<Operator::POW>() const
{
    if (!pow_function) throw SemaError("Pow function not registered");
    return pow_function;
}