#pragma once

#include "Exp.hh"
#include "Base.hh"

#include "Seq/Tuple.hh"
#include "Number/NaturalIntervalStatic.hh"
#include "Boolean/Boolean.hh"

namespace cong::lang
{
    namespace local {
        template <core::Natural N_>
          class Proj
            : public intern::Base
        {
            using Base_ = intern::Base;
        public:
            using ReduceSpace = core::FunStaticMake<core::NaturalStatic<0>>;
            using ReduceTime = core::FunStaticMake<core::NaturalStatic<1>>;
            using ReduceValue = core::FunId;

            using Arity = core::FunStaticMake<core::NaturalIntervalStatic<N_>>;
            // @todo invalid if length of tuple is less than N_
            using ApplySpace = core::FunStaticMake<core::NaturalStatic<0>>;
            using ApplyTime = core::FunStaticMake<core::NaturalStatic<1>>;
            struct ApplyValue
            {
                template <typename Exp_, typename TupleOfExp_>
                struct Call
                {
                private:
                    static_assert(N_ > 0, "Proj requires N_ >= 1 to avoid invalid offset indexing.");
                    using Offset_ = core::NaturalStatic<N_ - 1>;
                    using Call_ = core::ItemAt::Call<TupleOfExp_, Offset_>;
                public:
                    using Type = typename Call_::Type;
                    /**
                     * @brief Retrieves an element from a tuple of expressions.
                     *
                     * This function extracts the element from the provided tuple at the position computed as N_ - 1.
                     * The parameter `exp` is included to satisfy interface requirements but is not used in the extraction.
                     *
                     * @param exp An expression instance (unused) required for interface compatibility.
                     * @param tupleOfExp A tuple containing expressions from which the element is projected.
                     * @return The element from `tupleOfExp` located at index (N_ - 1).
                     */
                    static constexpr
                    Type
                    call(Exp_ exp,
                         TupleOfExp_ tupleOfExp)
                    {
                        return Call_::call(tupleOfExp, Offset_{});
                    }
                };
            };
        };
    };

    template <core::Natural N_>
    using Proj = intern::Exp<local::Proj<N_>>;

};
