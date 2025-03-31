#pragma once

#include <tuple>
#include <utility>                      // for stdlib core functions

// Tuple
namespace cong::lang::core {

    template <typename... ItemS>
    using Tuple = std::tuple<ItemS...>;

    template <typename... ItemS>
    constexpr
    Tuple<ItemS...>
    tuple(ItemS&&... itemS)
    {
        return {std::forward<ItemS>(itemS)...};
    }

};

// Boolean

