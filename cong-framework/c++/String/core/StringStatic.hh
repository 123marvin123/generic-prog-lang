#pragma once

#include <algorithm>

namespace cong::lang::core {
    // https://dev.to/sgf4/strings-as-template-parameters-c20-4joh
    template<std::size_t N>
    struct StringStatic {

            consteval StringStatic(const char (&str)[N]) {
                std::copy_n(str, N, data);
            }

            consteval bool operator==(const StringStatic<N> str) const {
                return std::equal(str.data, str.data+N, data);
            }

            template<std::size_t N2>
            consteval bool operator==(const StringStatic<N2> s) const {
                return false;
            }

            template<std::size_t N2>
            consteval StringStatic<N+N2-1> operator+(const StringStatic<N2> str) const {
                char newchar[N+N2-1] {};
                std::copy_n(data, N-1, newchar);
                std::copy_n(str.data, N2, newchar+N-1);
                return newchar;
            }

            consteval char operator[](std::size_t n) const {
                return data[n];
            }

            consteval std::size_t size() const {
                return N-1;
            }

            char data[N] {};
        };


    template <StringStatic S>
    concept verbose_check = false;

    namespace detail
    {
        template<unsigned... digits>
        struct to_chars { static const char value[]; };

        template<unsigned... digits>
        constexpr char to_chars<digits...>::value[] = {('0' + digits)..., 0};

        template<unsigned rem, unsigned... digits>
        struct explode : explode<rem / 10, rem % 10, digits...> {};

        template<unsigned... digits>
        struct explode<0, digits...> : to_chars<digits...> {};
    }

    template<unsigned num>
    struct num_to_string : detail::explode<num> {};

    template<StringStatic A, StringStatic... B>
    static consteval auto concat()
    {
        return (A + ... + B);
    }

    template<StringStatic S>
    static consteval auto print_string()
    {
        static_assert(verbose_check<S>);
    }

}
