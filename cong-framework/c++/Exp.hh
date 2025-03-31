//
// Created by Marvin Haschker on 31.03.25.
//

#ifndef EXP_HH
#define EXP_HH

#include "Seq/Tuple.hh"
#include "Boolean/BooleanStatic.hh"
#include "Fun.hh"
#include "Undefined.hh"

#include <utility>

namespace cong::lang {
    namespace intern {
        class Environment {};

        template <class Impl_>
        class Exp : public Impl_
        {
            using Base_ = Impl_;
        public:
            template <typename... InitS_>
            constexpr Exp(InitS_&&... initS)
              : Base_{std::forward<InitS_>(initS)...}
            {}

            template <typename... ExpS_>
            constexpr auto operator()(ExpS_&&... expS) const
            {
                return bind(Environment{},
                            *this,
                            std::forward<ExpS_>(expS)...);
            }
        };

        struct IsExp
        {
        private:
            template <typename Plain_>
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
            struct Call
            {
                using Type = typename Dispatch<typename core::Plain::Call<Exp_>::Type>::Type;
            };
        };

#define CONG_LANG_LOCAL_FUNSTATICBYMEMBERFUN(Fun_, Default_) \
    namespace local \
    { \
        CONG_LANG_CORE_FUNSTATICBYMEMBERFUN(Fun_); \
    } \
    using Fun_ = core::FunByCond<core::FunByFunStatic<local::Fun_>, IsExp, Default_>;

        CONG_LANG_LOCAL_FUNSTATICBYMEMBERFUN(IsStateful, core::True);
        CONG_LANG_LOCAL_FUNSTATICBYMEMBERFUN(Arity, core::Invalid);
        CONG_LANG_LOCAL_FUNSTATICBYMEMBERFUN(IsEager, core::False);
        CONG_LANG_LOCAL_FUNSTATICBYMEMBERFUN(IsSpecific, core::False);

#undef CONG_LANG_LOCAL_FUNSTATICBYMEMBERFUN

#define CONG_LANG_LOCAL_FUNBYMEMBERFUN(Fun_) \
    namespace local \
    { \
        CONG_LANG_CORE_FUNBYMEMBERFUN(Fun_); \
    } \
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
                static constexpr Type
                call(Exp_ exp)
                {
                    return Base_::call(exp);
                }
            };
        };

        template <typename... ExpS_>
        typename Eval::template Call<ExpS_...>::Type eval(ExpS_&&... expS) {
            return Eval::template Call<ExpS_...>::call(std ::forward<ExpS_>(expS)...);
        }

        struct IsValid
        {
        private:
            template <typename Type_, typename Dummy_ = void>
            struct Dispatch
            {
                using Type = core::True;
            };
            template <typename Dummy_>
            struct Dispatch<core::Invalid, Dummy_>
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
            template <typename Type_, typename Dummy_ = void>
            struct Dispatch
            {
                using Type = core::True;
            };
            template <typename Dummy_>
            struct Dispatch<core::Undefined, Dummy_>
            {
                using Type = core::False;
            };
        public:
            template <typename Exp_>
            struct Call : Dispatch<typename core::Plain::Call<Exp_>::Type>
            {
            };
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
                static constexpr Type
                call(Exp_ exp, TupleOfExp_ tupleOfExp)
                {
                    return Eval_::call(Bind_{Environment{},
                                             ExpNew_{},
                                             tupleOfExp});
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
                static constexpr Type
                call(Exp_, core::Tuple<ExpS_...> tupleOfExp)
                {
                    return std::apply(Call_::call, tupleOfExp);
                }
            };
        };

    };

    };
};

#endif //EXP_HH
