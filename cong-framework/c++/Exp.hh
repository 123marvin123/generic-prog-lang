#pragma once

#include "Boolean/core/BooleanStatic.hh"
#include "Decls.hh"
#include "Fun.hh"
#include "Seq/core/Tuple.hh"
#include "Undefined.hh"

#include <utility>

namespace cong::lang
{
    namespace intern
    {
        class Environment
        {
        };

        template <class Impl_>
        class Exp : public Impl_
        {
            using Base_ = Impl_;

        public:
            template <typename... InitS_>
            constexpr Exp(InitS_&&... initS) : Base_{std::forward<InitS_>(initS)...}
            {
            }

            template <typename... ExpS_>
            constexpr auto operator()(ExpS_&&... expS) const
            {
                return bind(Environment{}, *this, std::forward<ExpS_>(expS)...);
            }
        };

        struct IsExp
        {
        private:
            template <typename>
            struct Dispatch
            {
                using Type = core::False;
            };

            template <class Impl_>
            struct Dispatch<Exp<Impl_>>
            {
                using Type = core::True;
            };

        public:
            template <typename Exp_>
            struct Call : Dispatch<typename core::Plain::Call<Exp_>::Type>
            {
            };
        };

#define CONG_LANG_LOCAL_FUNSTATICBYMEMBERFUN(Fun_, Default_)                                                           \
    namespace local                                                                                                    \
    {                                                                                                                  \
        CONG_LANG_CORE_FUNSTATICBYMEMBERFUN(Fun_);                                                                     \
    }                                                                                                                  \
    using Fun_ = core::FunByCond<core::FunByFunStatic<local::Fun_>, IsExp, Default_>;

        CONG_LANG_LOCAL_FUNSTATICBYMEMBERFUN(IsStateful, core::True);
        CONG_LANG_LOCAL_FUNSTATICBYMEMBERFUN(Arity, core::Invalid);
        CONG_LANG_LOCAL_FUNSTATICBYMEMBERFUN(IsEager, core::False);
        CONG_LANG_LOCAL_FUNSTATICBYMEMBERFUN(IsSpecific, core::False);

#undef CONG_LANG_LOCAL_FUNSTATICBYMEMBERFUN

#define CONG_LANG_LOCAL_FUNBYMEMBERFUN(Fun_)                                                                           \
    namespace local                                                                                                    \
    {                                                                                                                  \
        CONG_LANG_CORE_FUNBYMEMBERFUN(Fun_);                                                                           \
    }                                                                                                                  \
    using Fun_ = core::FunByCond<local::Fun_, IsExp, core::Invalid>;

        CONG_LANG_LOCAL_FUNBYMEMBERFUN(ReduceSpace);
        CONG_LANG_LOCAL_FUNBYMEMBERFUN(ReduceTime);
        CONG_LANG_LOCAL_FUNBYMEMBERFUN(ReduceValue);

        CONG_LANG_LOCAL_FUNBYMEMBERFUN(ApplySpace);
        CONG_LANG_LOCAL_FUNBYMEMBERFUN(ApplyTime);
        CONG_LANG_LOCAL_FUNBYMEMBERFUN(ApplyValue);

#undef CONG_LANG_LOCAL_FUNBYMEMBERFUN

        struct Eval
        {
            template <typename Exp_>
            struct Call
            {
            private:
                using Base_ = ReduceValue::Call<Exp_>;

            public:
                using Type = typename Base_::Type;

                static constexpr Type call(Exp_ exp) { return Base_::call(exp); }
            };
        };

        template <typename... ExpS_>
        typename Eval::Call<ExpS_...>::Type eval(ExpS_&&... expS)
        {
            return Eval::Call<ExpS_...>::call(std::forward<ExpS_>(expS)...);
        }

        struct IsValid
        {
        private:
            template <typename Type_>
            struct Dispatch
            {
                using Type = core::True;
            };

            template <>
            struct Dispatch<core::Invalid>
            {
                using Type = core::False;
            };

        public:
            template <typename Exp_>
            struct Call : Dispatch<typename core::Plain::Call<Exp_>::Type>
            {
            };
        };

        struct IsDefined
        {
        private:
            template <bool>
            struct Dispatch
            {
                using Type = core::True;
            };

            template <>
            struct Dispatch<true>
            {
                using Type = core::False;
            };

        public:
            template <typename Exp_>
            struct Call : Dispatch<std::is_base_of_v<core::UndefinedTag, typename core::Plain::Call<Exp_>::Type>>
            {
            };
        };

        struct WrapUndefined
        {
        private:
            template<core::StringStatic S, class IsDefined_, class Stacktrace_>
            struct Dispatch
            {
                using Type = core::Undefined<S, Stacktrace_>;
            };

            template<core::StringStatic S, class Stacktrace_>
            struct Dispatch<S, core::True, Stacktrace_>
            {
                using Type = core::Undefined<S>;
            };

        public:
            template<core::StringStatic S, class Stacktrace_>
            struct Call : Dispatch<S, typename IsDefined::Call<Stacktrace_>::Type, Stacktrace_>
            {

            };
        };

        struct PrintUndefined
        {
        private:
            template<class Stacktrace_, core::StringStatic Sep_, class IsDefined_>
            struct Dispatch
            {
                static consteval auto call()
                {
                    return core::StringStatic{""};
                }
            };

            template<class Stacktrace_, core::StringStatic Sep_>
            struct Dispatch<Stacktrace_, Sep_, core::False>
            {
                static consteval auto call()
                {
                    return core::concat<
                        core::concat<Stacktrace_::str(), Sep_>(),
                        Call<typename Stacktrace_::Parent>::call()
                    >();
                }
            };
        public:
            template<class Stacktrace_, core::StringStatic Separator_ = "; ">
            struct Call : Dispatch<Stacktrace_, Separator_, typename IsDefined::Call<Stacktrace_>::Type>
            {

            };
        };

        struct TransformExp // is a Fun(Exp)Dynamic
        {
        private:
            template <typename PlainTupleOfExp_>
            struct Dispatch;

            template <typename... ItemS_>
            struct Dispatch<core::Tuple<ItemS_...>>
            {
                template <typename Exp_, typename TupleOfExp_>
                struct Call
                {
                    using Type = core::Tuple<typename ApplyValue::Call<Exp_, ItemS_>::Type...>;

                    static constexpr Type call(Exp_ exp, TupleOfExp_ tupleOfExp)
                    {
                        return std::apply([&exp](ItemS_&... itemS)
                                          { return core::tuple(ApplyValue ::Call<Exp_, ItemS_>::call(exp, itemS)...); },
                                          tupleOfExp);
                    }
                };
            };

        public:
            template <typename Exp_, typename TupleOfExp_>
            struct Call
            {
                using Tuple_ = typename core::Plain::Call<TupleOfExp_>::Type;
                using Base_ = Dispatch<Tuple_>;

                using Type = typename Base_::template Call<Exp_, TupleOfExp_>::Type;

                static constexpr Type call(Exp_ exp, TupleOfExp_ tupleOfExp)
                {
                    return Base_::template Call<Exp_, TupleOfExp_>::call(exp, tupleOfExp);
                }
            };
        };

        template <typename BoolStatic_, typename Fun_, typename ExpType_>
        struct CondEval;

        template <typename Fun_, typename ExpType_>
        struct CondEval<core::True, Fun_, ExpType_>
        {
        private:
            static_assert(std::is_same_v<typename IsExp::Call<ExpType_>::Type, core::True>, "Not an expression");
            static_assert(std::is_same_v<typename IsValid::Call<ExpType_>::Type, core::True>, "Expression not valid");
            static_assert(std::is_same_v<typename IsDefined::Call<ExpType_>::Type, core::True>,
                          "Expression not defined");

        public:
            using Type = typename Eval::Call<ExpType_>::Type;
            static constexpr Type call(Fun_&& f) { return eval(std::forward<Fun_>(f)()); }
        };

        namespace local
        {
            template <class ExpNew_>
            struct ApplyReplace
            {
                template <typename Exp_, typename TupleOfExp_>
                struct Call
                {
                private:
                    using Bind_ = Exp<lang::local::Bind<Environment, ExpNew_, TupleOfExp_>>;
                    using Eval_ = Eval::Call<Bind_>;

                public:
                    using Type = typename Eval_::Type;

                    static constexpr Type call(Exp_ exp, TupleOfExp_ tupleOfExp)
                    {
                        return Eval_::call(Bind_{Environment{}, ExpNew_{}, tupleOfExp});
                    }
                };
            };

            template <class Fun_>
            struct ApplyByFun
            {
                template <typename Exp_, typename TupleOfExp_>
                struct Call;

                template <typename Exp_, typename... ExpS_>
                struct Call<Exp_, core::Tuple<ExpS_...>>
                {
                private:
                    using Call_ = typename Fun_::template Call<ExpS_...>;

                public:
                    using Type = typename Call_::Type;

                    static constexpr Type call(Exp_, core::Tuple<ExpS_...> tupleOfExp)
                    {
                        return std::apply(Call_::call, tupleOfExp);
                    }
                };
            };
        }; // namespace local
    }; // namespace intern
}; // namespace cong::lang
