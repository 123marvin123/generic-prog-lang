#pragma once

#include "../Exp.hh"
#include "../Bind.hh"
#include "../Function.hh"
#include "../Traits.hh"
#include "../Decls.hh"
#include "../Seq/core/Tuple.hh"
#include "core/NaturalStatic.hh"


#include "../Object/Object.hh"

#include "Natural.hh"
#include "Integer.hh"
namespace Number {

struct DecPred {
    using Params = ::cong::lang::core::Tuple<Number::ConceptNatural>;

    using ReturnConcept = Number::ConceptInteger;

};

struct SpecPred;

template <typename... Exp_>
using Pred = ::cong::lang::Bind< 
    ::cong::lang::intern::Environment,
    ::cong::lang::intern::Exp<::cong::lang::intern::FunctionImpl<DecPred, SpecPred>>,
    Exp_...
>;

template <typename... Exp_>
constexpr
Pred<Exp_...> pred(Exp_&&... args);


}

