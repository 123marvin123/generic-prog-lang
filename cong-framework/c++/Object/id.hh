#pragma once

#include "id_dec.hh"

#include "Boolean/BooleanStatic.hh"
#include "Number/NaturalStatic.hh"
#include "Boolean/BooleanDynamic.hh"
#include "Number/NaturalDynamic.hh"

namespace Object {

struct SpecId {
    static constexpr auto name = "id";
    static constexpr auto description = "p(1) (the argument itself)";

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
struct SpecId::GenericImpl<cong::lang::core::NaturalStatic<0>>
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
            static constexpr auto call_(std::tuple_element_t<0, TupleOfExp_> p1, ...)
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
            static constexpr auto call_(std::tuple_element_t<0, TupleOfExp_> p1, ...)
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
        static constexpr auto call_(std::tuple_element_t<0, TupleOfExp_> p1, ...)
        {
            return p1;
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
Id<Exp_...> id(Exp_&&... args) 
{
    cong::lang::intern::EvalRequirements::Call<SpecId, Exp_...>
                ::call(std::forward<Exp_>(args)...);

    return ::cong::lang::bind(
        ::cong::lang::intern::Environment{},
        ::cong::lang::intern::Exp<::cong::lang::intern::FunctionImpl<DecId, SpecId>>{},
        std::forward<Exp_>(args)...);
}

}

