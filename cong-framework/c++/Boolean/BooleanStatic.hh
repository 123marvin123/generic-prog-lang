#pragma once

#include "Boolean.hh"
#include "../Type.hh"
#include <type_traits>

namespace cong::lang::core
{
    namespace intern {
        // type only, not to be instantiated
        template <typename Native_, Native_ native_>
        struct BooleanStatic
        {
            using Native = Native_;
            /**
 * @brief Retrieves the compile-time boolean value.
 *
 * This static constexpr function returns the constant boolean value represented
 * by the template parameter `native_`, allowing access to this value at compile time.
 *
 * @return Native The compile-time boolean constant.
 */
static constexpr Native native() { return native_; }
        };
    };

    template <Boolean native_>
    using BooleanStatic = intern::BooleanStatic<Boolean, native_>;

    using True = BooleanStatic<true>;
    using False = BooleanStatic<false>;

    struct Cond
    {
    private:
      template <typename BooleanStatic_,
                typename TypeTrue_,
                typename TypeFalse_>
      struct Dispatch_;

      template <typename Native_,
                typename TypeTrue_,
                typename TypeFalse_>
      struct Dispatch_<intern::BooleanStatic<Native_,true>,
                       TypeTrue_,
                       TypeFalse_>
      {
        using Type = TypeTrue_;
      };

      template <typename Native_,
                typename TypeTrue_,
                typename TypeFalse_>
      struct Dispatch_<intern::BooleanStatic<Native_,false>,
                       TypeTrue_,
                       TypeFalse_>
      {
        using Type = TypeFalse_;
      };
    public:
      template <typename BooleanStatic_,
                typename TypeTrue_,
                typename TypeFalse_>
      struct Call
        : Dispatch_<typename Plain::Call<BooleanStatic_>::Type,
                    TypeTrue_,
                    TypeFalse_>
      {};
    };

    template <class Fun_,
              class Cond_,
              typename Default_>
    struct FunByCond
    {
    private:
      template <typename BooleanStatic_, typename... ArgS_>
      struct Dispatch_;
      template <typename Native_,
                typename... ArgS_>
      struct Dispatch_<intern::BooleanStatic<Native_,false>, ArgS_...>
      {
        using Type = Default_;
      };
      template <typename Native_,
                typename... ArgS_>
      struct Dispatch_<intern::BooleanStatic<Native_,true>, ArgS_...>
        : Fun_::template Call<ArgS_...>
      {
      private:
        using Base_ = typename Fun_::template Call<ArgS_...>;
      public:
        using Type = typename Base_::Type;
      };
    public:
      template <typename Arg1_, typename... ArgS_>
      struct Call
        : Dispatch_<typename Cond_::template Call<Arg1_>::Type,
                    Arg1_,
                    ArgS_...>
      {};
    };
}
