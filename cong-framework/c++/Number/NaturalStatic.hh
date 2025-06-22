#pragma once

#include "../Object/ObjectStatic.hh"
#include "../ApplyMember.hh"
#include "../Exp.hh"

#include "add_dec.hh"
#include "sub_dec.hh"
#include "mul_dec.hh"
#include "div_dec.hh"
#include "mod_dec.hh"
#include "succ_dec.hh"
#include "pred_dec.hh"

#include "../Ordered/isGreater_dec.hh"
#include "../Ordered/isGreaterEqual_dec.hh"
#include "../Ordered/isLess_dec.hh"
#include "../Ordered/isLessEqual_dec.hh"

namespace cong::lang
{
    namespace local {
        template <typename Native_, Native_ native_>
        struct NaturalStatic
            : ObjectStatic<Native_, native_>
        {
            using Base_ = ObjectStatic<Native_, native_>;
            using Satisfies = core::Tuple<Number::ConceptNatural>;

            CONG_LANG_INTERN_APPLYMEMBER_DEFAULT;
        };


#define CONCEPT_ Natural
#define STAGE_ Static
#define DIR_ Number
#include "../ApplyMember_operator.hh"

        struct ResultingType
        {
#define MAKE_FN(name_, op_) \
            template<class Arg1_, class Arg2_> \
            static constexpr auto name_(Arg1_ p1, Arg2_ p2) \
            { \
                if constexpr(std::is_same_v<typename core::IsStatic<Arg2_>::Type, core::True>) \
                { \
                    return lang::BooleanStatic<(Arg1_::native() op_ Arg2_::native())>{}; \
                } \
                else \
                { \
                    return lang::BooleanDynamic{p1.native() op_ p2.native()}; \
                } \
            } \

            MAKE_FN(less, <)
            MAKE_FN(lessEqual, <=)
            MAKE_FN(greater, >)
            MAKE_FN(greaterEqual, >=)
#undef MAKE_FN
        };

        template<class Native_, Native_ native_>
        CONG_LANG_INTERN_APPLYMEMBER((NaturalStatic<Native_, native_>),
                                     Ordered, IsGreater, 1, 2,
                                     (decltype(ResultingType::greater(std::declval<Arg1_>(), std::declval<Arg2_>()))),
                                     (return ResultingType::greater(p1, p2)));

        template<class Native_, Native_ native_>
        CONG_LANG_INTERN_APPLYMEMBER((NaturalStatic<Native_, native_>),
                             Ordered, IsGreaterEqual, 1, 2,
                             (decltype(ResultingType::greaterEqual(std::declval<Arg1_>(), std::declval<Arg2_>()))),
                             (return ResultingType::greaterEqual(p1, p2)));

        template<class Native_, Native_ native_>
        CONG_LANG_INTERN_APPLYMEMBER((NaturalStatic<Native_, native_>),
                                     Ordered, IsLess, 1, 2,
                                     (decltype(ResultingType::less(std::declval<Arg1_>(), std::declval<Arg2_>()))),
                                     (return ResultingType::less(p1, p2)));

        template<class Native_, Native_ native_>
        CONG_LANG_INTERN_APPLYMEMBER((NaturalStatic<Native_, native_>),
                             Ordered, IsLessEqual, 1, 2,
                             (decltype(ResultingType::lessEqual(std::declval<Arg1_>(), std::declval<Arg2_>()))),
                             (return ResultingType::lessEqual(p1, p2)));
    }


    template <core::Natural value_>
    using NaturalStatic = intern::Exp<local::NaturalStatic<core::Natural, value_>>;

    template <core::Natural value_>
    using N = NaturalStatic<value_>;

}
