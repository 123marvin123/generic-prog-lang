#pragma once

#include "Exp.hh"
#include "Base.hh"

#include "Seq/core/Tuple.hh"
#include "Number/core/NaturalIntervalStatic.hh"
#include "Number/core/NaturalStatic.hh"
#include "Boolean/BooleanStatic.hh"

#include "Fun.hh"
#include "Type.hh"
#include "Undefined.hh"
#include "ApplyMember.hh"

#include <utility>

namespace cong::lang
{
    namespace intern
    {
        struct EvalRequirements {
        private:
            template<unsigned int N, class IsAvail_, class Dec_, class... Args>
            struct Dispatch;

            template<unsigned int N, class Dec_, class... Args>
            struct Dispatch<N, False, Dec_, Args...>
            {
                static constexpr auto call(Args&&...)
                {
                    return True{};
                }
            };

            template<unsigned int N, class Dec_, class... Args>
            struct Dispatch<N, True, Dec_, Args...>
            {
                static constexpr auto call(Args&&... args)
                {
                    using Call_ = typename Dec_::template Requirement<N>::template Call<Args...>;

                    auto a = Call_::call(std::forward<Args>(args)...) ;
                    auto b = Dispatch<N + 1, typename Dec_::template Requirement<N + 1>::Present, Dec_, Args...>::call
                           (std::forward<Args>(args)...);

                    return core::Truthy::Call<decltype(a)>::call(a) &&
                        core::Truthy::Call<decltype(b)>::call(b);
                }
            };

        public:
            template<class Dec_, class... Args>
            struct Call : Dispatch<0, typename Dec_::template Requirement<0>::Present, Dec_, Args...>
            {
            };
        };

        template <class Dec_, class Spec_>
        class FunctionImpl
            : public Base
        {
            using Base_ = Base;

        public:
            using ReduceSpace = core::FunStaticMake<core::NaturalStatic<0>>;
            using ReduceTime = core::FunStaticMake<core::NaturalStatic<1>>; // @todo appropriate?
            using ReduceValue = core::FunId;

        private:
            using Length_ = typename core::Length::Call<typename Dec_::ParamTupleOfConcept>::Type;
            using Interval_ = typename core::NaturalIntervalStaticFromNaturalStatic::Call<Length_>::Type;

        public:
            using Arity = core::FunStaticMake<Interval_>;

            // @todo make this a part of Dec_ / macro parameter?
            using IsEager = core::FunStaticMake<core::False>;
            using IsSpecific = core::FunStaticMake<core::False>;

            CONG_LANG_INTERN_APPLYMEMBER_DEFAULT;

            template <>
            struct ApplyMember<Spec_, core::NaturalStatic<0>>
            {
            private:
                // Dispatches are Fun

                template <typename Exp__, typename TupleOfExp__, typename TupleOfImpl_, typename Offset_>
                struct DispatchOffset;

                // generic implementation is defined for given arguments;
                // propagate the call to that implementation
                CONG_LANG_CORE_FUN_PROPAGATE
                (DispatchDefined,
                 (Exp__, TupleOfExp__, TupleOfImpl_, Offset_, Apply_, Type_), (),
                 (
                     (Base__, (Apply_))
                 ),
                 Base__
                );

                // generic implementation is not defined for given arguments;
                // re-try with predecessor in tuple of generic implementations
                CONG_LANG_CORE_FUN_PROPAGATE
                (DispatchDefined,
                 (Exp__, TupleOfExp__, TupleOfImpl_, Offset_, Apply_), (core::Undefined),
                 (
                     (Pred_, (typename core::Pred::Call<Offset_>::Type)),
                     (Base__, (DispatchOffset<Exp__, TupleOfExp__, TupleOfImpl_, Pred_>))
                 ),
                 Base__
                );

                // call generic implementation (converted to Fun) on given arguments, examine definedness
                CONG_LANG_CORE_FUN_PROPAGATE
                (DispatchImpl,
                 (Exp__, TupleOfExp__, TupleOfImpl_, Offset_, Apply_), (),
                 (
                     (Type_, (typename Apply_::template Call<Exp__, TupleOfExp__>::Type)),
                     (Base__, (DispatchDefined<Exp__, TupleOfExp__, TupleOfImpl_, Offset_, Apply_, Type_>))
                 ),
                 Base__
                );

                // standard case: try generic implementation at position before the previous
                CONG_LANG_CORE_FUN_PROPAGATE
                (DispatchOffset,
                 (Exp__, TupleOfExp__, TupleOfImpl_, Offset_), (),
                 (
                     (Pred_, (typename core::Pred::Call<Offset_>::Type)),
                     (Impl_, (typename core::ItemAt::Call<TupleOfImpl_, Pred_>::Type)),
                     (ImplPlain_, (typename core::Plain::Call<Impl_>::Type)),
                     (Apply_, (local::ApplyReplace<ImplPlain_>)), // @todo requires ImplPlain_ to be static - add check?
                     (Base__, (DispatchImpl<Exp__, TupleOfExp__, TupleOfImpl_, Offset_, Apply_>))
                 ),
                 Base__
                );

                // final case: no further generic implementation (previous offset was zero)
                CONG_LANG_CORE_FUN_PROPAGATE
                (DispatchOffset,
                 (Exp__, TupleOfExp__, TupleOfImpl_), (core::NaturalStatic<0>),
                 (
                     (Make_, (core::FunStaticMake<core::Undefined>)),
                     (Base__, (local::ApplyByFun<Make_>))
                 ),
                 Base__
                );

            public:
                // pick last (backwards order) generic impl. whose application is not Undefined
                // @todo instead, pick the "best" algorithm
                // starting the search from the end of the seq of generic impl. (length as initial offset)
                CONG_LANG_CORE_FUN_CALL_PROPAGATE
                (
                    (
                        (TupleOfExpReqEquiv_, (typename Spec_::ResultTupleOfExpReqEquiv)),
                        (Length_, (typename core::Length::Call<TupleOfExpReqEquiv_>::Type)),
                        (Base__, (DispatchOffset<Exp_,
                            TupleOfExp_,
                            TupleOfExpReqEquiv_,
                            Length_>))
                    ),
                    Base__
                );
            };

            struct ApplyValue
            {
            private:
                // Dispatches are Fun

                // @todo allow to provide/process a tuple of (specific) implementations, as above
                template <typename Exp__, typename TupleOfExp__, typename Offset_>
                struct DispatchOffset;

                // specific implementation is defined for given arguments;
                // propagate the call to that implementation
                CONG_LANG_CORE_FUN_PROPAGATE
                (DispatchDefined, (Exp__, TupleOfExp__, Offset_, Apply_, Type_), (),
                 (
                     (Base__, (Apply_))
                 ),
                 Base__
                );

                // specific implementation is not defined for given arguments;
                // re-try with specific implementation for predecessor in tuple of arguments
                CONG_LANG_CORE_FUN_PROPAGATE
                (DispatchDefined, (Exp__, TupleOfExp__, Offset_, Apply_), (core::Undefined),
                 (
                     (Pred_, (typename core::Pred::Call<Offset_>::Type)),
                     (Base__, (DispatchOffset<Exp__, TupleOfExp__, Pred_>))
                 ),
                 Base__
                );

                // call specific implementation (converted to Fun) on given arguments, examine definedness
                CONG_LANG_CORE_FUN_PROPAGATE
                (DispatchImpl, (Exp__, TupleOfExp__, Offset_, Apply_), (),
                 (
                     (Type_, (typename Apply_::template Call<Exp__, TupleOfExp__>::Type)),
                     (Base__, (DispatchDefined<Exp__, TupleOfExp__, Offset_, Apply_, Type_>))
                 ),
                 Base__
                );

                // standard case: try specific implementation for argument at position before the previous
                // note: arguments are counted from 1 (0 is Exp), thus use item N-1 of tuple if Offset is N
                CONG_LANG_CORE_FUN_PROPAGATE
                (DispatchOffset, (Exp__, TupleOfExp__, Offset_), (),
                 (
                     (Pred_, (typename core::Pred::Call<Offset_>::Type)),
                     (Arg_, (typename core::ItemAt::Call<TupleOfExp__, Pred_>::Type)),
                     (ArgPlain_, (typename core::Plain::Call<Arg_>::Type)),
                     (ArgVal_, (typename Eval::Call<ArgPlain_>::Type)),
                     (ValPlain_, (typename core::Plain::Call<ArgVal_>::Type)),
                     (Apply_, (typename ValPlain_::template ApplyMember<Spec_, Offset_>)),
                     (Base__, (DispatchImpl<Exp__, TupleOfExp__, Offset_, Apply_>))
                 ),
                 Base__
                );

                // final case: no further arguments (previously, first was checked),
                // use specific implementation of Exp itself
                CONG_LANG_CORE_FUN_PROPAGATE
                (DispatchOffset, (Exp__, TupleOfExp__), (core::NaturalStatic<0>),
                 (
                     (ArgPlain_, (typename core::Plain::Call<Exp__>::Type)),
                     (Base__, (typename ArgPlain_::template ApplyMember<Spec_, core::NaturalStatic<0>>)),
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
                            Length_>))
                    ),
                    Base__
                );
            };
        };
    };
};
