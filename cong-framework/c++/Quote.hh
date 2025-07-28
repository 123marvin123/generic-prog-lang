#pragma once

#include "Exp.hh"
#include "Base.hh"

#include "Number/core/NaturalIntervalStatic.hh"
#include "Number/core/NaturalStatic.hh"
#include "Boolean/core/BooleanStatic.hh"

namespace cong::lang
{
    namespace local {

        template <typename Exp_>
          class Quote
            : public intern::Base
        {
            using Base_ = intern::Base;
        public:
            using ReduceSpace = core::FunStaticMake<core::NaturalStatic<0>>;
            using ReduceTime = core::FunStaticMake<core::NaturalStatic<1>>;

            struct ReduceValue
            {
                template <typename Arg1_, typename...>
                struct Call
                {
                    using Type = typename core::Plain::Call<Arg1_>::Type::Type;

                    static constexpr Type call(Arg1_&& arg1)
                    {
                        return std::forward<Type>(arg1.exp_);
                    }
                };
            };

            using ApplySpace = core::FunStaticMake<core::NaturalStatic<0>>;
            using ApplyTime = core::FunStaticMake<core::NaturalStatic<1>>;

            using ApplyValue = ReduceValue;
        private:
            typename core::ToNonRValRef::Call<Exp_>::Type exp_;
        public:
            constexpr
            explicit Quote(Exp_&& exp)
              : Base_{},
                exp_{std::forward<Exp_>(exp)}
            {}

            using Type = Exp_;
        };

    };

    template <typename Exp_>
    using Quote = intern::Exp<local::Quote<Exp_>>;

    template <typename Exp_>
    static constexpr Quote<Exp_> quote(Exp_&& e)
    {
        return {std::forward<Exp_>(e)};
    }

};
