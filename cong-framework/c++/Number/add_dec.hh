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

struct DecAdd {
    using Params = ::cong::lang::core::Tuple<::Number::ConceptNumber, ::Number::ConceptNumber>;

    using ReturnConcept = ::Number::ConceptNumber;

};

struct SpecAdd;

template <typename... Exp_>
using Add = ::cong::lang::Bind< 
    ::cong::lang::intern::Environment,
    ::cong::lang::intern::Exp<::cong::lang::intern::FunctionImpl<DecAdd, SpecAdd>>,
    Exp_...
>;

template <typename... Exp_>
constexpr
Add<Exp_...> add(Exp_&&... args);


}

