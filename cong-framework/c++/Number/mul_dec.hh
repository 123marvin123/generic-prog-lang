#pragma once

#include "../Exp.hh"
#include "../Bind.hh"
#include "../Function.hh"
#include "../Traits.hh"
#include "../Decls.hh"
#include "../Seq/core/Tuple.hh"
#include "core/NaturalStatic.hh"

#include "../Object/Object.hh"
#include "Number.hh"
namespace Number {

struct DecMul {
    using Params = ::cong::lang::core::Tuple<Number::ConceptNumber, Number::ConceptNumber>;

    using ReturnConcept = Number::ConceptNumber;

};

struct SpecMul;

template <typename... Exp_>
using Mul = ::cong::lang::Bind< 
    ::cong::lang::intern::Environment,
    ::cong::lang::intern::Exp<::cong::lang::intern::FunctionImpl<DecMul, SpecMul>>,
    Exp_...
>;

template <typename... Exp_>
constexpr
Mul<Exp_...> mul(Exp_&&... args);


}

