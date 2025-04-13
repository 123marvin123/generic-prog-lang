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
  using NaturalStatic = intern::RealStatic<Real, native_>;

  struct Add
    {
    private:
        template <typename Arg1_, typename Arg2_>
        struct Dispatch_;

        template <typename Native_,
                  Native_ native1_,
                  Native_ native2_>
        struct Dispatch_<intern::RealStatic<Native_, native1_>, intern::RealStatic<Native_, native2_>>
        {
            using Type = intern::RealStatic<Native_, native1_ + native2_>;
        };

    public:
        template <typename Arg1_, typename Arg2_>
        struct Call
            : Dispatch_<typename Plain::Call<Arg1_>::Type, typename Plain::Call<Arg2_>::Type>
        {
        };
    };

    struct Sub
    {
    private:
        template <typename Arg1_, typename Arg2_>
        struct Dispatch_;

        template <typename Native_,
                  Native_ native1_,
                  Native_ native2_>
        struct Dispatch_<intern::RealStatic<Native_, native1_>, intern::RealStatic<Native_, native2_>>
        {
            using Type = intern::RealStatic<Native_, native1_ - native2_>;
        };

    public:
        template <typename Arg1_, typename Arg2_>
        struct Call
            : Dispatch_<typename Plain::Call<Arg1_>::Type, typename Plain::Call<Arg2_>::Type>
        {
        };
    };

    struct Mul
    {
    private:
        template <typename Arg1_, typename Arg2_>
        struct Dispatch_;

        template <typename Native_,
                  Native_ native1_,
                  Native_ native2_>
        struct Dispatch_<intern::RealStatic<Native_, native1_>, intern::RealStatic<Native_, native2_>>
        {
            using Type = intern::RealStatic<Native_, native1_ * native2_>;
        };

    public:
        template <typename Arg1_, typename Arg2_>
        struct Call
            : Dispatch_<typename Plain::Call<Arg1_>::Type, typename Plain::Call<Arg2_>::Type>
        {
        };
    };

    struct Div
    {
    private:
        template <typename Arg1_, typename Arg2_>
        struct Dispatch_;

        template <typename Native_,
                  Native_ native1_,
                  Native_ native2_>
        struct Dispatch_<intern::RealStatic<Native_, native1_>, intern::RealStatic<Native_, native2_>>
        {
            using Type = intern::RealStatic<Native_, native1_ / native2_>;
        };

    public:
        template <typename Arg1_, typename Arg2_>
        struct Call
            : Dispatch_<typename Plain::Call<Arg1_>::Type, typename Plain::Call<Arg2_>::Type>
        {
        };
    };
}