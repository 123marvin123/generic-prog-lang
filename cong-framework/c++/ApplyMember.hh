#pragma once

#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/comparison/greater.hpp>
#include <boost/preprocessor/arithmetic/inc.hpp>

#include <core/Lexical.hh>

#define CONG_LANG_INTERN_APPLYMEMBER_DEFAULT \
CONG_LANG_CORE_FUN_PROPAGATE \
(ApplyMember, \
(Spec__,Offset_),(), \
( \
(Base__, (typename Base_::template ApplyMember<Spec__, Offset_>)) \
), \
Base__ \
)

#define CONG_LANG_INTERN_APPLYMEMBER_LOCAL_PARAM_LIST(ignore_, n, text_) \
  BOOST_PP_CAT(BOOST_PP_CAT(Arg, BOOST_PP_INC(n)), _) \
  BOOST_PP_CAT(p, BOOST_PP_INC(n))

#define CONG_LANG_INTERN_APPLYMEMBER_LOCAL_TEMPL_LIST(ignore_, n, text_) \
  BOOST_PP_CAT(BOOST_PP_CAT(text_, BOOST_PP_INC(n)), _)

#define CONG_LANG_INTERN_APPLYMEMBER_LOCAL_TEMP_LIST2_1(ARITY_) \
  template <BOOST_PP_ENUM(ARITY_, CONG_LANG_INTERN_APPLYMEMBER_LOCAL_TEMPL_LIST, class Arg)>

#define CONG_LANG_INTERN_APPLYMEMBER_LOCAL_TEMP_LIST2_0(ARITY_) \
  template <typename...>

#define CONG_LANG_INTERN_APPLYMEMBER(PAREN_CLASS_, Name_, OFFSET_, ARITY_, PAREN_TYPE_, IMPL_) \
  template<> \
  struct CONG_LANG_CORE_INTERN_UNPAREN(PAREN_CLASS_)::ApplyMember \
  < \
    CONG_LANG_CORE_INTERN_PASTE(Spec, Name_), \
    ::cong::lang::core::NaturalStatic<OFFSET_> \
  > \
  { \
  private: \
    struct Fun_ \
    { \
      BOOST_PP_CAT(CONG_LANG_INTERN_APPLYMEMBER_LOCAL_TEMP_LIST2_, \
                   BOOST_PP_GREATER(ARITY_, 0)) \
      (ARITY_) \
      struct Call \
      { \
        using Type = CONG_LANG_CORE_INTERN_UNPAREN(PAREN_TYPE_); \
        static constexpr \
        Type \
        call(BOOST_PP_ENUM(ARITY_, CONG_LANG_INTERN_APPLYMEMBER_LOCAL_PARAM_LIST, ~)) \
        { \
          CONG_LANG_CORE_INTERN_UNPAREN(IMPL_); \
        } \
      }; \
    }; \
  public: \
    /* @todo PROPAGATE Call?! */ \
    template <typename Exp_, typename TupleOfExp_> \
    struct Call \
    { \
    private: \
      using Base_ = ::cong::lang::intern::local::ApplyByFun<Fun_>; \
      using Call_ = typename Base_::template Call<Exp_, TupleOfExp_>; \
    public: \
      using Type = typename Call_::Type; \
      static constexpr \
      Type \
      call(Exp_ exp, \
           TupleOfExp_ tupleOfExp) \
      { \
        return Call_::call(exp, \
                           tupleOfExp); \
      } \
    }; \
  }; \
  class AllowAndRequireSemicolonAfterMacroCall
