#pragma once

#include "Seq/core/Tuple.hh"
#include "Decls.hh"
#include "Val.hh"


namespace Object {
struct ConceptObject : cong::lang::intern::Val, cong::lang::ConceptTag {
    using Bases = ::cong::lang::core::Tuple<>;
    static constexpr cong::lang::core::StringStatic name = "Object";
    static constexpr cong::lang::core::StringStatic description = "";
};

}

