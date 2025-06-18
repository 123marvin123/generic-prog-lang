#pragma once
#include "Real.hh"
#include "../../Type.hh"

namespace cong::lang::core
{
  namespace intern
  {
    // type only, not to be instantiated
    template <typename Native_, Native_ native_>
    struct RealStatic
    {
      using Native = Native_;
      static constexpr Native native() { return native_; }
    };
   }

  template <Real native_>
  using RealStatic = intern::RealStatic<Real, native_>;

#define CLASS_ intern::RealStatic
#include "../../core/Operator.hh"
#include "operator.hh"
#include "../../core/Operator_foot.hh"
#undef CLASS_

}