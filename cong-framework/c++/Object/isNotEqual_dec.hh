#pragma once

#include "../Exp.hh"
#include "../Bind.hh"
#include "../Function.hh"
#include "../Traits.hh"
#include "../Decls.hh"
#include "../Seq/core/Tuple.hh"
#include "../Number/core/NaturalStatic.hh"


#include "Object.hh"

#include "isEqual_dec.hh"
#include "../Boolean/not__dec.hh"
#include "../Boolean/Boolean.hh"

namespace Object {

struct DecIsNotEqual {
    using Params = ::cong::lang::core::Tuple<ConceptObject, ConceptObject>;

    using ReturnConcept = Boolean::ConceptBoolean;

};

struct SpecIsNotEqual;

template <typename... Exp_>
using IsNotEqual = ::cong::lang::Bind< 
    ::cong::lang::intern::Environment,
    ::cong::lang::intern::Exp<::cong::lang::intern::FunctionImpl<DecIsNotEqual, SpecIsNotEqual>>,
    Exp_...
>;

template <typename... Exp_>
constexpr
IsNotEqual<Exp_...> isNotEqual(Exp_&&... args);


}

