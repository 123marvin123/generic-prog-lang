#pragma once

#include "../Object/ObjectDynamic.hh"
#include "../ApplyMember.hh"
#include "../Exp.hh"

#include "core/Boolean.hh"
#include "core/BooleanStatic.hh"
#include "../Number/core/NaturalStatic.hh"
#include "BooleanStatic.hh"

namespace cong::lang {
        namespace local
        {
            template <typename Native_>
            class BooleanDynamic
            // @todo use canonical Native type/constants (from core)?
              : public ObjectDynamic<Native_>
            {
                using Base_ = ObjectDynamic<Native_>;
            public:
                using typename Base_::Native;
                using Satisfies = std::tuple<Boolean::ConceptBoolean>;

                // @todo should only by accessible from factory function
                explicit constexpr
                BooleanDynamic(Native native = false)
                  : Base_{native}
                {}
                template <typename Native__, Native__ native__>
                constexpr
                BooleanDynamic(cong::lang::intern::Exp<BooleanStatic<Native__, native__>>)
                  : Base_{native__}
                {}

                CONG_LANG_INTERN_APPLYMEMBER_DEFAULT;
            };
#define CONCEPT_ Boolean
#define STAGE_ Dynamic
#define DIR_ Boolean
#include "../ApplyMember_operator.hh"
        }

    using BooleanDynamic = intern::Exp<local::BooleanDynamic<bool>>;
}