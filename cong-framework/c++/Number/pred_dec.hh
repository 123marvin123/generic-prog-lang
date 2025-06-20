#pragma once

#include "Exp.hh"
#include "Bind.hh"
#include "Function.hh"
#include "Traits.hh"
#include "Decls.hh"
#include "Seq/core/Tuple.hh"


#include "Object/Object.hh"
#include "Number/Number.hh"
#include "Object/Object.hh"
namespace Number {

struct DecPred {
    using Params = ::cong::lang::core::Tuple<::Object::ConceptObject>;

    using ReturnConcept = ::Object::ConceptObject;

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

