#pragma once

#include <utility>
#include "../Val.hh"
#include "../Traits.hh"
#include "../Number/core/NaturalStatic.hh"
#include "../ApplyMember.hh"

namespace cong::lang {

      struct DynamicTag {};
      namespace local {

      template <typename Type_>
        class ObjectDynamic
          : public intern::Val, public DynamicTag
      {
        using Base_ = intern::Val;
      public:
        using Native = typename core::ToNonRValRef::Call<Type_>::Type;
      private:
        Native native_;
      public:
        // @todo adjust initialization across different Exp variants
        template <typename Init_>
        explicit constexpr
        ObjectDynamic(Init_&& init)
          : native_{std::forward<Init_>(init)}
        {}

        constexpr
        //typename core::Traits<typename core::Traits<Native>::ToConst>::ToReference
        const Native&
        native() const
        {
          return native_;
        }

        Native&
        native()
        {
          return native_;
        }

        using ApplySpace = core::FunStaticMake<core::NaturalStatic<1>>;

        CONG_LANG_INTERN_APPLYMEMBER_DEFAULT;
      };
  }

    template <typename Native_>
    using ObjectDynamic = intern::Exp<local::ObjectDynamic<Native_>>;

};