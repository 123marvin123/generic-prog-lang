#pragma once

#include "../Seq/core/Tuple.hh"
#include "../Decls.hh"

#include "../Object/Object.hh"

namespace Ordered {
struct ConceptOrdered {
    using Bases = ::cong::lang::core::Tuple<Object::ConceptObject>;
    static constexpr auto name = "Ordered";
    static constexpr auto description = "element of totally ordered set";
};

}

