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

struct DecIsGreater {
    using Params = ::cong::lang::core::Tuple<::Ordered::ConceptOrdered, ::Ordered::ConceptOrdered>;

    using ReturnConcept = ::Boolean::ConceptBoolean;

};

struct SpecIsGreater;

template <typename... Exp_>
using IsGreater = ::cong::lang::Bind< 
    ::cong::lang::intern::Environment,
    ::cong::lang::intern::Exp<::cong::lang::intern::FunctionImpl<DecIsGreater, SpecIsGreater>>,
    Exp_...
>;

template <typename... Exp_>
constexpr
IsGreater<Exp_...> isGreater(Exp_&&... args);


}

