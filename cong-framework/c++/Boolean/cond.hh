#pragma once

#include "cond_dec.hh"

#include "Boolean/BooleanStatic.hh"
#include "Boolean/BooleanDynamic.hh"

#include "Number/NaturalDynamic.hh"
#include "Number/NaturalStatic.hh"
#include "Number/core/NaturalStatic.hh"
#include "String/core/StringStatic.hh"

#include "Proj.hh"


namespace Boolean {

struct SpecCond {
    static constexpr cong::lang::core::StringStatic name = "cond";
    static constexpr cong::lang::core::StringStatic description = "";

    template<class Index_>
    struct Requirement
    {
        using Present = cong::lang::core::False;
        template<class...>
        struct Call
        {
            using Type = cong::lang::core::Undefined<"Req for Cond not specified">;
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
            using Type = cong::lang::core::Undefined<"Generic impl for Cond not specified">;
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
struct SpecCond::GenericImpl<cong::lang::core::NaturalStatic<0>>
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
            static constexpr auto call_(std::tuple_element_t<0, TupleOfExp_> c , std::tuple_element_t<1, TupleOfExp_> a , std::tuple_element_t<2, TupleOfExp_> b, ...)
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
            static constexpr auto call_(std::tuple_element_t<0, TupleOfExp_> c , std::tuple_element_t<1, TupleOfExp_> a , std::tuple_element_t<2, TupleOfExp_> b, ...)
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
        static constexpr auto call_(std::tuple_element_t<0, TupleOfExp_> c , std::tuple_element_t<1, TupleOfExp_> a , std::tuple_element_t<2, TupleOfExp_> b, ...)
        {
            
            using PlainP2 = std::decay_t<decltype(a)>;
            using PlainP3 = std::decay_t<decltype(b)>;

            using IsSame_ = std::is_same<PlainP2, PlainP3>;

            if constexpr (IsSame_::value) {
                return c.native() ? a : b;
            } else {
                return c.native() ? std::variant<PlainP2, PlainP3>{std::in_place_index<0>, a}
                                           : std::variant<PlainP2, PlainP3>{std::in_place_index<1>, b};
            }
        
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
Cond<Exp_...> cond(Exp_&&... args) 
{
    cong::lang::intern::EvalRequirements::Call<SpecCond, Exp_...>
                ::call(std::forward<Exp_>(args)...);

    return ::cong::lang::bind(
        ::cong::lang::intern::Environment{},
        ::cong::lang::intern::Exp<::cong::lang::intern::FunctionImpl<DecCond, SpecCond>>{},
        std::forward<Exp_>(args)...);
}

}

