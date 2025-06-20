#pragma once

#include <type_traits>
#include "../ApplyMember.hh"
#include "../Decls.hh"
#include "../Number/core/NaturalStatic.hh"
#include "../Val.hh"

#include "Object.hh"
#include "isEqual_dec.hh"
#include "isNotEqual_dec.hh"
#include "id_dec.hh"
#include "../Ordered/isGreater_dec.hh"

namespace cong::lang
{
    namespace local
    {
        template <typename Native_, Native_ value_>
        class BooleanStatic;

        template <typename Native_, Native_ native_>
        class ObjectStatic : public intern::Val, public StaticTag
        {
            using Base_ = intern::Val;

        public:
            using Native = Native_;
            static constexpr Native native() { return native_; }

            using ApplySpace = core::FunStaticMake<core::NaturalStatic<1>>;
            CONG_LANG_INTERN_APPLYMEMBER_DEFAULT;
        };
    }; // namespace local

    template <typename Native_, Native_ native_>
    using ObjectStatic = intern::Exp<local::ObjectStatic<Native_, native_>>;

    template <core::Boolean value_>
    using B = intern::Exp<local::BooleanStatic<core::Boolean, value_>>;

    namespace local
    {

        template <typename Native_, Native_ native_>
        CONG_LANG_INTERN_APPLYMEMBER((ObjectStatic<Native_, native_>),
                             Object, Id, 1, 1,
                             (intern::Exp<ObjectStatic>),
                             (return p1));

        template <typename Native_, Native_ native_>
        CONG_LANG_INTERN_APPLYMEMBER((ObjectStatic<Native_, native_>),
                                     Object, IsEqual, 1, 2,
                                     (B<core::IsSame::Call<Arg1_, Arg2_>::Type::native()>),
                                     (return {}));

        template <typename Native_, Native_ native_>
        CONG_LANG_INTERN_APPLYMEMBER((ObjectStatic<Native_, native_>),
                                     Object, IsNotEqual, 1, 2,
                                     (B<!core::IsSame::Call<Arg1_, Arg2_>::Type::native()>),
                                     (return {}));

    }
} // namespace cong::lang

