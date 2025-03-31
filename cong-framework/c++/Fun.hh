//
// Created by Marvin Haschker on 30.03.25.
//

#ifndef FUN_HH
#define FUN_HH

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

#endif //FUN_HH
