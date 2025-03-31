#pragma once

namespace cong::lang::core {

    template <typename Type_>
    struct FunStaticMake
    {
        template <typename... ArgS_>
        struct Call
        {
            using Type = Type_;
        };
    };

    template <class FunStatic_>
    struct FunByFunStatic
    {
        template <typename... ArgS_>
        struct Call
        {
            using Type = typename FunStatic_::template Call<ArgS_...>::Type;
            /**
             * @brief Returns a default-initialized instance of Type.
             *
             * This static constexpr method accepts a variable number of arguments, which are used only for
             * template type deduction, and returns a default-constructed object of type Type.
             *
             * @tparam ArgS_ Unused template parameter pack for argument types.
             * @param argS Provided arguments that do not influence the returned result.
             * @return A default-constructed object of type Type.
             */
            static constexpr Type call(ArgS_... argS)
            {
                return {};
            }
        };
    };

    struct FunId
    {
        template <typename Arg1_, typename... ArgS_>
        struct Call
        {
            using Type = Arg1_;
            /**
             * @brief Returns the first argument, ignoring any additional arguments.
             *
             * This static constexpr function acts as an identity function by returning the first parameter provided,
             * while all subsequent arguments are disregarded.
             *
             * @tparam Arg1_ The type of the first argument.
             * @tparam ArgS_ The types of the additional arguments, which are ignored.
             * @param arg1 The primary value to be returned.
             * @param ... Unused additional arguments.
             * @return The value of the first argument.
             */
            static constexpr Type call(Arg1_ arg1, ArgS_...)
            {
                return arg1;
            }
        };
    };
};

#define CONG_LANG_CORE_FUNSTATICBYMEMBERFUN(Fun_) \
    struct Fun_ \
    { \
        template <typename Arg1_, typename... ArgS_> \
        struct Call \
            : ::cong::lang::core::Plain::Call<Arg1_>::Type \
                ::Fun_::template Call<Arg1_, ArgS_...> \
        { \
        private: \
            using Base_ = typename ::cong::lang::core::Plain::Call<Arg1_>::Type \
                                    ::Fun_::template Call<Arg1_, ArgS_...>; \
        public: \
            using Type = typename Base_::Type; \
        }; \
    }

#define CONG_LANG_CORE_FUNBYMEMBERFUN(Fun_) \
    struct Fun_ \
    { \
        template <typename Arg1_, typename... ArgS_> \
        struct Call \
            : ::cong::lang::core::Plain::Call<Arg1_>::Type \
                ::Fun_::template Call<Arg1_, ArgS_...> \
        { \
        private: \
            using Base_ = typename ::cong::lang::core::Plain::Call<Arg1_>::Type \
                                    ::Fun_::template Call<Arg1_, ArgS_...>; \
        public: \
            using Type = typename Base_::Type; \
        }; \
    }

#define CONG_LANG_CORE_FUNBYMEMBER(Fun_, Member_, member_) \
    struct Fun_ \
    { \
        template <typename Arg1_> \
        struct Call \
        { \
            using Type = typename ::cong::lang::core::Plain::Call<Arg1_>::Type::Member_&; \
            static constexpr Type call(Arg1_ arg1) \
            { \
                return arg1.member_; \
            } \
        }; \
    }
