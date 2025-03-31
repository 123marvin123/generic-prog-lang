#include <utility> // std::remove_*

namespace cong::lang::core {

    struct Plain
    {
        template <typename T>
        struct Call
        {
            using Type = typename std::remove_cv<typename std::remove_reference<T>::type>::type;
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
