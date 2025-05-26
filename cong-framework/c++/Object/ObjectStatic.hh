#pragma once

#include <type_traits>
#include "../ApplyMember.hh"
#include "../Decls.hh"
#include "../Number/core/NaturalStatic.hh"
#include "../Val.hh"

namespace cong::lang
{
    struct StaticTag {};

    namespace local
    {
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

    template <typename T>
    struct IsStatic
    {
        static constexpr bool value = std::is_base_of<StaticTag, std::remove_cv_t<T>>::value;
        using Type = core::BooleanStatic<value>;
    };

} // namespace cong::lang
