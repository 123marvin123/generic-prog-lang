#pragma once

#include "Exp.hh"
#include "Bind.hh"
#include "Function.hh"
#include "Traits.hh"
#include "Decls.hh"
#include "Seq/core/Tuple.hh"


#include "Object/Object.hh"
#include "Number/Number.hh"
namespace Number {

struct DecMod {
    using Params = ::cong::lang::core::Tuple<::Number::ConceptNumber, ::Number::ConceptNumber>;

    using ReturnConcept = ::Number::ConceptNumber;

};

struct SpecMod;

template <typename... Exp_>
using Mod = ::cong::lang::Bind< 
    ::cong::lang::intern::Environment,
    ::cong::lang::intern::Exp<::cong::lang::intern::FunctionImpl<DecMod, SpecMod>>,
    Exp_...
>;

template <typename... Exp_>
constexpr
Mod<Exp_...> mod(Exp_&&... args);


}

