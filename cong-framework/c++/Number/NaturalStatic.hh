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

#define CONCEPT_ Natural
#define STAGE_ Static
#define DIR_ Number
#include "../ApplyMember_operator.hh"

    }

    template <core::Natural value_>
    using NaturalStatic = intern::Exp<local::NaturalStatic<core::Natural, value_>>;

    template <core::Natural value_>
    using N = NaturalStatic<value_>;

}
