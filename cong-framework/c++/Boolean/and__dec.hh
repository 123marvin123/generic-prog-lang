#pragma once

#include "Exp.hh"
#include "Bind.hh"
#include "Function.hh"
#include "Traits.hh"
#include "Decls.hh"
#include "Seq/core/Tuple.hh"


#include "Object/Object.hh"
#include "Boolean/Boolean.hh"
namespace Boolean {

struct DecAnd_ {
    using Params = ::cong::lang::core::Tuple<::Boolean::ConceptBoolean, ::Boolean::ConceptBoolean>;

    using ReturnConcept = ::Boolean::ConceptBoolean;

};

struct SpecAnd_;

template <typename... Exp_>
using And_ = ::cong::lang::Bind< 
    ::cong::lang::intern::Environment,
    ::cong::lang::intern::Exp<::cong::lang::intern::FunctionImpl<DecAnd_, SpecAnd_>>,
    Exp_...
>;

template <typename... Exp_>
constexpr
And_<Exp_...> and_(Exp_&&... args);


}

