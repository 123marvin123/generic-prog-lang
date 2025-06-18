#pragma once

#include "succ_dec.hh"

#include "../Boolean/BooleanStatic.hh"
#include "NaturalStatic.hh"
#include "../Boolean/BooleanDynamic.hh"
#include "NaturalDynamic.hh"

namespace Number {

struct SpecSucc {
    static constexpr auto name = "succ";
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
Succ<Exp_...> succ(Exp_&&... args) 
{
    cong::lang::intern::EvalRequirements::Call<SpecSucc, Exp_...>
                ::call(std::forward<Exp_>(args)...);

    return ::cong::lang::bind(
        ::cong::lang::intern::Environment{},
        ::cong::lang::intern::Exp<::cong::lang::intern::FunctionImpl<DecSucc, SpecSucc>>{},
        std::forward<Exp_>(args)...);
}

}

