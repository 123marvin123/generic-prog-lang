#pragma once

#include "div_dec.hh"

#include "Boolean/BooleanStatic.hh"
#include "Number/NaturalStatic.hh"
#include "Boolean/BooleanDynamic.hh"
#include "Number/NaturalDynamic.hh"

namespace Number {

struct SpecDiv {
    static constexpr auto name = "div";
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
Div<Exp_...> div(Exp_&&... args) 
{
    cong::lang::intern::EvalRequirements::Call<SpecDiv, Exp_...>
                ::call(std::forward<Exp_>(args)...);

    return ::cong::lang::bind(
        ::cong::lang::intern::Environment{},
        ::cong::lang::intern::Exp<::cong::lang::intern::FunctionImpl<DecDiv, SpecDiv>>{},
        std::forward<Exp_>(args)...);
}

}

