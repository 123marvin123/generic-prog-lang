#pragma once

#include "../Seq/core/Tuple.hh"
#include "../Decls.hh"

#include "../Object/Object.hh"

namespace Number {
struct ConceptNumber {
    using Bases = ::cong::lang::core::Tuple<Object::ConceptObject>;
    static constexpr auto name = "Number";
    static constexpr auto description = "";
};

}

