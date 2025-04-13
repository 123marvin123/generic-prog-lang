#include "Lexical.hh"

#define CONG_LANG_CORE_INTERN_FUN_PRED(CLASS__, EXP_) \
  ::cong::lang::core::BooleanStatic<(EXP_)>

#define CONG_LANG_CORE_INTERN_FUN_AUTO(CLASS__, EXP_) \
  CLASS__<Native_, (EXP_)>

#define CONG_LANG_CORE_FUN_1(CLASS__, Name_, name_, MODE_, EXP_) \
  struct Name_ \
  { \
  private: \
    template <typename Arg_> \
    struct Dispatch_; \
    \
    template <typename Native_, \
              Native_ native_> \
    struct Dispatch_<CLASS__<Native_, native_>> \
    { \
      using Type = CONG_LANG_CORE_INTERN_PASTE(CONG_LANG_CORE_INTERN_FUN_,MODE_)(CLASS__, EXP_); \
    }; \
  public: \
    template <typename Arg_> \
    struct Call \
      : Dispatch_<typename Plain::Call<Arg_>::Type> \
    {}; \
  }

#define CONG_LANG_CORE_FUN_2(CLASS__, Name_, name_, MODE_, EXP_) \
  struct Name_ \
  { \
  private: \
    template <typename Arg1_, \
              typename Arg2_> \
    struct Dispatch_; \
    \
    /* @todo any proper use case which would justify/require using different Native1_/Native2_ */ \
    template <typename Native_, \
              Native_ native1_, \
              Native_ native2_> \
    struct Dispatch_<CLASS__<Native_, native1_>, \
                     CLASS__<Native_, native2_>> \
    { \
      using Type = CONG_LANG_CORE_INTERN_PASTE(CONG_LANG_CORE_INTERN_FUN_,MODE_)(CLASS__, EXP_); \
    }; \
  public: \
    template <typename Arg1_, \
              typename Arg2_> \
    struct Call \
      : Dispatch_<typename Plain::Call<Arg1_>::Type, \
                  typename Plain::Call<Arg2_>::Type> \
    {}; \
  }