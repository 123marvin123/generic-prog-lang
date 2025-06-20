#pragma once

#include "Seq/core/Tuple.hh"
#include "Decls.hh"
#include "Val.hh"

#include "Number/Number.hh"

namespace Number {
struct ConceptReal : cong::lang::intern::Val, cong::lang::ConceptTag {
    using Bases = ::cong::lang::core::Tuple<Number::ConceptNumber>;
    static constexpr cong::lang::core::StringStatic name = "Real";
    static constexpr cong::lang::core::StringStatic description = "real number";
};

}

