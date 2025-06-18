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

struct DecNot_ {
    using Params = ::cong::lang::core::Tuple<Boolean::ConceptBoolean>;

    using ReturnConcept = Boolean::ConceptBoolean;

};

struct SpecNot_;

template <typename... Exp_>
using Not_ = ::cong::lang::Bind< 
    ::cong::lang::intern::Environment,
    ::cong::lang::intern::Exp<::cong::lang::intern::FunctionImpl<DecNot_, SpecNot_>>,
    Exp_...
>;

template <typename... Exp_>
constexpr
Not_<Exp_...> not_(Exp_&&... args);


}

