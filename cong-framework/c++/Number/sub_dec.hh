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

struct DecSub {
    using Params = ::cong::lang::core::Tuple<Number::ConceptNumber, Number::ConceptNumber>;

    using ReturnConcept = Number::ConceptNumber;

};

struct SpecSub;

template <typename... Exp_>
using Sub = ::cong::lang::Bind< 
    ::cong::lang::intern::Environment,
    ::cong::lang::intern::Exp<::cong::lang::intern::FunctionImpl<DecSub, SpecSub>>,
    Exp_...
>;

template <typename... Exp_>
constexpr
Sub<Exp_...> sub(Exp_&&... args);


}

