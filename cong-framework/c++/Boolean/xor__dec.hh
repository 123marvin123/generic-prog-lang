#pragma once

#include "Exp.hh"
#include "Bind.hh"
#include "Function.hh"
#include "Traits.hh"
#include "Decls.hh"
#include "Seq/core/Tuple.hh"
#include "Number/core/NaturalStatic.hh"


#include "Object/Object.hh"

#include "Boolean/or__dec.hh"
#include "Boolean/not__dec.hh"
#include "Object/isNotEqual_dec.hh"
#include "Boolean/and__dec.hh"
#include "Boolean/Boolean.hh"
namespace Boolean {

struct DecXor_ {
    using Params = ::cong::lang::core::Tuple<Boolean::ConceptBoolean, Boolean::ConceptBoolean>;

    using ReturnConcept = Boolean::ConceptBoolean;

};

struct SpecXor_;

template <typename... Exp_>
using Xor_ = ::cong::lang::Bind< 
    ::cong::lang::intern::Environment,
    ::cong::lang::intern::Exp<::cong::lang::intern::FunctionImpl<DecXor_, SpecXor_>>,
    Exp_...
>;

template <typename... Exp_>
constexpr
Xor_<Exp_...> xor_(Exp_&&... args);


}

