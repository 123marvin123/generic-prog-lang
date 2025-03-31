//
// Created by Marvin Haschker on 29.03.25.
//

#ifndef DECLS_HH
#define DECLS_HH

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



#endif //DECLS_HH
