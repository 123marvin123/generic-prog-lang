#pragma once

#include "../Seq/core/Tuple.hh"
#include "../Decls.hh"

#include "../Ordered/Ordered.hh"
#include "Number.hh"

namespace Number {
struct ConceptRational {
    using Bases = ::cong::lang::core::Tuple<Ordered::ConceptOrdered, Number::ConceptNumber>;
    static constexpr auto name = "Rational";
    static constexpr auto description = "rational number";
};

}

