#pragma once

#include "not__dec.hh"

#include "Boolean/BooleanStatic.hh"
#include "Number/NaturalStatic.hh"
#include "Boolean/BooleanDynamic.hh"
#include "Number/NaturalDynamic.hh"

namespace Boolean {

struct SpecNot_ {
    static constexpr auto name = "not_";
    static constexpr auto description = "$\\lnot$ p(1) (logical negation)";

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
Not_<Exp_...> not_(Exp_&&... args) 
{
    cong::lang::intern::EvalRequirements::Call<SpecNot_, Exp_...>
                ::call(std::forward<Exp_>(args)...);

    return ::cong::lang::bind(
        ::cong::lang::intern::Environment{},
        ::cong::lang::intern::Exp<::cong::lang::intern::FunctionImpl<DecNot_, SpecNot_>>{},
        std::forward<Exp_>(args)...);
}

}

