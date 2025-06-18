#pragma once

#include "sub_dec.hh"

#include "../Boolean/BooleanStatic.hh"
#include "NaturalStatic.hh"
#include "../Boolean/BooleanDynamic.hh"
#include "NaturalDynamic.hh"

namespace Number {

struct SpecSub {
    static constexpr auto name = "sub";
    static constexpr auto description = "";

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
Sub<Exp_...> sub(Exp_&&... args) 
{
    cong::lang::intern::EvalRequirements::Call<SpecSub, Exp_...>
                ::call(std::forward<Exp_>(args)...);

    return ::cong::lang::bind(
        ::cong::lang::intern::Environment{},
        ::cong::lang::intern::Exp<::cong::lang::intern::FunctionImpl<DecSub, SpecSub>>{},
        std::forward<Exp_>(args)...);
}

}

