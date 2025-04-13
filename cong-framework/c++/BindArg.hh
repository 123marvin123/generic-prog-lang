#pragma once

#include "Exp.hh"
#include "Base.hh"

#include "Decls.hh"
#include "Boolean/core/BooleanStatic.hh"

#include "Traits.hh"

#include <utility>

namespace cong::lang
{
    namespace local
    {
        template <typename Arg_>
        class BindArg : public intern::Base

        {
            using Base_ = intern::Base;

        public:
            struct IsStateful
            {
                template <typename BindArgExp_>
                struct Call
                    : ::cong::lang::intern::IsStateful::Call<Arg_>
                {
                };
            };

            using Arity = core::FunStaticMake<core::NaturalIntervalStatic<1>>;

            using ReduceValue = core::FunId;

            struct ApplyValue
            {
                template <typename BindArgExp_, typename Exp_>
                struct Call
                {
                private:
                    using ApplyValue_ = intern::ApplyValue::Call<Exp_, Arg_>;

                public:
                    using Type = typename ApplyValue_::Type;

                    static constexpr
                    Type call(BindArgExp_ bindArgExp, Exp_ exp)
                    {
                        return ApplyValue_::call(exp,
                                                 bindArgExp.arg_);
                    }
                };
            };

        private:
            typename core::ToNonRValRef::Call<Arg_>::Type arg_;

        public:
            constexpr
            BindArg(Arg_ arg)
                : arg_{arg}
            {
            }
        };
    };

    template <typename Arg_>
    using BindArg = intern::Exp<local::BindArg<Arg_>>;

    template <typename Arg_>
    constexpr
    BindArg<Arg_>
    bindArg(Arg_&& arg)
    {
        return {std::forward<Arg_>(arg)};
    }
};
