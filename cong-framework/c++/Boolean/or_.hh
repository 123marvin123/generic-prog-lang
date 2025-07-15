#pragma once

#include "or__dec.hh"

#include "Boolean/BooleanStatic.hh"
#include "Boolean/BooleanDynamic.hh"

#include "Number/NaturalDynamic.hh"
#include "Number/NaturalStatic.hh"
#include "Number/core/NaturalStatic.hh"
#include "String/core/StringStatic.hh"

#include "Proj.hh"


namespace Boolean {

struct SpecOr_ {
    static constexpr cong::lang::core::StringStatic name = "or_";
    static constexpr cong::lang::core::StringStatic description = "";

    template<class Index_>
    struct Requirement
    {
        using Present = cong::lang::core::False;
        template<class...>
        struct Call
        {
            using Type = cong::lang::core::Undefined<"Req for Or_ not specified">;
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
            using Type = cong::lang::core::Undefined<"Generic impl for Or_ not specified">;
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
Or_<Exp_...> or_(Exp_&&... args) 
{
    return ::cong::lang::bind(
        ::cong::lang::intern::Environment{},
        ::cong::lang::intern::Exp<::cong::lang::intern::FunctionImpl<DecOr_, SpecOr_>>{},
        std::forward<Exp_>(args)...);
}

}

