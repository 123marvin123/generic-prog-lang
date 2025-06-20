#pragma once

#include <utility> // std::remove_*

namespace cong::lang::core
{
    struct Plain
    {
        template <typename T>
        struct Call
        {
            using Type = std::remove_cv_t<std::remove_reference_t<T>>;
        };
    };

    struct ToNonRValRef
    {
        template <typename T>
        struct Call
        {
            using Type = T;
        };

        template <typename T>
        struct Call<T&&>
        {
            using Type = T;
        };
    };
};
