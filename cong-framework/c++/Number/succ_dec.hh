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

struct DecSucc {
    using Params = ::cong::lang::core::Tuple<Number::ConceptNatural>;

    using ReturnConcept = Number::ConceptInteger;

};

struct SpecSucc;

template <typename... Exp_>
using Succ = ::cong::lang::Bind< 
    ::cong::lang::intern::Environment,
    ::cong::lang::intern::Exp<::cong::lang::intern::FunctionImpl<DecSucc, SpecSucc>>,
    Exp_...
>;

template <typename... Exp_>
constexpr
Succ<Exp_...> succ(Exp_&&... args);


}

