#pragma once

#include "Exp.hh"
#include "Base.hh"

#include "Seq/core/Tuple.hh"
#include "Number/core/NaturalIntervalStatic.hh"
#include "Number/core/NaturalStatic.hh"
#include "Boolean/core/BooleanStatic.hh"

#include "CollectGenericImpls.hh"
#include "Fun.hh"
#include "Type.hh"
#include "Undefined.hh"
#include "ApplyMember.hh"

#include <utility>

namespace Map
{
    struct SpecMap;
}

namespace cong::lang
{
    namespace intern
    {
        namespace local
        {
            template<class Fn_>
            struct AnonymousFunctionImpl : Base
            {
                using Satisfies = core::Tuple<Map::SpecMap>;
                using Base_ = Base;

                using ReduceSpace = core::FunStaticMake<core::Zero>;
                using ReduceTime = core::FunStaticMake<core::One>;
                using ReduceValue = core::FunId;

            private:
                const Fn_& fn;

            public:

                explicit AnonymousFunctionImpl(const Fn_& lambda) : fn(lambda)
                {
                }

                template<typename... Args>
                auto operator()(Args&&... args)
                {
                    return bind(cong::lang::intern::Exp<AnonymousFunctionImpl>{*this}, std::forward<Args>(args)...);
                }

                using IsEager = core::FunStaticMake<core::False>;
                using IsSpecific = core::FunStaticMake<core::False>;

                CONG_LANG_INTERN_APPLYMEMBER_DEFAULT;

                struct ApplyValue
                {
                    template <typename Exp_, typename TupleOfExp_>
                    struct Call
                    {
                        static constexpr auto call(Exp_ exp, TupleOfExp_ tupleOfExp)
                        {
                            auto res = std::apply([&]<typename... Args>(Args&&... args)
                            {
                                return exp.fn(std::forward<Args>(args)...);
                            }, tupleOfExp);
                            return res;
                        }

                        using Type = std::invoke_result_t<decltype(call), Exp_, TupleOfExp_>;
                    };
                };
            };
        }

        template<typename T>
        using AnonymousFunctionImpl = Exp<local::AnonymousFunctionImpl<T>>;

        template<class Fn_>
        auto WrapLambda(Fn_&& f)
        {
            return AnonymousFunctionImpl<Fn_>{std::forward<Fn_>(f)};
        }

        struct EvalRequirements {
        private:
            template<class N, class IsAvail_, class IsStatic_, class Dec_, class... Args>
            struct Dispatch;

            template<class N, class Dec_, class IsStatic_, class... Args>
            struct Dispatch<N, core::False, IsStatic_, Dec_, Args...>
            {
                static constexpr auto call(Args&&...)
                {
                    return core::True{};
                }
            };

            // Case: requirement is static
            template<class N, class Dec_, class... Args>
            struct Dispatch<N, core::True, core::True, Dec_, Args...>
            {
                static constexpr auto call(Args&&... args)
                {
                    using R = typename Dec_::template Requirement<N>;
                    using Call_ = typename R::template Call<Args...>;
                    using Succ_ = typename core::Succ::Call<N>::Type;
                    using SuccReq_ = typename Dec_::template Requirement<Succ_>;

                    using SuccIsStatic_ = std::conditional_t<
                        std::is_same_v<typename SuccReq_::Present, core::True>,
                        typename core::IsStatic<typename SuccReq_::template Call<Args...>::Type >::Type,
                        core::False
                    >;

                    using A = decltype(Call_::call(std::forward<Args>(args)...));

                    if constexpr(std::is_same_v<typename IsDefined::Call<A>::Type, core::True>)
                    {
                        if constexpr(A::native() == false)
                        {
                            core::print_string<
                                core::concat<Dec_::name, ": requirement #",
                                core::num_to_string<N::native()+1>::value, " (name: ", R::name, "), not met: ", R::description>()
                            >();
                        }
                    }
                    else
                    {
                        core::print_string<
                        PrintUndefined::Call<
                            typename WrapUndefined::Call<
                                core::concat<"Could not evaluate requirement (name: ", R::name, ", desc: ",
                                                R::description, ")">(), A>::Type>::call()
                        >();
                    }


                    Dispatch<
                        Succ_,
                        typename SuccReq_::Present, SuccIsStatic_, Dec_, Args...
                    >::call(std::forward<Args>(args)...);


                    return A{};
                }
            };

            // Case: requirement is dynamic
            template<class N, class Dec_, class... Args>
            struct Dispatch<N, core::True, core::False, Dec_, Args...>
            {
                static auto call(Args&&... args)
                {
                    using R = typename Dec_::template Requirement<N>;
                    using Call_ = typename R::template Call<Args...>;
                    using Succ_ = typename core::Succ::Call<N>::Type;
                    using SuccReq_ = typename Dec_::template Requirement<Succ_>;

                    using SuccIsStatic_ = std::conditional_t<
                        std::is_same_v<typename SuccReq_::Present, core::True>,
                        typename core::IsStatic<typename SuccReq_::template Call<Args...>::Type >::Type,
                        core::False
                    >;

                    auto a = Call_::call(std::forward<Args>(args)...) ;

                    if constexpr (std::is_same_v<typename IsDefined::Call<decltype(a)>::Type, core::True>)
                    {
                        if (!core::Truthy::Call<decltype(a)>::call(a))
                        {
                            throw std::runtime_error(std::format("Requirement (name: {}, desc: {}) evaluated to false",
                                R::name.data, R::description.data));
                        }
                    }
                    else
                    {
                        throw std::runtime_error(std::format("Requirement (name: {}, desc: {}) is Undefined: {}",
                        R::name.data, R::description.data, a.str().data));
                    }

                    Dispatch<Succ_, typename SuccReq_::Present, SuccIsStatic_, Dec_, Args...>::call
                           (std::forward<Args>(args)...);

                    return a;
                }
            };

        public:

            template<class Dec_, class... Args>
            struct Call : Dispatch<
                core::Zero,
                typename Dec_::template Requirement<core::Zero>::Present,
                std::conditional_t<
                    std::is_same_v<typename Dec_::template Requirement<core::Zero>::Present, core::True>,
                    typename core::IsStatic<typename Dec_::template Requirement<core::Zero>::template Call<Args...>::Type
                     >::Type,
                    core::False
                >,
                Dec_, Args...>
            {
            };

            // Helper to unpack tuple types into parameter pack
            template<class Spec_, class TupleType>
            struct UnpackTuple;

            template<class Spec_, class... Types>
            struct UnpackTuple<Spec_, std::tuple<Types...>>
            {
                using Type = Call<Spec_, Types...>;
            };

        };

        template <class Dec_, class Spec_>
        class FunctionImpl
            : public Base
        {
            using Base_ = Base;

        public:
            using ReduceSpace = core::FunStaticMake<core::Zero>;
            using ReduceTime = core::FunStaticMake<core::One>; // @todo appropriate?
            using ReduceValue = core::FunId;

        private:
            using Length_ = typename core::Length::Call<typename Dec_::Params>::Type;
            using Interval_ = typename core::NaturalIntervalStaticFromNaturalStatic::Call<Length_>::Type;

        public:
            using Arity = core::FunStaticMake<Interval_>;

            // @todo make this a part of Dec_ / macro parameter?
            using IsEager = core::FunStaticMake<core::False>;
            using IsSpecific = core::FunStaticMake<core::False>;

            CONG_LANG_INTERN_APPLYMEMBER_DEFAULT;

            template <typename Stacktrace_>
            struct ApplyMember<Spec_, core::Zero, Stacktrace_>
            {
            private:
                // Dispatches are Fun

                /*template <typename Exp__, typename TupleOfExp__, typename Offset_>
                struct DispatchOffset;*/

                //template<typename Exp__, typename TupleOfExp__, typename ResultingType_, typename Stacktrace__, typename Available_>
                //struct DispatchStaticAvailable;

                template<typename TupleOfImpl_, typename Stacktrace__>
                struct DispatchDynamicAvailable;

                // There is at least one dynamic implementation available for
                // given arguments; we need to look for the best one at runtime
                CONG_LANG_CORE_FUN_PROPAGATE
                (DispatchDynamicAvailable,
                    (TupleOfImpl__, Stacktrace__), (),
                    (
                        (Base__, (SelectDynamicGenericImpl<TupleOfImpl__, Spec_, Stacktrace__>))
                    ),
                    Base__
                );

                // Static implementation is defined for given arguments;
                // propagate the call to that implementation, no need to search
                // for dynamic implementation because we prefer static eval
                // whenever possible
                CONG_LANG_CORE_FUN_PROPAGATE
                (DispatchStaticAvailable,
                    (Exp__, TupleOfExp__, Impl_, Stacktrace__, Available_), (),
                    (
                        (Base__, (Impl_))
                    ),
                    Base__
                );

                // static implementation not available for given arguments;
                // we need to look if dynamic implementation is available
                CONG_LANG_CORE_FUN_PROPAGATE
                (DispatchStaticAvailable,
                    (Exp__, TupleOfExp__, Type_, Stacktrace__), (core::False),
                    (
                        (DynamicImpls_, (typename CollectDynamicGenericImpls<Spec_, Exp__, TupleOfExp__>::Type)),
                        (Error_, (typename WrapUndefined::Call<core::concat<"No static implementation available for ", Spec_::name>(), Stacktrace__>::Type)),
                        (Base__, (DispatchDynamicAvailable<DynamicImpls_, Error_>))
                    ),
                    Base__
                );


            public:
                CONG_LANG_CORE_FUN_CALL_PROPAGATE
                (
                    (
                        (StaticAvailable_, (typename FindStaticGenericImpl<Spec_, Exp_, TupleOfExp_>::Type)),
                        //(Valid_, (typename core::And_::Call<typename IsDefined::Call<StaticAvailable_>::Type, typename IsExp::Call<StaticAvailable_>::Type>::Type)),
                        (Valid_, (typename IsDefined::Call<StaticAvailable_>::Type)),
                        (Base__, (DispatchStaticAvailable<Exp_, TupleOfExp_, StaticAvailable_, Stacktrace_, Valid_>))
                    ),
                    Base__
                );
            };

            struct RecursiveReduce
            {
            private:
                template<class TupleOfExp_>
                struct Dispatch;

                template<class... Args>
                struct Dispatch<core::Tuple<Args...>>
                {
                    using Type = core::Tuple<typename intern::ReduceValue::Call<Args>::Type...>;
                };

            public:
                template<class TupleOfExp_>
                struct Call : Dispatch<TupleOfExp_>
                {
                };
            };

            struct ApplyValue
            {
            private:
                // Dispatches are Fun

                // @todo allow to provide/process a tuple of (specific) implementations, as above
                template <typename Exp__, typename TupleOfExp__, typename Stacktrace_, typename Offset_>
                struct DispatchOffset;

                // specific implementation is defined for given arguments;
                // propagate the call to that implementation
                CONG_LANG_CORE_FUN_PROPAGATE
                (DispatchDefined, (Exp__, TupleOfExp__, Offset_, Apply_, Stacktrace_, IsDefined_), (),
                 (
                     (Base__, (Apply_))
                 ),
                 Base__
                );

                // specific implementation is not defined for given arguments;
                // re-try with specific implementation for predecessor in tuple of arguments
                CONG_LANG_CORE_FUN_PROPAGATE
                (DispatchDefined, (Exp__, TupleOfExp__, Offset_, Apply_, Stacktrace_), (core::False),
                 (
                     (Pred_, (typename core::Pred::Call<Offset_>::Type)),
                     (Error_, (typename WrapUndefined::Call<"Specific implementation not defined", Stacktrace_>::Type)),
                     (Base__, (DispatchOffset<Exp__, TupleOfExp__, Error_, Pred_>))
                 ),
                 Base__
                );

                // call specific implementation (converted to Fun) on given arguments, examine definedness
                CONG_LANG_CORE_FUN_PROPAGATE
                (DispatchImpl, (Exp__, TupleOfExp__, Offset_, Apply_, Stacktrace_), (),
                 (
                     (Type_, (typename Apply_::template Call<Exp__, TupleOfExp__>::Type)),
                     (Base__, (DispatchDefined<Exp__, TupleOfExp__, Offset_, Apply_, Stacktrace_, typename IsDefined::Call<Type_>::Type>))
                 ),
                 Base__
                );

                // standard case: try specific implementation for argument at position before the previous
                // note: arguments are counted from 1 (0 is Exp), thus use item N-1 of tuple if Offset is N
                CONG_LANG_CORE_FUN_PROPAGATE
                (DispatchOffset, (Exp__, TupleOfExp__, Stacktrace_, Offset_), (),
                 (
                     (Pred_, (typename core::Pred::Call<Offset_>::Type)),
                     (Arg_, (typename core::ItemAt::Call<TupleOfExp__, Pred_>::Type)),
                     (ArgPlain_, (typename core::Plain::Call<Arg_>::Type)),
                     (ArgVal_, (typename Eval::Call<ArgPlain_>::Type)),
                     (ValPlain_, (typename EnsureDefined<typename core::Plain::Call<ArgVal_>::Type,
                     core::concat<Spec_::name, " -> Argument is undefined: ", core::num_to_string<Offset_::native()
                     >::value>()>::Type)),
                     (Apply_, (typename ValPlain_::template ApplyMember<Spec_, Offset_, Stacktrace_>)),
                     (Base__, (DispatchImpl<Exp__, TupleOfExp__, Offset_, Apply_, Stacktrace_>))
                 ),
                 Base__
                );

                // final case: no further arguments (previously, first was checked),
                // use specific implementation of Exp itself
                CONG_LANG_CORE_FUN_PROPAGATE
                (DispatchOffset, (Exp__, TupleOfExp__, Stacktrace_), (core::NaturalStatic<0>),
                 (
                     (ArgPlain_, (typename core::Plain::Call<Exp__>::Type)),
                     (Base__, (typename ArgPlain_::template ApplyMember<Spec_, core::NaturalStatic<0>, Stacktrace_>)),
                 ),
                 Base__
                );

            public:
                // pick last (backwards order) specific impl. whose application is not Undefined
                // @todo instead, pick the "best" algorithm
                // starting the search from the end of the seq of arguments (length as initial offset)
                template <typename Exp_, typename TupleOfExp_>
                struct Call
                {
                private:
                    using RecursiveReduce_ = typename RecursiveReduce::template Call<TupleOfExp_>::Type;
                    using Length_ = typename core::Length::Call<RecursiveReduce_>::Type;
                    using Base__ = DispatchOffset<Exp_, RecursiveReduce_, void, Length_>;
                    using Call_ = typename Base__::template Call<Exp_, RecursiveReduce_>;

                public:
                    using Type = typename Call_::Type;
                    static constexpr Type call(Exp_ exp, TupleOfExp_ tupleOfExp)
                    {
                        auto res = std::apply([](auto&&... args)
                        {
                            return core::tupleNonRValRef(local::ReduceValue::Call<decltype(args)>::call(args)...);
                        }, tupleOfExp);
                        return Call_::call(exp, res);
                    }
                };
            };
        };
    };
};
