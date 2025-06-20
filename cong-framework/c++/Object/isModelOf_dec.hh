#pragma once

#include "Exp.hh"
#include "Bind.hh"
#include "Function.hh"
#include "Traits.hh"
#include "Decls.hh"
#include "Seq/core/Tuple.hh"


#include "Object/Object.hh"
#include "Object/Object.hh"
#include "Boolean/Boolean.hh"

namespace Object {

struct DecIsModelOf {
    using Params = ::cong::lang::core::Tuple<::Object::ConceptObject, ::Object::ConceptObject>;

    using ReturnConcept = ::Boolean::ConceptBoolean;

};

struct SpecIsModelOf;

template <typename... Exp_>
using IsModelOf = ::cong::lang::Bind< 
    ::cong::lang::intern::Environment,
    ::cong::lang::intern::Exp<::cong::lang::intern::FunctionImpl<DecIsModelOf, SpecIsModelOf>>,
    Exp_...
>;

template <typename... Exp_>
constexpr
IsModelOf<Exp_...> isModelOf(Exp_&&... args);


}

