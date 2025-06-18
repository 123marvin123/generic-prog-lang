#pragma once

#include "../Seq/core/Tuple.hh"
#include "../Decls.hh"

#include "Number.hh"

namespace Number {
struct ConceptReal {
    using Bases = ::cong::lang::core::Tuple<Number::ConceptNumber>;
    static constexpr auto name = "Real";
    static constexpr auto description = "real number";
};

}

