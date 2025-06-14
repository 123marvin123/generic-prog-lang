#pragma once

#include "../Object/ObjectStatic.hh"

namespace cong::lang
{
    namespace local {
        template <typename Native_, Native_ native_>
        struct NaturalStatic
            : ObjectStatic<Native_, native_>
        {
            using Base_ = ObjectStatic<Native_, native_>;

            CONG_LANG_INTERN_APPLYMEMBER_DEFAULT;
        };
    }

    template <core::Natural value_>
    using NaturalStatic = intern::Exp<local::NaturalStatic<core::Natural, value_>>;

    template <core::Natural value_>
    using N = NaturalStatic<value_>;

}