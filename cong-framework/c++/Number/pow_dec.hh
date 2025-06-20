#pragma once

#include "Exp.hh"
#include "Bind.hh"
#include "Function.hh"
#include "Traits.hh"
#include "Decls.hh"
#include "Seq/core/Tuple.hh"


#include "Object/Object.hh"
#include "Number/Integer.hh"#include "Number/Number.hh"
namespace Number {

struct DecPow {
    using Params = ::cong::lang::core::Tuple<::Number::ConceptNumber, ::Number::ConceptInteger>;

    using ReturnConcept = ::Number::ConceptNumber;

};

struct SpecPow;

template <typename... Exp_>
using Pow = ::cong::lang::Bind< 
    ::cong::lang::intern::Environment,
    ::cong::lang::intern::Exp<::cong::lang::intern::FunctionImpl<DecPow, SpecPow>>,
    Exp_...
>;

template <typename... Exp_>
constexpr
Pow<Exp_...> pow(Exp_&&... args);


}

