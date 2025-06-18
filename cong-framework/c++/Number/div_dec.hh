#pragma once

#include "../Exp.hh"
#include "../Bind.hh"
#include "../Function.hh"
#include "../Traits.hh"
#include "../Decls.hh"
#include "../Seq/core/Tuple.hh"
#include "../Number/core/NaturalStatic.hh"


#include "../Object/Object.hh"
#include "Number.hh"

namespace Number {

struct DecDiv {
    using Params = ::cong::lang::core::Tuple<Number::ConceptNumber, Number::ConceptNumber>;

    using ReturnConcept = Number::ConceptNumber;

};

struct SpecDiv;

template <typename... Exp_>
using Div = ::cong::lang::Bind< 
    ::cong::lang::intern::Environment,
    ::cong::lang::intern::Exp<::cong::lang::intern::FunctionImpl<DecDiv, SpecDiv>>,
    Exp_...
>;

template <typename... Exp_>
constexpr
Div<Exp_...> div(Exp_&&... args);


}

