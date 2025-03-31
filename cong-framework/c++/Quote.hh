#pragma once

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
                    /**
                     * @brief Extracts the expression from the provided argument.
                     *
                     * Retrieves and returns the value of the `exp_` member from the given object.
                     *
                     * @param arg1 Object containing the expression as `exp_`.
                     * @return Type The extracted expression.
                     */
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
                    /**
                     * @brief Extracts and returns the expression contained in the argument.
                     *
                     * Retrieves the stored expression by accessing the `exp_` member of the provided object.
                     *
                     * @tparam Arg1_ The type of the object holding the expression.
                     * @param arg1 The object from which the expression is extracted.
                     * @return Type The expression extracted from the object.
                     */
                    static constexpr Type call(Arg1_ arg1)
                    {
                        return arg1.exp_;
                    }
                };
            };
        private:
            typename core::ToNonRValRef::Call<Exp_>::Type exp_;
        public:
            /**
             * @brief Constructs a Quote instance with the specified expression.
             *
             * This constexpr constructor initializes the base class and stores the provided expression,
             * converting it to a non-rvalue reference for internal use.
             *
             * @param exp The expression to be encapsulated by this Quote.
             */
            constexpr
            Quote(Exp_ exp)
              : Base_{},
                exp_{exp}
            {}
        };

    };
};
