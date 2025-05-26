#pragma once

#include "../Object/ObjectStatic.hh"

namespace cong::lang
{
    namespace local {
        template <typename Native_, Native_ native_>
        struct NaturalStatic
            : public ObjectStatic<Native_, native_>
        {
            using Base_ = ObjectStatic<Native_, native_>;
        public:
            CONG_LANG_INTERN_APPLYMEMBER_DEFAULT;
        };
    }

    template <typename Native_, Native_ value_>
    using NaturalStatic = intern::Exp<local::NaturalStatic<Native_, value_>>;

    template <core::Natural value_>
    using N = NaturalStatic<core::Natural, value_>;

}