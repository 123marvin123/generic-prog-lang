#pragma once

#include "pred_dec.hh"

#include "Boolean/BooleanStatic.hh"
#include "Boolean/BooleanDynamic.hh"

#include "Number/NaturalDynamic.hh"
#include "Number/NaturalStatic.hh"
#include "Number/core/NaturalStatic.hh"
#include "String/core/StringStatic.hh"

#include "Proj.hh"


#include "Ordered/isGreater.hh"
#include "Boolean/not_.hh"
#include "Boolean/or_.hh"
#include "Object/isModelOf.hh"
namespace Number {

struct SpecPred {
    static constexpr cong::lang::core::StringStatic name = "pred";
    static constexpr cong::lang::core::StringStatic description = "";

    template<class Index_>
    struct Requirement
    {
        using Present = cong::lang::core::False;
        template<class...>
        struct Call
        {
            using Type = cong::lang::core::Undefined<"Req for Pred not specified">;
            static constexpr Type call(...);
        };
    };

    template<class Index_>
    struct GenericImpl
    {
        using Present = cong::lang::core::False;
        template<typename...>
        struct Call 
        {
            using Type = cong::lang::core::Undefined<"Generic impl for Pred not specified">;
            static constexpr Type call(...);
        };
    };

    template<cong::lang::core::StringStatic Name>
    struct NameToRequirement;

    using GenericImpls = cong::lang::core::Tuple<
    >;
};

/*
 * Requirement #1 named IsNumber:
 * ::Object::isModelOf(n, ::cong::lang::intern::Exp<::Number::ConceptNumber>{})
*/
template<>
struct SpecPred::Requirement<cong::lang::core::NaturalStatic<0>> {
    using Present = cong::lang::core::True;

    static constexpr cong::lang::core::StringStatic name = "IsNumber";
    static constexpr cong::lang::core::StringStatic description = "Argument is a number";

    template<class Arg1_>
    struct Call
    {
        static constexpr auto call(Arg1_&& n)
        {
            const auto& resultFn = [&]{
                return ::Object::isModelOf(n, ::cong::lang::intern::Exp<::Number::ConceptNumber>{});
            };

            using ExpType_ = std::decay_t<decltype(resultFn())>;
            return cong::lang::intern::CondEval<
                        typename ::cong::lang::intern::IsExp::Call<ExpType_>::Type,
                        decltype(resultFn),
                        ExpType_
                   >::call(resultFn);
        }
        using Type = std::invoke_result_t<decltype(call), Arg1_>;
    };
};

template<>
struct SpecPred::NameToRequirement<"IsNumber">
{
    using Type = SpecPred::Requirement<cong::lang::core::NaturalStatic<0>>;
};
 
/*
 * Requirement #2 named IsValidNatural:
 * ::Boolean::or_(::Boolean::not_(NameToRequirement<"IsNumber">::Type::Call<Arg1_>::call(n)), ::Ordered::isGreater(n, ::cong::lang::NaturalStatic<0>{}))
*/
template<>
struct SpecPred::Requirement<cong::lang::core::NaturalStatic<1>> {
    using Present = cong::lang::core::True;

    static constexpr cong::lang::core::StringStatic name = "IsValidNatural";
    static constexpr cong::lang::core::StringStatic description = "p1 > 0 if Natural";

    template<class Arg1_>
    struct Call
    {
        static constexpr auto call(Arg1_&& n)
        {
            const auto& resultFn = [&]{
                return ::Boolean::or_(::Boolean::not_(NameToRequirement<"IsNumber">::Type::Call<Arg1_>::call(n)), ::Ordered::isGreater(n, ::cong::lang::NaturalStatic<0>{}));
            };

            using ExpType_ = std::decay_t<decltype(resultFn())>;
            return cong::lang::intern::CondEval<
                        typename ::cong::lang::intern::IsExp::Call<ExpType_>::Type,
                        decltype(resultFn),
                        ExpType_
                   >::call(resultFn);
        }
        using Type = std::invoke_result_t<decltype(call), Arg1_>;
    };
};

template<>
struct SpecPred::NameToRequirement<"IsValidNatural">
{
    using Type = SpecPred::Requirement<cong::lang::core::NaturalStatic<1>>;
};


template <typename... Exp_>
constexpr
Pred<Exp_...> pred(Exp_&&... args) 
{
    return ::cong::lang::bind(
        ::cong::lang::intern::Environment{},
        ::cong::lang::intern::Exp<::cong::lang::intern::FunctionImpl<DecPred, SpecPred>>{},
        std::forward<Exp_>(args)...);
}

}

