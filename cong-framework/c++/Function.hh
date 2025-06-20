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

namespace cong::lang
{
    namespace intern
    {
        template<class Exp_, core::StringStatic S>
        struct EnsureDefined
        {
        private:
            using IsUndefined_ = typename core::Not_::Call<typename IsDefined::Call<Exp_>::Type>::Type;
            using IsExp_ = typename IsExp::Call<Exp_>::Type;

            static consteval auto call()
            {
                if constexpr (std::is_same_v<IsUndefined_, core::True>)
                {
                    core::print_string<PrintUndefined::Call<typename WrapUndefined::Call<S, Exp_>::Type>::call()>();
                    return false;
                }

                if constexpr (std::is_same_v<IsExp_, core::False>)
                {
                    core::print_string<S>();
                    return false;
                }

                return true;
            }
        public:
            using Type = std::conditional_t<call(), Exp_, Exp_>;
        };

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
                    using Call_ = typename Dec_::template Requirement<N>::template Call<Args...>;
                    using Succ_ = typename core::Succ::Call<N>::Type;
                    using SuccReq_ = typename Dec_::template Requirement<Succ_>;

                    using SuccIsStatic_ = std::conditional_t<
                        std::is_same_v<typename SuccReq_::Present, core::True>,
                        typename core::IsStatic<typename SuccReq_::template Call<Args...>::Type >::Type,
                        core::False
                    >;

                    using A = decltype(Call_::call(std::forward<Args>(args)...));
                    using B = decltype(Dispatch<
                        Succ_,
                        typename SuccReq_::Present, SuccIsStatic_, Dec_, Args...
                    >::call(std::forward<Args>(args)...));

                    if constexpr(A::native() == false)
                    {
                        using R = typename Dec_::template Requirement<N>;
                        core::print_string<
                            core::concat<Dec_::name, ": requirement #",
                            core::num_to_string<N::native()+1>::value, " (name: ", R::name, "), not met: ", R::description>()
                        >();
                    }
                    else if constexpr (B::native() == false)
                    {
                        static_assert(A::native() && B::native(), "Other requirement not met");

                     }

                    return A{};
                }
            };

            // Case: requirement is dynamic
            template<class N, class Dec_, class... Args>
            struct Dispatch<N, core::True, core::False, Dec_, Args...>
            {
                static auto call(Args&&... args)
                {
                    using Call_ = typename Dec_::template Requirement<N>::template Call<Args...>;
                    using Succ_ = typename core::Succ::Call<N>::Type;
                    using SuccReq_ = typename Dec_::template Requirement<Succ_>;

                    using SuccIsStatic_ = std::conditional_t<
                        std::is_same_v<typename SuccReq_::Present, core::True>,
                        typename core::IsStatic<typename SuccReq_::template Call<Args...>::Type >::Type,
                        core::False
                    >;

                    auto a = Call_::call(std::forward<Args>(args)...) ;
                    auto b = Dispatch<Succ_, typename SuccReq_::Present, SuccIsStatic_, Dec_, Args...>::call
                           (std::forward<Args>(args)...);

                    if (!core::Truthy::Call<decltype(a)>::call(a) || !core::Truthy::Call<decltype(b)>::call(b))
                    {
                        throw std::runtime_error("Requirement not met");
                    }

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

            template <>
            struct ApplyMember<Spec_, core::Zero>
            {
            private:
                // Dispatches are Fun

                /*template <typename Exp__, typename TupleOfExp__, typename Offset_>
                struct DispatchOffset;*/

                template<typename Exp__, typename TupleOfExp__, typename ResultingType_, typename Available_>
                struct DispatchStaticAvailable;

                template<typename TupleOfImpl_>
                struct DispatchDynamicAvailable;

                // There is at least one dynamic implementation available for
                // given arguments; we need to look for the best one at runtime
                CONG_LANG_CORE_FUN_PROPAGATE
                (DispatchDynamicAvailable,
                    (TupleOfImpl__), (),
                    (
                        (Base__, (SelectDynamicGenericImpl<TupleOfImpl__, Spec_>))
                    ),
                    Base__
                );

                // Static implementation is defined for given arguments;
                // propagate the call to that implementation, no need to search
                // for dynamic implementation because we prefer static eval 
                // whenever possible
                CONG_LANG_CORE_FUN_PROPAGATE
                (DispatchStaticAvailable, 
                    (Exp__, TupleOfExp__, Impl_, Available_), (),
                    (
                        (Base__, (Impl_))
                    ), 
                    Base__
                );

                // static implementation not available for given arguments;
                // we need to look if dynamic implementation is available
                CONG_LANG_CORE_FUN_PROPAGATE
                (DispatchStaticAvailable,
                    (Exp__, TupleOfExp__, Type_), (core::False),
                    (
                        (DynamicImpls_, (typename CollectDynamicGenericImpls<Spec_, Exp__, TupleOfExp__>::Type)),
                        (Base__, (DispatchDynamicAvailable<DynamicImpls_>))
                    ),
                    Base__
                );


            public:
                CONG_LANG_CORE_FUN_CALL_PROPAGATE
                (
                    (
                        (StaticAvailable_, (typename FindStaticGenericImpl<Spec_, Exp_, TupleOfExp_>::Type)),
                        (Base__, (DispatchStaticAvailable<Exp_, TupleOfExp_, StaticAvailable_, typename IsDefined::Call<StaticAvailable_>::Type>))
                    ),
                    Base__
                );
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
                     (ValPlain_, (typename EnsureDefined<typename core::Plain::Call<ArgVal_>::Type, "Argument is undefined">::Type)),
                     (Apply_, (typename ValPlain_::template ApplyMember<Spec_, Offset_>)),
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
                     (Base__, (typename ArgPlain_::template ApplyMember<Spec_, core::NaturalStatic<0>>)), // TODO: stacktrace weiter reichen?
                 ),
                 Base__
                );

            public:
                // pick last (backwards order) specific impl. whose application is not Undefined
                // @todo instead, pick the "best" algorithm
                // starting the search from the end of the seq of arguments (length as initial offset)
                CONG_LANG_CORE_FUN_CALL_PROPAGATE
                (
                    (
                        (Length_, (typename core::Length::Call<TupleOfExp_>::Type)),
                        (Base__, (DispatchOffset<Exp_,
                            TupleOfExp_,
                            void,
                            Length_>))
                    ),
                    Base__
                );
            };
        };
    };
};
