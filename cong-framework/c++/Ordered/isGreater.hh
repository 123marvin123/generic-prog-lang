#pragma once

#include "isGreater_dec.hh"

namespace Ordered {

struct SpecIsGreater {
    static constexpr auto name = "isGreater";
    static constexpr auto description = "p(1) $>$ p(2) (is p(1) greater than p(2)?)";

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
IsGreater<Exp_...> isGreater(Exp_&&... args) 
{
    cong::lang::intern::EvalRequirements::Call<SpecIsGreater, Exp_...>
                ::call(std::forward<Exp_>(args)...);

    return ::cong::lang::bind(
        ::cong::lang::intern::Environment{},
        ::cong::lang::intern::Exp<::cong::lang::intern::FunctionImpl<DecIsGreater, SpecIsGreater>>{},
        std::forward<Exp_>(args)...);
}

}

