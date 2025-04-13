#pragma once

#include "../../Type.hh"

namespace cong::lang::core
{
    using Boolean = bool;

    struct Truthy
    {
    private:
        template<class T>
        struct Dispatch
        {
            using Type = bool;
            static constexpr bool call(const typename Plain::Call<T>::Type& b)
            {
                return b.native();
            }
        };
        template<>
        struct Dispatch<bool>
        {
            using Type = bool;
            static constexpr bool call(const bool& b)
            {
                return b;
            }
        };
    public:
        template<typename T>
        struct Call : Dispatch<typename Plain::Call<T>::Type>
        {
        };
    };

    struct Falsy
    {
    private:
        template<class T>
        struct Dispatch
        {
            using Type = bool;
            static constexpr bool call(const typename Plain::Call<T>::Type& b)
            {
                return !b.native();
            }
        };
        template<>
        struct Dispatch<bool>
        {
            static constexpr bool call(const bool& b)
            {
                return b == false;
            }
        };
    public:
        template<typename T>
        struct Call : Dispatch<typename Plain::Call<T>::Type>
        {
        };
    };
}
