#pragma once

#include "../Exp.hh"
#include "../Function.hh"
#include "../Decls.hh"
#include "../Seq/core/Tuple.hh"

#include "Object.hh"

#include "../Boolean/Boolean.hh"

namespace Object {

struct DecIsEqual {
    using Params = ::cong::lang::core::Tuple<ConceptObject, ConceptObject>;

    using ReturnConcept = Boolean::ConceptBoolean;

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

