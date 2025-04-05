#pragma once

#include <tuple>
#include <utility>                      // for stdlib core functions

// Tuple
namespace cong::lang
{
    namespace core
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
    };

    namespace intern
    {
        class Environment;
        template <class Impl_>
        class Exp;
    };

    namespace local
    {
        template <typename Env_,
                  typename Exp0_,
                  typename TupleOfExp_>
        class Bind;
    }

    template <typename Env_,
              typename Exp0_,
              typename... ExpS_>
    using Bind = intern::Exp<local::Bind<Env_,
                                         Exp0_,
                                         core::Tuple<ExpS_...>>>;

    template <typename Env_,
              typename Exp0_,
              typename... ExpS_>
    constexpr
    Bind<Env_,
         Exp0_,
         ExpS_...>
    bind(Env_&& env,
         Exp0_&& exp0,
         ExpS_&&... expS);
};

// Boolean
