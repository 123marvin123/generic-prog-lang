#pragma once

#include "../Seq/core/Tuple.hh"
#include "../Decls.hh"

#include "../Ordered/Ordered.hh"
#include "Number.hh"

namespace Number {
struct ConceptCardinal {
    using Bases = ::cong::lang::core::Tuple<Ordered::ConceptOrdered, Number::ConceptNumber>;
    static constexpr auto name = "Cardinal";
    static constexpr auto description = "cardinal number";
};

}

