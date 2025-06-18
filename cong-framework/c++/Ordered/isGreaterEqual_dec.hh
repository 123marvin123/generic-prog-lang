#pragma once

#include "../Exp.hh"
#include "../Bind.hh"
#include "../Function.hh"
#include "../Traits.hh"
#include "../Decls.hh"
#include "../Seq/core/Tuple.hh"
#include "../Number/core/NaturalStatic.hh"


#include "../Object/Object.hh"

#include "../Object/isEqual_dec.hh"
#include "../Ordered/isGreater_dec.hh"
#include "../Ordered/Ordered.hh"
#include "../Boolean/or__dec.hh"
#include "../Boolean/Boolean.hh"

namespace Ordered {

struct DecIsGreaterEqual {
    using Params = ::cong::lang::core::Tuple<Ordered::ConceptOrdered, Ordered::ConceptOrdered>;

    using ReturnConcept = Boolean::ConceptBoolean;

};

struct SpecIsGreaterEqual;

template <typename... Exp_>
using IsGreaterEqual = ::cong::lang::Bind< 
    ::cong::lang::intern::Environment,
    ::cong::lang::intern::Exp<::cong::lang::intern::FunctionImpl<DecIsGreaterEqual, SpecIsGreaterEqual>>,
    Exp_...
>;

template <typename... Exp_>
constexpr
IsGreaterEqual<Exp_...> isGreaterEqual(Exp_&&... args);


}

