#pragma once

#include "or__dec.hh"

#include "Boolean/BooleanStatic.hh"
#include "Number/NaturalStatic.hh"
#include "Boolean/BooleanDynamic.hh"
#include "Number/NaturalDynamic.hh"

namespace Boolean {

struct SpecOr_ {
    static constexpr auto name = "or_";
    static constexpr auto description = "p(1) $\\lor$ p(2) (logical disjunction)";

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



template <typename... Exp_>
constexpr
Or_<Exp_...> or_(Exp_&&... args) 
{
    cong::lang::intern::EvalRequirements::Call<SpecOr_, Exp_...>
                ::call(std::forward<Exp_>(args)...);

    return ::cong::lang::bind(
        ::cong::lang::intern::Environment{},
        ::cong::lang::intern::Exp<::cong::lang::intern::FunctionImpl<DecOr_, SpecOr_>>{},
        std::forward<Exp_>(args)...);
}

}

