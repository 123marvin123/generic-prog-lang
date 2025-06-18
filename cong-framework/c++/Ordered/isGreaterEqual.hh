#pragma once

#include "isGreaterEqual_dec.hh"

#include "../Boolean/BooleanStatic.hh"
#include "../Number/NaturalStatic.hh"
#include "../Boolean/BooleanDynamic.hh"
#include "../Number/NaturalDynamic.hh"

namespace Ordered {

struct SpecIsGreaterEqual {
    static constexpr auto name = "isGreaterEqual";
    static constexpr auto description = "p(1) $\\geq$ p(2) (is p(1) greater than or equal to p(2)?)";

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
        GenericImpl<cong::lang::core::NaturalStatic<0>>    >;
};


/*
 * Generic Implementation #1:
*/
template<>
struct SpecIsGreaterEqual::GenericImpl<cong::lang::core::NaturalStatic<0>>
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
            return ::Boolean::or_(::Ordered::isGreater(p1, p2), ::Object::isEqual(p1, p2));
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
IsGreaterEqual<Exp_...> isGreaterEqual(Exp_&&... args) 
{
    cong::lang::intern::EvalRequirements::Call<SpecIsGreaterEqual, Exp_...>
                ::call(std::forward<Exp_>(args)...);

    return ::cong::lang::bind(
        ::cong::lang::intern::Environment{},
        ::cong::lang::intern::Exp<::cong::lang::intern::FunctionImpl<DecIsGreaterEqual, SpecIsGreaterEqual>>{},
        std::forward<Exp_>(args)...);
}

}

