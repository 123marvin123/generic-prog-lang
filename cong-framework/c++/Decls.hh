#pragma once

#include <tuple>
#include <utility>                      // for stdlib core functions

// Tuple
namespace cong::lang::core {

    template <typename... ItemS>
    using Tuple = std::tuple<ItemS...>;

    template <typename... ItemS>
    /**
     * @brief Creates a tuple by perfectly forwarding the provided arguments.
     *
     * Constructs a tuple (an alias for std::tuple) containing the arguments, preserving each argument's value category through perfect forwarding.
     * The function is marked as constexpr, allowing it to be used in compile-time constant expressions when applicable.
     *
     * @tparam ItemS Types of the elements to be stored in the tuple.
     * @param itemS Variadic arguments to populate the tuple.
     * @return Tuple<ItemS...> A tuple containing the forwarded arguments.
     */
    constexpr
    Tuple<ItemS...>
    tuple(ItemS&&... itemS)
    {
        return {std::forward<ItemS>(itemS)...};
    }

};

// Boolean

