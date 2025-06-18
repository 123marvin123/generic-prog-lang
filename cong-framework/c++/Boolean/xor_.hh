#pragma once

#include "xor__dec.hh"

#include "Boolean/BooleanStatic.hh"
#include "Number/NaturalStatic.hh"
#include "Boolean/BooleanDynamic.hh"
#include "Number/NaturalDynamic.hh"

namespace Boolean {

struct SpecXor_ {
    static constexpr auto name = "xor_";
    static constexpr auto description = "p(1) $\\oplus$ p(2) (logical exclusive disjunction)";

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
 * ::Object::isNotEqual(p1, p2)
*/
template<>
struct SpecXor_::Requirement<cong::lang::core::NaturalStatic<0>> {
    using Present = cong::lang::core::True;
    template<class Arg1_ , class Arg2_>
    struct Call
    {
        static constexpr auto call(Arg1_&& p1 , Arg2_&& p2)
        {
            using ExpType_ = std::decay_t<decltype(::Object::isNotEqual(p1, p2))>;
            const auto& result = [&]{ return ::Object::isNotEqual(p1, p2); };
            return cong::lang::intern::CondEval<
                        typename ::cong::lang::intern::IsExp::Call<ExpType_>::Type,
                        decltype(result),
                        ExpType_
                   >::call(result);
        }
        using Type = std::invoke_result_t<decltype(call), Arg1_ , Arg2_>;
    };
}; 
/*
 * Requirement #2:
 * ::Boolean::or_(::Boolean::and_(p1, ::Boolean::not_(p2)), ::Boolean::and_(::Boolean::not_(p1), p2))
*/
template<>
struct SpecXor_::Requirement<cong::lang::core::NaturalStatic<1>> {
    using Present = cong::lang::core::True;
    template<class Arg1_ , class Arg2_>
    struct Call
    {
        static constexpr auto call(Arg1_&& p1 , Arg2_&& p2)
        {
            using ExpType_ = std::decay_t<decltype(::Boolean::or_(::Boolean::and_(p1, ::Boolean::not_(p2)), ::Boolean::and_(::Boolean::not_(p1), p2)))>;
            const auto& result = [&]{ return ::Boolean::or_(::Boolean::and_(p1, ::Boolean::not_(p2)), ::Boolean::and_(::Boolean::not_(p1), p2)); };
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
Xor_<Exp_...> xor_(Exp_&&... args) 
{
    cong::lang::intern::EvalRequirements::Call<SpecXor_, Exp_...>
                ::call(std::forward<Exp_>(args)...);

    return ::cong::lang::bind(
        ::cong::lang::intern::Environment{},
        ::cong::lang::intern::Exp<::cong::lang::intern::FunctionImpl<DecXor_, SpecXor_>>{},
        std::forward<Exp_>(args)...);
}

}

