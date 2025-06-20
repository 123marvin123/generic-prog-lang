#pragma once

#include "../Object/ObjectStatic.hh"
#include "../ApplyMember.hh"
#include "../Exp.hh"

#include "core/Boolean.hh"
#include "core/BooleanStatic.hh"
#include "../Number/core/NaturalStatic.hh"

#include "not__dec.hh"
#include "or__dec.hh"
#include "and__dec.hh"
#include "xor__dec.hh"

namespace cong::lang {
	namespace local {
		template <typename Native_, Native_ native_>
  		class BooleanStatic
    		: public lang::ObjectStatic<Native_, native_>
  		{
    		using Base_ = lang::ObjectStatic<Native_, native_>;
  		public:
			using Satisfies = std::tuple<Boolean::ConceptBoolean>;
    		CONG_LANG_INTERN_APPLYMEMBER_DEFAULT;
  		};

#define CONCEPT_ Boolean
#define STAGE_ Static
#define DIR_ Boolean
#include "../ApplyMember_operator.hh"
	}

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
