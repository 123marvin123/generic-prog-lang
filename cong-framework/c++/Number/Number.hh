#pragma once

#include "Seq/core/Tuple.hh"
#include "Decls.hh"
#include "Val.hh"

#include "Object/Object.hh"

namespace Number {
struct ConceptNumber : cong::lang::intern::Val, cong::lang::ConceptTag {
    using Bases = ::cong::lang::core::Tuple<Object::ConceptObject>;
    static constexpr cong::lang::core::StringStatic name = "Number";
    static constexpr cong::lang::core::StringStatic description = "";
};

}

