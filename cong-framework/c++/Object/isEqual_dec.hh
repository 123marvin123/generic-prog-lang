#pragma once

#include "Exp.hh"
#include "Bind.hh"
#include "Function.hh"
#include "Traits.hh"
#include "Decls.hh"
#include "Seq/core/Tuple.hh"


#include "Object/Object.hh"
#include "Boolean/Boolean.hh"

namespace Object {

struct DecIsEqual {
    using Params = ::cong::lang::core::Tuple<::Object::ConceptObject, ::Object::ConceptObject>;

    using ReturnConcept = ::Boolean::ConceptBoolean;

};

struct SpecIsEqual;

template <typename... Exp_>
using IsEqual = ::cong::lang::Bind< 
    ::cong::lang::intern::Environment,
    ::cong::lang::intern::Exp<::cong::lang::intern::FunctionImpl<DecIsEqual, SpecIsEqual>>,
    Exp_...
>;

template <typename... Exp_>
constexpr
IsEqual<Exp_...> isEqual(Exp_&&... args);


}

