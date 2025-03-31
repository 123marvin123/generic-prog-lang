#pragma once

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
            /**
             * @brief Constructs an Exp instance by forwarding initialization parameters.
             *
             * This constexpr constructor accepts a variadic set of arguments and forwards them 
             * to the base class constructor using perfect forwarding. This enables compile-time 
             * instantiation of expression objects with custom initialization.
             *
             * @tparam InitS_ The types of the initialization parameters.
             * @param initS One or more initialization arguments forwarded to the base class.
             */
            constexpr Exp(InitS_&&... initS)
              : Base_{std::forward<InitS_>(initS)...}
            {}

            template <typename... ExpS_>
            /**
             * @brief Binds the current expression with provided subexpressions.
             *
             * This operator overload forwards the current expression and the given subexpressions
             * into the `bind` function, using a default-constructed environment. The result is a new
             * expression resulting from this binding.
             *
             * @tparam ExpS_ Variadic types of the subexpressions.
             * @param expS Subexpression arguments to bind with the current expression.
             * @return The result of binding the current expression with the provided subexpressions.
             */
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
                /**
                 * @brief Evaluates the provided expression.
                 *
                 * Delegates the evaluation of the given expression to the Base_ implementation
                 * and returns its computed result.
                 *
                 * @param exp The expression to evaluate.
                 * @return The result of evaluating the expression.
                 */
                static constexpr Type
                call(Exp_ exp)
                {
                    return Base_::call(exp);
                }
            };
        };

        template <typename... ExpS_>
        /**
         * @brief Evaluates one or more expressions.
         *
         * Forwards the provided expression(s) to the evaluation mechanism defined by the Eval structure.
         * The function invokes the static call method of Eval::Call, preserving the value category of each
         * argument to compute and return the evaluation result.
         *
         * @tparam ExpS_ Types of the expression arguments.
         * @param expS One or more expressions to evaluate.
         * @return The result of evaluating the provided expression(s) as defined by the evaluation framework.
         */
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
                /**
                 * @brief Evaluates a bound expression in a fresh environment.
                 *
                 * Constructs a binding by combining a default-constructed Environment, a new expression (ExpNew_),
                 * and a tuple of subexpressions (tupleOfExp). This binding is then evaluated via Eval_::call,
                 * with the result returned as a value of type Type.
                 *
                 * @param exp An expression whose type is used for overload resolution (not directly used).
                 * @param tupleOfExp A tuple of expressions that are bound and evaluated.
                 * @return Type The result of evaluating the bound expression.
                 */
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
                /**
                 * @brief Forwards a tuple of expressions to the underlying call operation.
                 *
                 * This function unpacks the provided tuple of expressions and passes them as arguments
                 * to the call method defined in Call_, returning its result.
                 *
                 * @param Exp_ A type tag used for overload resolution associated with the current expression context.
                 * @param tupleOfExp A tuple containing expressions whose elements are forwarded to the call operator.
                 * @return Type The result obtained by applying Call_::call to the unpacked tuple elements.
                 */
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
