#pragma once

#include "isEqual_dec.hh"
#include "String/core/StringStatic.hh"


namespace Object {

struct SpecIsEqual {
    static constexpr cong::lang::core::StringStatic name = "isEqual";
    static constexpr cong::lang::core::StringStatic description = "";

    template<class Index_>
    struct Requirement
    {
        using Present = cong::lang::core::False;
        template<class...>
        struct Call
        {
            using Type = cong::lang::core::Undefined<"Req for IsEqual not specified">;
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
            using Type = cong::lang::core::Undefined<"Generic impl for IsEqual not specified">;
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
IsEqual<Exp_...> isEqual(Exp_&&... args) 
{
    return ::cong::lang::bind(
        ::cong::lang::intern::Environment{},
        ::cong::lang::intern::Exp<::cong::lang::intern::FunctionImpl<DecIsEqual, SpecIsEqual>>{},
        std::forward<Exp_>(args)...);
}

}

