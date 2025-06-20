#pragma once

#include "Exp.hh"
#include "Bind.hh"
#include "Function.hh"
#include "Traits.hh"
#include "Decls.hh"
#include "Seq/core/Tuple.hh"


#include "Object/Object.hh"
#include "Object/Object.hh"
namespace Object {

struct DecId {
    using Params = ::cong::lang::core::Tuple<::Object::ConceptObject>;

    using ReturnConcept = ::Object::ConceptObject;

};

struct SpecId;

template <typename... Exp_>
using Id = ::cong::lang::Bind< 
    ::cong::lang::intern::Environment,
    ::cong::lang::intern::Exp<::cong::lang::intern::FunctionImpl<DecId, SpecId>>,
    Exp_...
>;

template <typename... Exp_>
constexpr
Id<Exp_...> id(Exp_&&... args);


}

