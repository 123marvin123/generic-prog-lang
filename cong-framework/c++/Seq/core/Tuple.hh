#pragma once

#include "../../Boolean/core/BooleanStatic.hh"
#include "../../Number/core/NaturalStatic.hh"
#include "../../Type.hh"

#include <utility>

namespace cong::lang::core
{
    template <typename... ItemS>
    using Tuple = std::tuple<ItemS...>;

    template <typename... ItemS>
    constexpr
    Tuple<ItemS...>
    tuple(ItemS&&... itemS)
    {
        return {std::forward<ItemS>(itemS)...};
    }

    struct IsTuple
    {
    private:
        template <typename>
        struct Dispatch
        {
            using Type = False;
        };

        template <typename... Elems>
        struct Dispatch<Tuple<Elems...>>
        {
            using Type = True;
        };

    public:
        template <typename Tuple_>
        struct Call
        {
            using Type = typename Dispatch<Tuple_>::Type;

            static constexpr Type call(Tuple_&& t)
            {
                return {};
            }
        };
    };

    struct Length
    {
        template <typename Tuple_>
        struct Call
        {
            using Type = NaturalStatic<
                std::tuple_size_v<typename Plain::Call<Tuple_>::Type>
            >;

            static Type call(Tuple_)
            {
                return {};
            }
        };
    };

    struct ItemAt
    {
        template <typename Tuple_, typename Offset_>
        struct Call
        {
            using Type = std::tuple_element_t<Offset_::native(),
                                              typename Plain::Call<Tuple_>::Type
            >&;

            static Type call(Tuple_& tuple,
                             Offset_)
            {
                return std::get<Offset_::native()>(tuple);
            }
        };
    };

    struct Item
    {
        template <typename Tuple_>
        struct Call
        {
        private:
            using ItemAt_ = ItemAt::Call<Tuple_, Zero>;

        public:
            using Type = typename ItemAt_::Type;

            static Type call(Tuple_& tuple)
            {
                return ItemAt_::call(std::forward<Tuple_>(tuple), Zero{});
            }
        };
    };

    namespace local
    {
        template <typename Fun_,
                  typename Init_,
                  typename Tuple_,
                  typename Length_,
                  typename Offset_>
        struct FoldDispatch
        {
        private:
            using FunCall_ = typename Fun_::template Call<Init_,
                                                          typename Plain::Call<typename ItemAt::Call<Tuple_,
                                                              Offset_>::Type>::Type>::Type;
            using Dispatch_ = FoldDispatch<Fun_,
                                           FunCall_,
                                           Tuple_,
                                           Length_,
                                           typename Succ::Call<Offset_>::Type>;

        public:
            using Type = typename Dispatch_::Type;

            static Type call(Fun_ fun,
                             Init_ init,
                             Tuple_ tuple)
            {
                return Dispatch_::call(fun,
                                       FunCall_::call(init,
                                                      ItemAt
                                                      ::Call<Tuple_, Offset_>
                                                      ::call(tuple,
                                                             Offset_{})),
                                       tuple);
            }
        };

        template <typename Fun_,
                  typename Init_,
                  typename Tuple_,
                  typename Length_>
        struct FoldDispatch<Fun_, Init_, Tuple_, Length_, Length_>
        {
            using Type = Init_;

            static Type call(Fun_,
                             Init_ init,
                             Tuple_)
            {
                return init;
            }
        };
    }

    struct Fold
    {
        template <typename Fun_, typename Init_, typename Tuple_>
        struct Call
            : local::FoldDispatch<Fun_,
                                  Init_,
                                  Tuple_,
                                  typename Length::Call<Tuple_>::Type,
                                  Zero>
        {
        };
    };

    struct Fold1
    {
        template <typename Fun_, typename Tuple_>
        struct Call
        {
        private:
            using Dispatch_ = local::FoldDispatch<Fun_,
                                                  typename Plain::Call<typename ItemAt::Call<
                                                      Tuple_, Zero>::Type>::Type,
                                                  Tuple_,
                                                  typename Length::Call<Tuple_>::Type,
                                                  One>;

        public:
            using Type = typename Dispatch_::Type;

            static Type call(Fun_ fun,
                             Tuple_ tuple)
            {
                return Dispatch_::call(fun,
                                       ItemAt::Call<Tuple_, NaturalStatic<0>>::call(tuple, NaturalStatic<0>{}),
                                       tuple);
            }
        };
    };

    struct Transform
    {
    private:
        template <typename Fun_,
                  typename Tuple_>
        struct Dispatch;

        template <typename Fun_,
                  typename... ItemS_>
        struct Dispatch<Fun_, Tuple<ItemS_...>>
        {
        private:
            using PlainFun_ = typename Plain::Call<Fun_>::Type;

        public:
            using Type = Tuple<typename PlainFun_::template Call<ItemS_>::Type...>;

        private:
            static constexpr Type call_(Fun_&& fun,
                                        ItemS_... itemS)
            {
                return tuple(std::forward<Fun_>(fun)(itemS)...);
            }

        public:
            static constexpr Type call(Fun_&& fun,
                                       Tuple<ItemS_...> tuple)
            {
                return std::apply([&fun](ItemS_&... itemS)
                                  {
                                      return call_(std::forward<Fun_>(fun),
                                                   itemS...);
                                  },
                                  tuple);
            }
        };

    public:
        template <typename Fun_,
                  typename Tuple_>
        struct Call
            : Dispatch<Fun_,
                       Tuple_>
        {
        };
    };


    struct ToTupleNonRValRef
    {
        template <typename Tuple_>
        struct Call;

        template <typename... ItemS>
        struct Call<Tuple<ItemS...>>
        {
            using Type = Tuple<typename ToNonRValRef::Call<ItemS>::Type...>;
        };
    };

    template <typename... ItemS>
    using TupleNonRValRef = typename ToTupleNonRValRef::Call<Tuple<ItemS...>>::Type;

    template <typename... ItemS>
    constexpr
    TupleNonRValRef<ItemS...>
    tupleNonRValRef(ItemS&&... itemS)
    {
        return {std::forward<ItemS>(itemS)...};
    }
};
