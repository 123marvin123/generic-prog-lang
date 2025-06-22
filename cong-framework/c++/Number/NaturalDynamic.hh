#pragma once

#include "../ApplyMember.hh"
#include "../Exp.hh"

#include "NaturalStatic.hh"
#include "../Object/ObjectDynamic.hh"
#include "../Boolean/BooleanDynamic.hh"

namespace cong::lang {

    namespace local {
        template <typename Native_ = unsigned long int>
        class NaturalDynamic
            : public ObjectDynamic<Native_>
        {
            using Base_ = ObjectDynamic<Native_>;
        public:
            using typename Base_::Native;
            using Satisfies = core::Tuple<Number::ConceptNatural>;
        public:

            constexpr
            NaturalDynamic(Native native = 0)
            : Base_{native}
            {}
            template <typename Native__, Native__ native__>
            constexpr
            NaturalDynamic(cong::lang::intern::Exp<NaturalStatic<Native__, native__>>)
            : Base_{native__}
            {}

            CONG_LANG_INTERN_APPLYMEMBER_DEFAULT;
        };

#define CONCEPT_ Natural
#define STAGE_ Dynamic
#define DIR_ Number
#include "../ApplyMember_operator.hh"

        template<class Native_>
        CONG_LANG_INTERN_APPLYMEMBER((NaturalDynamic<Native_>),
                                      Ordered, IsGreater, 1, 2,
                                      (::cong::lang::BooleanDynamic),
                                      (return {p1.native() > p2.native()}));


        template<class Native_>
        CONG_LANG_INTERN_APPLYMEMBER((NaturalDynamic<Native_>),
                                      Ordered, IsGreaterEqual, 1, 2,
                                      (cong::lang::BooleanDynamic),
                                      (return {p1.native() >= p2.native()}));

       template<class Native_>
       CONG_LANG_INTERN_APPLYMEMBER((NaturalDynamic<Native_>),
                                     Ordered, IsLess, 1, 2,
                                     (cong::lang::BooleanDynamic),
                                     (return {p1.native() < p2.native()}));

        template<class Native_>
       CONG_LANG_INTERN_APPLYMEMBER((NaturalDynamic<Native_>),
                                     Ordered, IsLessEqual, 1, 2,
                                     (cong::lang::BooleanDynamic),
                                     (return {p1.native() <= p2.native()}));

    }

    using NaturalDynamic = intern::Exp<local::NaturalDynamic<>>;

}