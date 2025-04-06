#pragma once

#include "Boolean.hh"
#include "../Type.hh"
#include <type_traits>

namespace cong::lang::core
{
    namespace intern
    {
        // type only, not to be instantiated
        template <typename Native_, Native_ native_>
        struct BooleanStatic
        {
            using Native = Native_;
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
        struct Dispatch_<intern::BooleanStatic<Native_, true>,
                         TypeTrue_,
                         TypeFalse_>
        {
            using Type = TypeTrue_;
        };

        template <typename Native_,
                  typename TypeTrue_,
                  typename TypeFalse_>
        struct Dispatch_<intern::BooleanStatic<Native_, false>,
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
        {
        };
    };

    template <class Fun_,
              class Cond_,
              typename Default_>
    struct FunByCond
    {
    private:
        template <typename BooleanStatic_, typename... ArgS_>
        struct Dispatch_;

        template <typename... ArgS_>
        struct Dispatch_<False, ArgS_...>
        {
            using Type = Default_;
        };

        template <typename... ArgS_>
        struct Dispatch_<True, ArgS_...>
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
        {
        };
    };

    struct Or_
    {
    private:
        template <typename Arg1_, typename Arg2_>
        struct Dispatch_;

        template <typename Native_,
                  Native_ native1_,
                  Native_ native2_>
        struct Dispatch_<intern::BooleanStatic<Native_, native1_>,
                         intern::BooleanStatic<Native_, native2_>>
        {
            using Type = intern::BooleanStatic<Native_, (native1_ || native2_)>;
        };

    public:
        template <typename Arg1_, typename Arg2_>
        struct Call
            : Dispatch_<typename Plain::Call<Arg1_>::Type,
                        typename Plain::Call<Arg2_>::Type>
        {
        };
    };

    struct And_
    {
    private:
        template <typename Arg1_, typename Arg2_>
        struct Dispatch_;

        template <typename Native_,
                  Native_ native1_,
                  Native_ native2_>
        struct Dispatch_<intern::BooleanStatic<Native_, native1_>,
                         intern::BooleanStatic<Native_, native2_>>
        {
            using Type = intern::BooleanStatic<Native_, (native1_ && native2_)>;
        };

    public:
        template <typename Arg1_, typename Arg2_>
        struct Call
            : Dispatch_<typename Plain::Call<Arg1_>::Type,
                        typename Plain::Call<Arg2_>::Type>
        {
        };
    };
}
