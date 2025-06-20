#pragma once

#include "Seq/core/Tuple.hh"
#include "Decls.hh"
#include "Val.hh"

#include "Ordered/Ordered.hh"
#include "Number/Number.hh"

namespace Number {
struct ConceptNatural : cong::lang::intern::Val, cong::lang::ConceptTag {
    using Bases = ::cong::lang::core::Tuple<Ordered::ConceptOrdered, Number::ConceptNumber>;
    static constexpr cong::lang::core::StringStatic name = "Natural";
    static constexpr cong::lang::core::StringStatic description = "natural number, possibly zero";
};

}

