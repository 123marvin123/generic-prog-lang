#pragma once

#include "Exp.hh"
#include "Bind.hh"
#include "Function.hh"
#include "Traits.hh"
#include "Decls.hh"
#include "Seq/core/Tuple.hh"


#include "Object/Object.hh"
#include "Ordered/Ordered.hh"
#include "Boolean/Boolean.hh"
namespace Ordered {

struct DecIsLess {
    using Params = ::cong::lang::core::Tuple<::Ordered::ConceptOrdered, ::Ordered::ConceptOrdered>;

    using ReturnConcept = ::Boolean::ConceptBoolean;

};

struct SpecIsLess;

template <typename... Exp_>
using IsLess = ::cong::lang::Bind< 
    ::cong::lang::intern::Environment,
    ::cong::lang::intern::Exp<::cong::lang::intern::FunctionImpl<DecIsLess, SpecIsLess>>,
    Exp_...
>;

template <typename... Exp_>
constexpr
IsLess<Exp_...> isLess(Exp_&&... args);


}

