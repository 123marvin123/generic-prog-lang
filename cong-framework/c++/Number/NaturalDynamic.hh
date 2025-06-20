#pragma once

#include "../ApplyMember.hh"
#include "../Exp.hh"

#include "NaturalStatic.hh"
#include "../Object/ObjectDynamic.hh"

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

    }

    using NaturalDynamic = intern::Exp<local::NaturalDynamic<>>;

}