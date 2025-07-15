#pragma once

#include "isGreaterEqual_dec.hh"

#include "Boolean/BooleanStatic.hh"
#include "Boolean/BooleanDynamic.hh"

#include "Number/NaturalDynamic.hh"
#include "Number/NaturalStatic.hh"
#include "Number/core/NaturalStatic.hh"
#include "String/core/StringStatic.hh"

#include "Proj.hh"


namespace Ordered {

struct SpecIsGreaterEqual {
    static constexpr cong::lang::core::StringStatic name = "isGreaterEqual";
    static constexpr cong::lang::core::StringStatic description = "";

    template<class Index_>
    struct Requirement
    {
        using Present = cong::lang::core::False;
        template<class...>
        struct Call
        {
            using Type = cong::lang::core::Undefined<"Req for IsGreaterEqual not specified">;
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
            using Type = cong::lang::core::Undefined<"Generic impl for IsGreaterEqual not specified">;
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
IsGreaterEqual<Exp_...> isGreaterEqual(Exp_&&... args) 
{
    return ::cong::lang::bind(
        ::cong::lang::intern::Environment{},
        ::cong::lang::intern::Exp<::cong::lang::intern::FunctionImpl<DecIsGreaterEqual, SpecIsGreaterEqual>>{},
        std::forward<Exp_>(args)...);
}

}

