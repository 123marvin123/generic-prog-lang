//
// Created by Marvin Haschker on 31.03.25.
//

#ifndef QUOTE_HH
#define QUOTE_HH

#include "Exp.hh"
#include "Base.hh"

#include "Number/NaturalIntervalStatic.hh"
#include "Number/NaturalStatic.hh"
#include "Boolean/BooleanStatic.hh"

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
                template <typename Arg1_>
                struct Call
                {
                    using Type = typename core::Plain::Call<Arg1_>::Type::Exp_&;
                    static constexpr Type call(Arg1_ arg1)
                    {
                        return arg1.exp_;
                    }
                };
            };

            using ApplySpace = core::FunStaticMake<core::NaturalStatic<0>>;
            using ApplyTime = core::FunStaticMake<core::NaturalStatic<1>>;

            struct ApplyValue
            {
                template <typename Arg1_>
                struct Call
                {
                    using Type = typename core::Plain::Call<Arg1_>::Type::Exp_&;
                    static constexpr Type call(Arg1_ arg1)
                    {
                        return arg1.exp_;
                    }
                };
            };
        private:
            typename core::ToNonRValRef::Call<Exp_>::Type exp_;
        public:
            constexpr
            Quote(Exp_ exp)
              : Base_{},
                exp_{exp}
            {}
        };

    };
};

#endif //QUOTE_HH
