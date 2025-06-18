#pragma once

#include <utility>                      // for stdlib core functions
#include "Seq/core/Tuple.hh"

// Tuple
namespace cong::lang
{
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


namespace cong::lang {

    namespace local {
    template<class Concept_>
    struct HasConcept
    {
    private:
        template<class T>
        struct CheckSingleConcept;
        
        template<class TupleOfBases_>
        struct Dispatch;

        template<>
        struct Dispatch<core::Tuple<>>
        {
            using Type = core::False;
        };

        template<class T, class... Ts>
        struct Dispatch<core::Tuple<T, Ts...>>
        {
            using Type = typename std::conditional<
                std::is_same<typename CheckSingleConcept<T>::Type, core::True>::value,
                core::True,
                typename Dispatch<core::Tuple<Ts...>>::Type
            >::type;
        };

        template<class T>
        struct CheckSingleConcept
        {
        private:
            using Plain_ = typename core::Plain::Call<T>::Type;

            /* SFINAE hack to check if bases exists; todo: remove? */
            template<typename U>
            static auto has_bases_impl(int) -> decltype(typename U::Bases{}, std::true_type{});
            template<typename U>
            static std::false_type has_bases_impl(...);
            
            using has_bases = decltype(has_bases_impl<Plain_>(0));
            
            using recursive_result = std::conditional_t<
                has_bases::value,
                typename Dispatch<typename Plain_::Bases>::Type,
                core::False
            >;
            
        public:
            using Type = typename std::conditional_t<
                std::is_same_v<Concept_, Plain_>,
                core::True,
                recursive_result
            >;
        };

    public:
        template<class T>
        struct Call
        {
            using Type = typename CheckSingleConcept<T>::Type;
        };
    };
    }

    struct StaticTag {};


}