#pragma once

#include "isNotEqual_dec.hh"

#include "../Boolean/BooleanStatic.hh"
#include "../Number/NaturalStatic.hh"
#include "../Boolean/BooleanDynamic.hh"
#include "../Number/NaturalDynamic.hh"

namespace Object {

struct SpecIsNotEqual {
    static constexpr auto name = "isNotEqual";
    static constexpr auto description = "p(1) $\\neq$ p(2) (is p(1) not equal to p(2)?)";

    template<class Index_>
    struct Requirement
    {
        using Present = cong::lang::core::False;
        template<class...>
        struct Call
        {
            using Type = cong::lang::core::Undefined;
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
            using Type = cong::lang::core::Undefined;
            static constexpr Type call(...);
        };
    };

    using GenericImpls = cong::lang::core::Tuple<
    >;
};

/*
 * Requirement #1:
 * ::Boolean::not_(::Object::isEqual(p1, p2))
*/
template<>
struct SpecIsNotEqual::Requirement<cong::lang::core::NaturalStatic<0>> {
    using Present = cong::lang::core::True;
    template<class Arg1_ , class Arg2_>
    struct Call
    {
        static constexpr auto call(Arg1_&& p1 , Arg2_&& p2)
        {
            using ExpType_ = std::decay_t<decltype(::Boolean::not_(::Object::isEqual(p1, p2)))>;
            const auto& result = [&]{ return ::Boolean::not_(::Object::isEqual(p1, p2)); };
            return cong::lang::intern::CondEval<
                        typename ::cong::lang::intern::IsExp::Call<ExpType_>::Type,
                        decltype(result),
                        ExpType_
                   >::call(result);
        }
        using Type = std::invoke_result_t<decltype(call), Arg1_ , Arg2_>;
    };
};

template <typename... Exp_>
constexpr
IsNotEqual<Exp_...> isNotEqual(Exp_&&... args) 
{
    cong::lang::intern::EvalRequirements::Call<SpecIsNotEqual, Exp_...>
                ::call(std::forward<Exp_>(args)...);

    return ::cong::lang::bind(
        ::cong::lang::intern::Environment{},
        ::cong::lang::intern::Exp<::cong::lang::intern::FunctionImpl<DecIsNotEqual, SpecIsNotEqual>>{},
        std::forward<Exp_>(args)...);
}

}

