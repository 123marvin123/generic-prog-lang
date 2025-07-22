#pragma once

#include "../Object/ObjectStatic.hh"
#include "../ApplyMember.hh"
#include "../Exp.hh"
#include "NaturalStatic.hh"

#include "core/Integer.hh"
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

#include "Integer.hh"

namespace cong::lang
{
    namespace local {
        template <typename Native_, Native_ native_>
        struct IntegerStatic
            : ObjectStatic<Native_, native_>
        {
            using Base_ = ObjectStatic<Native_, native_>;
            using Satisfies = core::Tuple<Number::ConceptInteger>;

            CONG_LANG_INTERN_APPLYMEMBER_DEFAULT;
        };


#define CONCEPT_ Integer
#define STAGE_ Static
#define DIR_ Number
#include "../ApplyMember_operator.hh"

        template<class Native_, Native_ native_>
        CONG_LANG_INTERN_APPLYMEMBER((IntegerStatic<Native_, native_>),
                                     Ordered, IsGreater, 1, 2,
                                     (decltype(ResultingType::greater(std::declval<Arg1_>(), std::declval<Arg2_>()))),
                                     (return ResultingType::greater(p1, p2)));

        template<class Native_, Native_ native_>
        CONG_LANG_INTERN_APPLYMEMBER((IntegerStatic<Native_, native_>),
                             Ordered, IsGreaterEqual, 1, 2,
                             (decltype(ResultingType::greaterEqual(std::declval<Arg1_>(), std::declval<Arg2_>()))),
                             (return ResultingType::greaterEqual(p1, p2)));

        template<class Native_, Native_ native_>
        CONG_LANG_INTERN_APPLYMEMBER((IntegerStatic<Native_, native_>),
                                     Ordered, IsLess, 1, 2,
                                     (decltype(ResultingType::less(std::declval<Arg1_>(), std::declval<Arg2_>()))),
                                     (return ResultingType::less(p1, p2)));

        template<class Native_, Native_ native_>
        CONG_LANG_INTERN_APPLYMEMBER((IntegerStatic<Native_, native_>),
                             Ordered, IsLessEqual, 1, 2,
                             (decltype(ResultingType::lessEqual(std::declval<Arg1_>(), std::declval<Arg2_>()))),
                             (return ResultingType::lessEqual(p1, p2)));
    }


    template <core::Integer value_>
    using IntegerStatic = intern::Exp<local::IntegerStatic<core::Integer, value_>>;

}
