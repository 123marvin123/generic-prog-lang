#pragma once

#include "Exp.hh"
#include "Bind.hh"
#include "Function.hh"
#include "Traits.hh"
#include "Decls.hh"
#include "Seq/core/Tuple.hh"


#include "Object/Object.hh"

#include "Boolean/Boolean.hh"
#include "Object/Object.hh"
namespace Boolean {

struct DecCond {
    using Params = ::cong::lang::core::Tuple<::Boolean::ConceptBoolean, ::Object::ConceptObject, ::Object::ConceptObject>;

    using ReturnConcept = ::Object::ConceptObject;

};

struct SpecCond;

template <typename... Exp_>
using Cond = ::cong::lang::Bind< 
    ::cong::lang::intern::Environment,
    ::cong::lang::intern::Exp<::cong::lang::intern::FunctionImpl<DecCond, SpecCond>>,
    Exp_...
>;

template <typename... Exp_>
constexpr
Cond<Exp_...> cond(Exp_&&... args);


}

