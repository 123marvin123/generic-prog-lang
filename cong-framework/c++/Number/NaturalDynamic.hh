#pragma once

#include "../Object/ObjectDynamic.hh"
#include "NaturalStatic.hh"

namespace cong::lang {

    namespace local {
        template <typename Native_ = unsigned long int>
        class NaturalDynamic
            : public ObjectDynamic<Native_>
        {
            using Base_ = ObjectDynamic<Native_>;
        public:
            using typename Base_::Native;
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
    }

    using NaturalDynamic = intern::Exp<local::NaturalDynamic<>>;

}