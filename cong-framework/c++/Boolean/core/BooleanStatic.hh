#pragma once

#include "../../Object/core/Object.hh"
#include "Boolean.hh"

namespace cong::lang::core
{
    namespace intern
    {
        template <typename Native_, Native_ native_>
          struct BooleanStatic : Object
        {
            using Native = Native_;

            static constexpr Native native()
            {
                return native_;
            }
        };
    }

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

    template <Boolean native_>
    using BooleanStatic = intern::BooleanStatic<Boolean, native_>;

    using True = BooleanStatic<true>;
    using False = BooleanStatic<false>;

    template <class Fun_,
              class Cond_,
              typename Default_>
    struct FunByCond
    {
    private:
        // @todo replace Dispatch_ by Cond (from Boolean)? either Make or Id
        template <typename BooleanStatic_, typename... ArgS_>
        struct Dispatch_;
        template <typename Native_,
                  typename... ArgS_>
        struct Dispatch_<intern::BooleanStatic<Native_,false>, ArgS_...>
        {
            using Type = Default_;
        };
        // @todo PROPAGATE Call!?
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

#define CLASS_ intern::BooleanStatic
#include "../../core/Operator.hh"
#include "operator.hh"
#undef CLASS_
};