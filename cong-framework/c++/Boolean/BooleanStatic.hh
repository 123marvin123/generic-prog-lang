#pragma once

#include "../Object/ObjectStatic.hh"

#include "../Val.hh"
#include "../ApplyMember.hh"
#include "../Exp.hh"

#include "core/Boolean.hh"

namespace cong::lang {
	namespace local {
		template <typename Native_, Native_ native_>
  		class BooleanStatic
    		: public cong::lang::ObjectStatic<Native_, native_>
  		{
    		using Base_ = cong::lang::ObjectStatic<Native_, native_>;
  		public:
    		CONG_LANG_INTERN_APPLYMEMBER_DEFAULT;
  		};
	};

	template <core::Boolean value_>
	using BooleanStatic = intern::Exp<local::BooleanStatic<core::Boolean, value_>>;

	using True = BooleanStatic<true>;
	using False = BooleanStatic<false>;

    template<core::Boolean native_>
    struct core::Truthy::Call<BooleanStatic<native_>>
    {
        using Type = bool;
        static constexpr Type call(...)
        {
            return native_;
        }
    };

    template<core::Boolean native_>
    struct core::Falsy::Call<BooleanStatic<native_>>
    {
        using Type = bool;
        static constexpr Type call(...)
        {
            return native_ == false;
        }
    };
};
