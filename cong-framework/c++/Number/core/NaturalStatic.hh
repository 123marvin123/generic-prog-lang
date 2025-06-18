#pragma once

#include "Natural.hh"
#include "../../Type.hh"

namespace cong::lang::core
{
    namespace intern
    {
        // type only, not to be instantiated
        template <typename Native_, Native_ native_>
        struct NaturalStatic
        {
            static constexpr Native_ native()
            {
                return native_;
            }
        };
    };

    template <Natural native_>
    using NaturalStatic = intern::NaturalStatic<Natural, native_>;

    using Zero = NaturalStatic<0>;
    using One = NaturalStatic<1>;

    struct Min
    {
    private:
        template <typename Arg1_,
                  typename Arg2_>
        struct Dispatch_;

        template <typename Native_,
                  Native_ native1_,
                  Native_ native2_>
        struct Dispatch_<intern::NaturalStatic<Native_, native1_>,
                         intern::NaturalStatic<Native_, native2_>>
        {
            using Type = intern::NaturalStatic<Native_,
                                               (native1_ == natInf
                                                    ? native2_
                                                    : (native2_ == natInf
                                                           ? native1_
                                                           : (native1_ < native2_ ? native1_ : native2_)))>;
        };

    public:
        template <typename Arg1_,
                  typename Arg2_>
        struct Call
            : Dispatch_<typename Plain::Call<Arg1_>::Type,
                        typename Plain::Call<Arg2_>::Type>
        {
        };
    };

    struct Max
    {
    private:
        template <typename Arg1_,
                  typename Arg2_>
        struct Dispatch_;

        template <typename Native_,
                  Native_ native1_,
                  Native_ native2_>
        struct Dispatch_<intern::NaturalStatic<Native_, native1_>,
                         intern::NaturalStatic<Native_, native2_>>
        {
            using Type = intern::NaturalStatic<Native_,
                                               (native1_ == natInf
                                                    ? native2_
                                                    : (native2_ == natInf
                                                           ? native1_
                                                           : (native1_ > native2_ ? native1_ : native2_)))>;
        };

    public:
        template <typename Arg1_,
                  typename Arg2_>
        struct Call
            : Dispatch_<typename Plain::Call<Arg1_>::Type,
                        typename Plain::Call<Arg2_>::Type>
        {
        };
    };

#define CLASS_ intern::NaturalStatic
#include "../../core/Operator.hh"
#include "operator.hh"
#include "../../core/Operator_foot.hh"
#undef CLASS_
};
