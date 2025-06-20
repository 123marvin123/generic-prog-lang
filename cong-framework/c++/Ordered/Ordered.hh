#pragma once

#include "Seq/core/Tuple.hh"
#include "Decls.hh"
#include "Val.hh"

#include "Object/Object.hh"

namespace Ordered {
struct ConceptOrdered : cong::lang::intern::Val, cong::lang::ConceptTag {
    using Bases = ::cong::lang::core::Tuple<Object::ConceptObject>;
    static constexpr cong::lang::core::StringStatic name = "Ordered";
    static constexpr cong::lang::core::StringStatic description = "element of totally ordered set";
};

}

