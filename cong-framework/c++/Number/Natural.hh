#pragma once

#include "../Seq/core/Tuple.hh"
#include "../Decls.hh"

#include "../Ordered/Ordered.hh"
#include "Number.hh"

namespace Number {
struct ConceptNatural {
    using Bases = ::cong::lang::core::Tuple<Ordered::ConceptOrdered, Number::ConceptNumber>;
    static constexpr auto name = "Natural";
    static constexpr auto description = "natural number, possibly zero";
};

}

