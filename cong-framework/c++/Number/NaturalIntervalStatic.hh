#pragma once

#include "NaturalStatic.hh"
#include "../Boolean/BooleanStatic.hh"

namespace cong::lang::core {
    namespace intern
    {
        // type only, not to be instantiated
        template <typename Native_, Native_ min_, Native_ max_>
        struct NaturalIntervalStatic
        {
        };
    };

    template <Natural min_, Natural max_ = natInf>
    using NaturalIntervalStatic = intern::NaturalIntervalStatic<Natural, min_, max_>;

    struct NaturalIntervalStaticFromNaturalStatic
    {
    private:
      template <typename NaturalStatic_>
      struct Dispatch_;

      template <typename Native_, Native_ value_>
      struct Dispatch_<intern::NaturalStatic<Native_, value_>>
      {
        using Type = NaturalIntervalStatic<value_, value_>;
      };
    public:
      template <typename NaturalIntervalStatic_>
      struct Call
        : Dispatch_<typename Plain::Call<NaturalIntervalStatic_>::Type>
      {};
    };

    struct IsEmpty
    {
    private:
      template <typename NaturalIntervalStatic_>
      struct Dispatch_;

      template <typename Native_, Native_ min_, Native_ max_>
      struct Dispatch_<intern::NaturalIntervalStatic<Native_, min_, max_>>
      {
        using Type = BooleanStatic<(min_ > max_)>;
      };
    public:
      template <typename NaturalIntervalStatic_>
      struct Call
        : Dispatch_<typename Plain::Call<NaturalIntervalStatic_>::Type>
      {};
    };

    struct IsElement
    {
    private:
      template <typename NaturalIntervalStatic_,
                typename NaturalStatic_>
      struct Dispatch_;

      template <typename Native_, Native_ min_, Native_ max_, Native_ value_>
      struct Dispatch_<intern::NaturalIntervalStatic<Native_, min_, max_>,
                       NaturalStatic<value_>>
      {
        using Type = BooleanStatic<min_ <= value_ && value_ <= max_>;
      };
    public:
      template <typename NaturalIntervalStatic_,
                typename NaturalStatic_>
      struct Call
        : Dispatch_<typename Plain::Call<NaturalIntervalStatic_>::Type,
                    typename Plain::Call<NaturalStatic_>::Type>
      {};
    };

    // @todo further Set functions?

    struct Intersect
    {
    private:
      template <typename NaturalIntervalStatic1_,
                typename NaturalIntervalStatic2_>
      struct Dispatch_;

      template <Natural min1_, Natural max1_, Natural min2_, Natural max2_>
      struct Dispatch_<NaturalIntervalStatic<min1_, max1_>,
                       NaturalIntervalStatic<min2_, max2_>>
      {
        using Type = NaturalIntervalStatic<Max::Call<NaturalStatic<min1_>,
                                                     NaturalStatic<min2_>>::Type::value,
                                           Min::Call<NaturalStatic<max1_>,
                                                     NaturalStatic<max2_>>::Type::value>;
      };
    public:
      template <typename NaturalIntervalStatic1_,
                typename NaturalIntervalStatic2_>
      struct Call
        : Dispatch_<typename Plain::Call<NaturalIntervalStatic1_>::Type,
                    typename Plain::Call<NaturalIntervalStatic2_>::Type>
      {};
    };
};
