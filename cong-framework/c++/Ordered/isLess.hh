#pragma once

#include "isLess_dec.hh"

#include "../Boolean/BooleanStatic.hh"
#include "../Number/NaturalStatic.hh"
#include "../Boolean/BooleanDynamic.hh"
#include "../Number/NaturalDynamic.hh"

namespace Ordered {

struct SpecIsLess {
    static constexpr auto name = "isLess";
    static constexpr auto description = "p(1) $<$ p(2) (is p(1) less than p(2)?)";

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
IsLess<Exp_...> isLess(Exp_&&... args) 
{
    cong::lang::intern::EvalRequirements::Call<SpecIsLess, Exp_...>
                ::call(std::forward<Exp_>(args)...);

    return ::cong::lang::bind(
        ::cong::lang::intern::Environment{},
        ::cong::lang::intern::Exp<::cong::lang::intern::FunctionImpl<DecIsLess, SpecIsLess>>{},
        std::forward<Exp_>(args)...);
}

}

