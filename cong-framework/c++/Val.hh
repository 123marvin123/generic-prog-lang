#pragma once

#include "Base.hh"

namespace cong::lang::intern
{
  class Val
    : public Base
  {
  public:
    // result is the given Exp_
    using ReduceSpace = core::FunStaticMake<core::NaturalStatic<0>>;
    using ReduceTime = core::FunStaticMake<core::NaturalStatic<1>>; // @todo appropriate?
    using ReduceValue = core::FunId;

    using ApplySpace = core::FunStaticMake<core::NaturalStatic<0>>;
    using ApplyTime = core::FunStaticMake<core::NaturalStatic<1>>; // @todo appropriate?
    using ApplyValue = core::FunId;
  };
}