#pragma once

#include "Exp.hh"
#include "Bind.hh"
#include "Function.hh"
#include "Traits.hh"
#include "Decls.hh"
#include "Seq/core/Tuple.hh"
#include "Number/core/NaturalStatic.hh"


#include "Object/Object.hh"

#include "Boolean/Boolean.hh"
namespace Boolean {

struct DecOr_ {
    using Params = ::cong::lang::core::Tuple<Boolean::ConceptBoolean, Boolean::ConceptBoolean>;

    using ReturnConcept = Boolean::ConceptBoolean;

};

struct SpecOr_;

template <typename... Exp_>
using Or_ = ::cong::lang::Bind< 
    ::cong::lang::intern::Environment,
    ::cong::lang::intern::Exp<::cong::lang::intern::FunctionImpl<DecOr_, SpecOr_>>,
    Exp_...
>;

template <typename... Exp_>
constexpr
Or_<Exp_...> or_(Exp_&&... args);


}

