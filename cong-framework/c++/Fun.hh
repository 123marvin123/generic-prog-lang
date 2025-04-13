#pragma once

#include "Seq/core/SeqLexical.hh"

#include "Type.hh"
#include "core/Lexical.hh"

#include <utility> // std::forward

// elementary Fun(ction) implementations and generic adapters
// Fun itself is not an argument

// dynamic version of Fun itself is not needed/useful, corresponds to Exp::ApplyValue

namespace cong::lang::core
{
  // @todo indicate arities as template parameters
  // @todo provide arities as member?

  // @todo AllowAndRequireSemicolonAfterMacroCall cannot be used here as re-declaration of a class
  //       member (if the Fun is one) are not allowed - why actually? alternative solution?

  // Fun(ction)s on static arguments (class template 'Call' contains type 'Type')

  // general structure:
  //struct FunStatic
  //{
  //  template <typename... ArgS_>
  //  struct Call
  //  {
  //    using Type = ...;
  //    CONG_LANG_CORE_DISPLAY_LEAF(Call, Type);
  //  };
  //};

  // a member Fun (of an Exp) takes the Exp as its first argument, hence all arguments are passed on
#define CONG_LANG_CORE_FUNSTATICBYMEMBERFUN(Fun_) \
struct Fun_ \
{ \
/* @todo PROPAGATE Call?! */ \
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

  // @todo can Fun_ and Member_ be considered identical identifiers?
  // @todo replace by family member data access?
  // @todo currently not used
#define CONG_LANG_CORE_FUNSTATICBYMEMBER(Fun_, Member_) \
struct Fun_ \
{ \
template <typename Arg1_> \
struct Call \
{ \
using Type = ::cong::lang::core::Plain::Call<Arg1_>::Type::Member_; \
}; \
}

  template <typename Type_>
  struct FunStaticMake
  {
    template <typename... ArgS_>
    struct Call
    {
      using Type = Type_;
    };
  };


  // Fun(ction)s on dynamic arguments (class template 'Call' contains type 'Type' and function 'call')

  // general structure:
  //struct Fun
  //{
  //  template <typename... ArgS_>
  //  struct Call
  //  {
  //    using Type = ...;
  //    CONG_LANG_CORE_DISPLAY_LEAF(Call, Type);
  //    static constexpr Type call(ArgS_... argS)
  //    {
  //      return ...;
  //    }
  //  };
  //};

  // @todo only used once (at this moment) - expendable?
  template <class FunStatic_>
  struct FunByFunStatic
  {
    // @todo PROPAGATE Call?!
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

  // @todo identical to CONG_LANG_CORE_FUNSTATICBYMEMBERFUN
  // @todo PROPAGATE Call?!
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

  // @todo provide as member Fun in generic Data component
#define CONG_LANG_CORE_FUNBYMEMBER(Fun_, Member_, member_) \
struct Fun_ \
{ \
template <typename Arg1_> \
struct Call \
{ \
using Type = typename ::cong::lang::core::Plain::Call<Arg1_>::Type::Member_&; /* @todo provide proper qualification */ \
static constexpr Type call(Arg1_ arg1) \
{ \
return arg1.member_; /* @todo private access required */ \
} \
}; \
}

  // not needed so far
  //template <typename Type_>
  //struct FunMake
  //{
  //  template <typename... ArgS_>
  //  struct Call
  //  {
  //    using Type = Type_;
  //    CONG_LANG_CORE_DISPLAY_LEAF(Call, Type);
  //    static constexpr Type call(ArgS_... argS)
  //    {
  //      return {argS...};
  //    }
  //  };
  //};

  // @todo better name (Id does not make sense for two arguments), rather a projection (from vararg)
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

  // @todo actually needed? might then also be needed for non-unary Fun1_?
  //template <class Fun1_, class Fun2_>
  //struct FunByComp
  //{
  //  // @todo PROPAGATE Call?!
  //  template <typename... ArgS_>
  //  struct Call
  //  {
  //  private:
  //    using Call2_ = typename Fun2_::template Call<ArgS_...>;
  //    using Call1_ = typename Fun1_::template Call<typename Call2_::Type>;
  //  public:
  //    using Type = typename Call1_::Type;
  //    CONG_LANG_CORE_DISPLAY_NODE(Call, Type);
  //    static constexpr Type call(ArgS_... argS)
  //    {
  //      return Call1_::call(Call2_::call(argS...));
  //    }
  //  };
  //};
}
  // @todo actually needed? (currently only once, in Exp.hh)
  // function front-end for static Fun
  // to be used in namespace ::cong::lang::core, outside of class
#define CONG_LANG_CORE_FUNCTION(Fun_, fun_) \
template <typename... ExpS_> \
typename Fun_::template Call<ExpS_...>::Type \
fun_(ExpS_&&... expS) \
{ \
/* @todo dep. on Tuple<>: */ \
/* CONG_LANG_ENSURE_ISTUPLEOFEXP(core::Tuple<ExpS_...>); */ \
return Fun_::template Call<ExpS_...>::call(std::forward<ExpS_>(expS)...); \
}


  /*
    macros for propagation/forwarding Fun type definitions in different flavors, chosen by the
    definition of CONG_LANG_CORE_FUN_PROPAGATE_...:
    * ..._EXPLICIT: type is explicitly defined, referring to the original's elements only on the lowest
    level (type alias and forwarded function call)
    * ..._INHERIT: type inherits from the original, i.e. it is a new type, but its members are not
    * ..._ALIAS: (default) type is a mere alias of the original
    From top to down, the number of types and code cost is decreasing, but debugging becomes more
    difficult.
  */

  // @todo introduce common solution for introducing compile-time settings
  // uncomment this line for debugging (or define the token via the compiler)
#define CONG_LANG_CORE_FUN_PROPAGATE_EXPLICIT // ..._INHERIT // ..._ALIAS

  // @todo move the following auxiliary macros to corresponding location
#define CONG_LANG_CORE_LOCAL_LET_PAIR(Name_, Original_) \
using Name_ = CONG_LANG_CORE_INTERN_UNPAREN(Original_);

#define CONG_LANG_CORE_LOCAL_LET(INIT_, Pair_) \
( \
CONG_LANG_CORE_INTERN_UNPAREN(INIT_) \
CONG_LANG_CORE_INTERN_APPLY(CONG_LANG_CORE_LOCAL_LET_PAIR, Pair_) \
)

#define CONG_LANG_CORE_LOCAL_TYPENAME(TYPE_) \
typename TYPE_

#define CONG_LANG_CORE_LOCAL_TEMPLATE(SEQOFTYPE_) \
template <CONG_LANG_CORE_INTERN_UNPAREN(CONG_LANG_CORE_TRANSFORM(CONG_LANG_CORE_LOCAL_TYPENAME, \
SEQOFTYPE_))>

#define CONG_LANG_CORE_LOCAL_TEMPLATE_ARGS(SEQOFTYPE_,SEQOFSPEC_) \
(<CONG_LANG_CORE_INTERN_UNPAREN(CONG_LANG_CORE_CONCAT(SEQOFTYPE_,SEQOFSPEC_))>)

#define CONG_LANG_CORE_LOCAL_TEMPLATE_SPEC(SEQOFTYPE_,SEQOFSPEC_) \
CONG_LANG_CORE_COND(CONG_LANG_CORE_ISEMPTY(SEQOFSPEC_), \
(), \
CONG_LANG_CORE_LOCAL_TEMPLATE_ARGS(SEQOFTYPE_,SEQOFSPEC_))

  /*
    @todo combine PROPAGATE with approach to encapsulate leaves of the expression correspondingly
    (including e.g. the DISPLAY of Call and Type) - maybe use Node/Leaf terminology
  */

  // in SEQLET_, type BASE_ must be defined as type of propagated Fun class
#if defined CONG_LANG_CORE_FUN_PROPAGATE_EXPLICIT

#define CONG_LANG_CORE_FUN_CALL_PROPAGATE(SEQLET_, BASE_) \
public: \
template <typename Exp_, typename TupleOfExp_> \
struct Call \
{ \
private: \
CONG_LANG_CORE_FOLD(CONG_LANG_CORE_LOCAL_LET, (), SEQLET_) \
using Call_ = typename BASE_::template Call<Exp_, TupleOfExp_>; \
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
}

#elif defined CONG_LANG_CORE_FUN_PROPAGATE_INHERIT

#define CONG_LANG_CORE_FUN_CALL_PROPAGATE(SEQLET_, BASE_) \
private: \
template <typename Exp_, typename TupleOfExp_> \
struct CallPropagate_ \
{ \
CONG_LANG_CORE_FOLD(CONG_LANG_CORE_LOCAL_LET, (), SEQLET_) \
using Call_ = typename BASE_::template Call<Exp_, TupleOfExp_>; \
}; \
public: \
template <typename Exp_, typename TupleOfExp_> \
struct Call \
: CallPropagate_<Exp_, TupleOfExp_>::Call_ \
{}

#else // #elif defined CONG_LANG_CORE_FUN_PROPAGATE_ALIAS

#define CONG_LANG_CORE_FUN_CALL_PROPAGATE(SEQLET_, BASE_) \
private: \
template <typename Exp_, typename TupleOfExp_> \
struct CallPropagate_ \
{ \
CONG_LANG_CORE_FOLD(CONG_LANG_CORE_LOCAL_LET, (), SEQLET_) \
using Call_ = typename BASE_::template Call<Exp_, TupleOfExp_>; \
}; \
public: \
template <typename Exp_, typename TupleOfExp_> \
using Call = typename CallPropagate_<Exp_, TupleOfExp_>::Call_

#endif

#define CONG_LANG_CORE_FUN_PROPAGATE(NAME_, SEQOFTYPE_, SEQOFSPEC_, SEQLET_, BASE_) \
CONG_LANG_CORE_LOCAL_TEMPLATE(SEQOFTYPE_) \
struct NAME_ CONG_LANG_CORE_LOCAL_TEMPLATE_SPEC(SEQOFTYPE_,SEQOFSPEC_) \
{ \
private: \
CONG_LANG_CORE_FOLD(CONG_LANG_CORE_LOCAL_LET, (), SEQLET_); \
public: \
CONG_LANG_CORE_FUN_CALL_PROPAGATE((), BASE_); \
}