#pragma once

// common/elementary lexical (preprocessor) functions

// @todo establish USING_CONG via definition at compile time; provide short names
//       for global(!) macros

// @todo shouldn't EVAL be replaced by EXPAND?
#define CONG_LANG_CORE_INTERN_EVAL(EXP_)\
EXP_


// @todo isn't this covered by PASTE? keep as a special case with more expressive name?
// @todo if not: is one step of evaluation always enough?
// @todo replace all calls by juxtaposition of macro name and sequence by APPLY calls
//       - exception: recursive calls using PAREN (below)
// @todo revise name 'APPLY', distinguish(?) from 'Apply'
// @todo to Map/core/Lexical.hh?
#define CONG_LANG_CORE_LOCAL_APPLY(FUN_, SEQ_)\
CONG_LANG_CORE_INTERN_EVAL(FUN_ SEQ_)
#define CONG_LANG_CORE_INTERN_APPLY(FUN_, SEQ_)\
CONG_LANG_CORE_LOCAL_APPLY(FUN_,SEQ_)


// @todo replace by proper Seq operation(s) (concat?) -> Seq/core/Lexical.hh
#define CONG_LANG_CORE_LOCAL_UNPAREN(...)\
__VA_ARGS__
#define CONG_LANG_CORE_INTERN_UNPAREN(SEQ_)\
CONG_LANG_CORE_LOCAL_UNPAREN SEQ_


// needed for recursive macros - see https://www.scs.stanford.edu/~dm/blog/va-opt.html
#define CONG_LANG_CORE_INTERN_PAREN ()

// EN expands/evaluates argument(s) 2^(N+1)-1 times
// => EXPAND expands/evaluates argument(s) 63 times
#define CONG_LANG_CORE_LOCAL_E0(...) __VA_ARGS__
#define CONG_LANG_CORE_LOCAL_E1(...) CONG_LANG_CORE_LOCAL_E0(CONG_LANG_CORE_LOCAL_E0(__VA_ARGS__))
#define CONG_LANG_CORE_LOCAL_E2(...) CONG_LANG_CORE_LOCAL_E1(CONG_LANG_CORE_LOCAL_E1(__VA_ARGS__))
#define CONG_LANG_CORE_LOCAL_E3(...) CONG_LANG_CORE_LOCAL_E2(CONG_LANG_CORE_LOCAL_E2(__VA_ARGS__))
#define CONG_LANG_CORE_LOCAL_E4(...) CONG_LANG_CORE_LOCAL_E3(CONG_LANG_CORE_LOCAL_E3(__VA_ARGS__))
#define CONG_LANG_CORE_LOCAL_E5(...) CONG_LANG_CORE_LOCAL_E4(CONG_LANG_CORE_LOCAL_E4(__VA_ARGS__))
#define CONG_LANG_CORE_LOCAL_E6(...) CONG_LANG_CORE_LOCAL_E5(CONG_LANG_CORE_LOCAL_E5(__VA_ARGS__))
#define CONG_LANG_CORE_LOCAL_E7(...) CONG_LANG_CORE_LOCAL_E6(CONG_LANG_CORE_LOCAL_E6(__VA_ARGS__))
#define CONG_LANG_CORE_LOCAL_E8(...) CONG_LANG_CORE_LOCAL_E7(CONG_LANG_CORE_LOCAL_E7(__VA_ARGS__))
#define CONG_LANG_CORE_INTERN_EXPAND(...) CONG_LANG_CORE_LOCAL_E8(__VA_ARGS__)

// @todo implement recursively for VAR_ARGS
// @todo replace all nontrivial applications of ## by PASTE calls
// extra expansion needed in order to have arguments be evaluated before pasting (concatenation)
#define CONG_LANG_CORE_LOCAL_PASTE(P1_, P2_)\
CONG_LANG_CORE_INTERN_EVAL(P1_##P2_)
#define CONG_LANG_CORE_INTERN_PASTE(P1_, P2_)\
CONG_LANG_CORE_LOCAL_PASTE(P1_,P2_)

#define CONG_LANG_CORE_LOCAL_PASTE3(P1_, P2_, P3_)\
CONG_LANG_CORE_INTERN_EVAL(P1_##P2_##P3_)
#define CONG_LANG_CORE_INTERN_PASTE3(P1_, P2_, P3_)\
CONG_LANG_CORE_LOCAL_PASTE3(P1_,P2_,P3_)

#define CONG_LANG_CORE_LOCAL_PASTE4(P1_, P2_, P3_, P4_)\
CONG_LANG_CORE_INTERN_EVAL(P1_##P2_##P3_##P4_)
#define CONG_LANG_CORE_INTERN_PASTE4(P1_, P2_, P3_, P4_)\
CONG_LANG_CORE_LOCAL_PASTE4(P1_,P2_,P3_,P4_)
