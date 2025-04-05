#pragma once

#include "Number/NaturalIntervalStatic.hh"
#include "Boolean/BooleanStatic.hh"

#include "Fun.hh"
#include "Undefined.hh"

namespace cong::lang::intern
{
  class Base
  {
  public:
    using IsStateful = core::FunStaticMake<core::False>;

    using ReduceSpace = core::FunStaticMake<core::Invalid>;
    using ReduceTime = core::FunStaticMake<core::Invalid>;
    using ReduceValue = core::FunStaticMake<core::Invalid>;

    using Arity = core::FunStaticMake<core::NaturalIntervalStatic<0>>;
    using ApplySpace = core::FunStaticMake<core::Invalid>;
    using ApplyTime = core::FunStaticMake<core::Invalid>;
    using ApplyValue = core::FunStaticMake<core::Invalid>;

    template <class Spec_, typename Offset_>
    struct ApplyMember
    {
      template <typename...>
      struct Call
      {
        using Type = core::Undefined;
      };
    };
  };
}