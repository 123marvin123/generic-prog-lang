#pragma once

#include "Seq/core/Tuple.hh"
#include "Decls.hh"
#include "Val.hh"

#include "Ordered/Ordered.hh"
#include "Number/Natural.hh"

namespace Number {
struct ConceptInteger : cong::lang::intern::Val, cong::lang::ConceptTag {
    using Bases = ::cong::lang::core::Tuple<Ordered::ConceptOrdered, Number::ConceptNatural>;
    static constexpr cong::lang::core::StringStatic name = "Integer";
    static constexpr cong::lang::core::StringStatic description = "integer number";
};

}

