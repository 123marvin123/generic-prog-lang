#pragma once

#include "BindArg.hh"
#include "Base.hh"

#include "Seq/Tuple.hh"
#include "Number/NaturalIntervalStatic.hh"
#include "Boolean/BooleanStatic.hh"

#include "Traits.hh"
#include "Type.hh"

#include <utility> // std::forward

namespace cong::lang
{
    namespace intern
    {
        class Environment;
        template <class Impl_>
        class Exp;
    }

    namespace local
    {
        template <typename Env_,
                  typename Exp_,
                  typename TupleOfExp_>
        class Bind
            : public intern::Base
        {
        public:
            struct IsStateful
            {
                template <typename ExpBind_ = Bind>
                struct Call
                {
                    using Type = typename core::Or_::Call
                    <
                        typename ExpBind_::IsStateful::template Call<Exp_>::Type,
                        typename core::Fold1::Call
                        <
                            core::Or_,
                            typename core::Transform::Call
                            <
                                typename ExpBind_::IsStateful,
                                typename core::Transform::Call<core::Plain,
                                                               TupleOfExp_>::Type
                            >::Type
                        >::Type
                    >::Type;
                };
            };

            struct Arity
            {
                template <typename ExpBind_>
                struct Call
                {
                    using Type = typename core::Fold1::Call
                    <
                        core::Intersect,
                        typename core::Transform::Call<intern::Arity,
                                                       TupleOfExp_>::Type
                    >::Type;
                };
            };

            struct ApplyValue
            {
                template <typename Exp__, typename TupleOfExp__>
                struct Call
                {
                private:
                    using BindArg_ = lang::BindArg<TupleOfExp__>;
                    using Transform_ = intern::TransformExp::Call<BindArg_, TupleOfExp_>;
                    using ApplyValue_ = intern::ApplyValue::Call<Exp_, typename Transform_::Type>;

                public:
                    using Type = typename ApplyValue_::Type;

                    static constexpr
                    Type
                    call(Exp__ exp,
                         TupleOfExp__ tupleOfExp)
                    {
                        return ApplyValue_::call(exp,
                                                 Transform_::call(BindArg_{tupleOfExp},
                                                                  exp.tupleOfExp_));
                    }
                };
            };

            struct ReduceValue
            {
                template <typename Exp__>
                struct Call
                {
                private:
                    using ApplyValue_ = intern::ApplyValue::Call<Exp_, TupleOfExp_>;

                public:
                    using Type = typename ApplyValue_::Type;

                    static constexpr
                    Type
                    call(Exp__ exp)
                    {
                        return ApplyValue_::call(exp.exp_,
                                                 exp.tupleOfExp_);
                    }
                };
            };

        private:
            typename core::ToNonRValRef::Call<Env_>::Type env_;
            typename core::ToNonRValRef::Call<Exp_>::Type exp_;
            typename core::ToTupleNonRValRef::Call<TupleOfExp_>::Type tupleOfExp_;

        public:
            constexpr
            Bind()
                : env_{},
                  exp_{},
                  tupleOfExp_{}
            {
            }

            constexpr
            Bind(Env_ env,
                 Exp_ exp,
                 TupleOfExp_ tupleOfExp)
                : env_{env},
                  exp_{exp},
                  tupleOfExp_{tupleOfExp}
            {
            }
        };
    };


    template <typename Env_,
              typename Exp0_,
              typename... ExpS_>
    constexpr
    Bind<Env_,
         Exp0_,
         ExpS_...>
    bind(Env_&& env,
         Exp0_&& exp0,
         ExpS_&&... expS)
    {
        return
        {
            std::forward<Env_>(env),
            std::forward<Exp0_>(exp0),
            core::tuple(std::forward<ExpS_>(expS)...)
        };
    }
};
