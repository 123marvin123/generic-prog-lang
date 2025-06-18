#pragma once

#include "../Seq/core/Tuple.hh"
#include "../Decls.hh"

#include "../Ordered/Ordered.hh"
#include "Natural.hh"

namespace Number {
struct ConceptInteger {
    using Bases = ::cong::lang::core::Tuple<Ordered::ConceptOrdered, Number::ConceptNatural>;
    static constexpr auto name = "Integer";
    static constexpr auto description = "integer number";
};

}

