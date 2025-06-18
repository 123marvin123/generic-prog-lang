#pragma once

#include "isEqual_dec.hh"

namespace Object {

struct SpecIsEqual {
    static constexpr auto name = "isEqual";
    static constexpr auto description = "p(1) $=$ p(2) (is p(1) equal to p(2)?)";

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
IsEqual<Exp_...> isEqual(Exp_&&... args) 
{
    cong::lang::intern::EvalRequirements::Call<SpecIsEqual, Exp_...>
                ::call(std::forward<Exp_>(args)...);

    return ::cong::lang::bind(
        ::cong::lang::intern::Environment{},
        ::cong::lang::intern::Exp<::cong::lang::intern::FunctionImpl<DecIsEqual, SpecIsEqual>>{},
        std::forward<Exp_>(args)...);
}

}

