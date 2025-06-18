#pragma once

#include "../Seq/core/Tuple.hh"
#include "../Decls.hh"

#include "../Ordered/Ordered.hh"
#include "Number.hh"

namespace Number {
struct ConceptComplex {
    using Bases = ::cong::lang::core::Tuple<Ordered::ConceptOrdered, Number::ConceptNumber>;
    static constexpr auto name = "Complex";
    static constexpr auto description = "complex number";
};

}

