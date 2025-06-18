#pragma once

#include "../Seq/core/Tuple.hh"
#include "../Decls.hh"

#include "../Object/Object.hh"

namespace Boolean {
struct ConceptBoolean {
    using Bases = ::cong::lang::core::Tuple<Object::ConceptObject>;
    static constexpr auto name = "Boolean";
    static constexpr auto description = "";
};

}

