#pragma once

#include "add_dec.hh"

#include "../Boolean/core/BooleanStatic.hh"
#include "../Undefined.hh"
#include "../Decls.hh"

namespace Number {

struct SpecAdd {
    static constexpr auto name = "add";
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
Add<Exp_...> add(Exp_&&... args) 
{
    cong::lang::intern::EvalRequirements::Call<SpecAdd, Exp_...>
                ::call(std::forward<Exp_>(args)...);

    return ::cong::lang::bind(
        ::cong::lang::intern::Environment{},
        ::cong::lang::intern::Exp<::cong::lang::intern::FunctionImpl<DecAdd, SpecAdd>>{},
        std::forward<Exp_>(args)...);
}

}

