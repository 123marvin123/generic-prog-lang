#pragma once

#include "sub_dec.hh"

#include "Boolean/BooleanStatic.hh"
#include "Boolean/BooleanDynamic.hh"

#include "Number/NaturalDynamic.hh"
#include "Number/NaturalStatic.hh"
#include "Number/core/NaturalStatic.hh"
#include "String/core/StringStatic.hh"

#include "Proj.hh"


namespace Number {

struct SpecSub {
    static constexpr cong::lang::core::StringStatic name = "sub";
    static constexpr cong::lang::core::StringStatic description = "";

    template<class Index_>
    struct Requirement
    {
        using Present = cong::lang::core::False;
        template<class...>
        struct Call
        {
            using Type = cong::lang::core::Undefined<"Req for Sub not specified">;
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
            using Type = cong::lang::core::Undefined<"Generic impl for Sub not specified">;
            static constexpr Type call(...);
        };
    };

    template<cong::lang::core::StringStatic Name>
    struct NameToRequirement;

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

