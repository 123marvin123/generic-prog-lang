#pragma once

#include "isModelOf_dec.hh"

#include "Boolean/BooleanStatic.hh"
#include "Boolean/BooleanDynamic.hh"

#include "Number/NaturalDynamic.hh"
#include "Number/NaturalStatic.hh"
#include "Number/core/NaturalStatic.hh"
#include "String/core/StringStatic.hh"

#include "Proj.hh"


namespace Object {

struct SpecIsModelOf {
    static constexpr cong::lang::core::StringStatic name = "isModelOf";
    static constexpr cong::lang::core::StringStatic description = "does object p(1) model concept p(2)?";

    template<class Index_>
    struct Requirement
    {
        using Present = cong::lang::core::False;
        template<class...>
        struct Call
        {
            using Type = cong::lang::core::Undefined<"Req for IsModelOf not specified">;
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
            using Type = cong::lang::core::Undefined<"Generic impl for IsModelOf not specified">;
            static constexpr Type call(...);
        };
    };

    template<cong::lang::core::StringStatic Name>
    struct NameToRequirement;

    using GenericImpls = cong::lang::core::Tuple<
        GenericImpl<cong::lang::core::NaturalStatic<0>>    >;
};


/*
 * Generic Implementation #1:
*/
template<>
struct SpecIsModelOf::GenericImpl<cong::lang::core::NaturalStatic<0>>
{
    using Present = cong::lang::core::True;
    template<typename Exp_, typename TupleOfExp_>
    struct Call;

private:
    struct ApplyTime_ {
        template<typename Exp_, typename... Args>
        struct Call;

        template<typename Exp_, typename... Args>
        struct Call<Exp_, cong::lang::core::Tuple<Args...>>
        {
        private:
            using TupleOfExp_ = cong::lang::core::Tuple<Args...>;
            static constexpr auto call_(std::tuple_element_t<0, TupleOfExp_> p1 , std::tuple_element_t<1, TupleOfExp_> p2, ...)
            {
                return cong::lang::NaturalStatic<cong::lang::core::natInf>{};
            }
        public:
            using Type = std::invoke_result_t<decltype(call_), Args...>;
            static constexpr Type call(Exp_ exp, TupleOfExp_ args) {
                return std::apply(call_, args);
            }
        };
    };

    struct ApplySpace_ {
        template<typename Exp_, typename... Args>
        struct Call;

        template<typename Exp_, typename... Args>
        struct Call<Exp_, cong::lang::core::Tuple<Args...>>
        {
        private:
            using TupleOfExp_ = cong::lang::core::Tuple<Args...>;
            static constexpr auto call_(std::tuple_element_t<0, TupleOfExp_> p1 , std::tuple_element_t<1, TupleOfExp_> p2, ...)
            {
                return cong::lang::NaturalStatic<cong::lang::core::natInf>{};
            }
        public:
            using Type = std::invoke_result_t<decltype(call_), Args...>;
            static constexpr Type call(Exp_ exp, TupleOfExp_ args) {
                return std::apply(call_, args);
            }
        };
    };

public:
    template<typename Exp_, typename... Args>
    struct Call<Exp_, cong::lang::core::Tuple<Args...>>
    {
    private:
        using TupleOfExp_ = cong::lang::core::Tuple<Args...>;
        static constexpr auto call_(std::tuple_element_t<0, TupleOfExp_> p1 , std::tuple_element_t<1, TupleOfExp_> p2, ...)
        {
            
            using Plain_ = typename cong::lang::core::Plain::Call<decltype(p2)>::Type;
            if constexpr (!std::is_base_of_v<cong::lang::ConceptTag, Plain_>)
            {
                return cong::lang::BooleanStatic<false>{}; // Not a concept
            }

            return cong::lang::BooleanStatic<
                cong::lang::core::IsModelOf::Call<
                    typename cong::lang::intern::Eval::Call<decltype(p1)>::Type,
                    typename cong::lang::intern::Eval::Call<decltype(p2)>::Type
                >::Type::native()
            >{};
        
        }
    public:
        using ApplyTime = ApplyTime_;
        using ApplySpace = ApplySpace_;
        using Type = std::invoke_result_t<decltype(call_), Args...>;
        static constexpr Type call(Exp_ exp, TupleOfExp_ args) {
            return std::apply(call_, args);
        }
    };
};
template <typename... Exp_>
constexpr
IsModelOf<Exp_...> isModelOf(Exp_&&... args) 
{
    return ::cong::lang::bind(
        ::cong::lang::intern::Environment{},
        ::cong::lang::intern::Exp<::cong::lang::intern::FunctionImpl<DecIsModelOf, SpecIsModelOf>>{},
        std::forward<Exp_>(args)...);
}

}

