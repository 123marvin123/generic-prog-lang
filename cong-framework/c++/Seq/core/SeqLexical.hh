#pragma once
#ifndef CONG_SEQ_LANG_CORE_SEQLEXICAL_HH
#define CONG_SEQ_LANG_CORE_SEQLEXICAL_HH

#include "../../core/Lexical.hh"
#include "../../Boolean/core/BooleanLexical.hh"
#include "../../Number/core/NaturalLexical.hh"

// @todo use alternative/additional implementations from boost preprocessor library?

#define CONG_LANG_CORE_LOCAL_ISEMPTY_DISPATCH_NONEMPTY()\
CONG_LANG_CORE_FALSE

#define CONG_LANG_CORE_LOCAL_ISEMPTY_DISPATCH()\
CONG_LANG_CORE_TRUE

#define CONG_LANG_CORE_LOCAL_ISEMPTY(...)\
CONG_LANG_CORE_INTERN_PASTE(CONG_LANG_CORE_LOCAL_ISEMPTY_DISPATCH,__VA_OPT__(_NONEMPTY))()

#define CONG_LANG_CORE_ISEMPTY(SEQ_)\
CONG_LANG_CORE_INTERN_APPLY(CONG_LANG_CORE_LOCAL_ISEMPTY,SEQ_)


#define CONG_LANG_CORE_LOCAL_LENGTH_REK_INDIRECT()\
CONG_LANG_CORE_LOCAL_LENGTH_REK

#define CONG_LANG_CORE_LOCAL_LENGTH_REK_DISPATCH_NONEMPTY(RESULT_, ITEM_, ...)\
CONG_LANG_CORE_LOCAL_LENGTH_REK_INDIRECT CONG_LANG_CORE_INTERN_PAREN(CONG_LANG_CORE_SUCC(RESULT_),\
                                                                     __VA_ARGS__)

#define CONG_LANG_CORE_LOCAL_LENGTH_REK_DISPATCH(RESULT_, ITEM_, ...)\
RESULT_

#define CONG_LANG_CORE_LOCAL_LENGTH_REK(RESULT_, ...)\
CONG_LANG_CORE_LOCAL_LENGTH_REK_DISPATCH##__VA_OPT__(_NONEMPTY)(RESULT_,\
                                                                __VA_ARGS__)

#define CONG_LANG_CORE_LENGTH(SEQ_)\
CONG_LANG_CORE_INTERN_EXPAND(CONG_LANG_CORE_LOCAL_LENGTH_REK(0,\
                                                             CONG_LANG_CORE_INTERN_UNPAREN(SEQ_)))


#define CONG_LANG_CORE_LOCAL_ITEM(ITEM_, ...)\
ITEM_

#define CONG_LANG_CORE_ITEM(SEQ_)\
CONG_LANG_CORE_LOCAL_ITEM SEQ_


// @todo shouldn't offsets start at 0 ?! be consistent with regular Seq!
#define CONG_LANG_CORE_LOCAL_ITEMAT_DISPATCH_1_1(P1_)\
P1_

#define CONG_LANG_CORE_LOCAL_ITEMAT_DISPATCH_1_2(P1_,P2_)\
P1_

#define CONG_LANG_CORE_LOCAL_ITEMAT_DISPATCH_1_3(P1_,P2_,P3_)\
P1_

#define CONG_LANG_CORE_LOCAL_ITEMAT_DISPATCH_1_4(P1_,P2_,P3_,P4_)\
P1_

#define CONG_LANG_CORE_LOCAL_ITEMAT_DISPATCH_1_5(P1_,P2_,P3_,P4_,P5_)\
P1_

#define CONG_LANG_CORE_LOCAL_ITEMAT_DISPATCH_1_6(P1_,P2_,P3_,P4_,P5_,P6_)\
P1_


#define CONG_LANG_CORE_LOCAL_ITEMAT_DISPATCH_2_2(P1_,P2_)\
P2_

#define CONG_LANG_CORE_LOCAL_ITEMAT_DISPATCH_2_3(P1_,P2_,P3_)\
P2_

#define CONG_LANG_CORE_LOCAL_ITEMAT_DISPATCH_2_4(P1_,P2_,P3_,P4_)\
P2_

#define CONG_LANG_CORE_LOCAL_ITEMAT_DISPATCH_2_5(P1_,P2_,P3_,P4_,P5_)\
P2_

#define CONG_LANG_CORE_LOCAL_ITEMAT_DISPATCH_2_6(P1_,P2_,P3_,P4_,P5_,P6_)\
P2_


#define CONG_LANG_CORE_LOCAL_ITEMAT_DISPATCH_3_3(P1_,P2_,P3_)\
P3_

#define CONG_LANG_CORE_LOCAL_ITEMAT_DISPATCH_3_4(P1_,P2_,P3_,P4_)\
P3_

#define CONG_LANG_CORE_LOCAL_ITEMAT_DISPATCH_3_5(P1_,P2_,P3_,P4_,P5_)\
P3_

#define CONG_LANG_CORE_LOCAL_ITEMAT_DISPATCH_3_6(P1_,P2_,P3_,P4_,P5_,P6_)\
P3_


#define CONG_LANG_CORE_LOCAL_ITEMAT_DISPATCH_4_4(P1_,P2_,P3_,P4_)\
P4_

#define CONG_LANG_CORE_LOCAL_ITEMAT_DISPATCH_4_5(P1_,P2_,P3_,P4_,P5_)\
P4_

#define CONG_LANG_CORE_LOCAL_ITEMAT_DISPATCH_4_6(P1_,P2_,P3_,P4_,P5_,P6_)\
P4_


#define CONG_LANG_CORE_LOCAL_ITEMAT_DISPATCH_5_5(P1_,P2_,P3_,P4_,P5_)\
P5_

#define CONG_LANG_CORE_LOCAL_ITEMAT_DISPATCH_5_6(P1_,P2_,P3_,P4_,P5_,P6_)\
P5_


#define CONG_LANG_CORE_LOCAL_ITEMAT_DISPATCH_6_6(P1_,P2_,P3_,P4_,P5_,P6_)\
P6_

#define CONG_LANG_CORE_ITEMAT(SEQ_, POS_)\
CONG_LANG_CORE_INTERN_EVAL(\
CONG_LANG_CORE_INTERN_APPLY\
(\
CONG_LANG_CORE_INTERN_PASTE\
(\
CONG_LANG_CORE_INTERN_PASTE(CONG_LANG_CORE_LOCAL_ITEMAT_DISPATCH_,POS_),\
CONG_LANG_CORE_INTERN_PASTE(_,CONG_LANG_CORE_LENGTH(SEQ_))\
),\
SEQ_\
)\
)

#define CONG_LANG_CORE_LOCAL_CONCAT(SEQ1_, ...)\
(CONG_LANG_CORE_INTERN_UNPAREN(SEQ1_)__VA_OPT__(,__VA_ARGS__))

// @todo comma only if both sequences are non-empty
// @todo improve/generalize: arbitrary number of SEQ
#define CONG_LANG_CORE_CONCAT(SEQ1_, SEQ2_)\
CONG_LANG_CORE_LOCAL_CONCAT(SEQ1_,CONG_LANG_CORE_INTERN_UNPAREN(SEQ2_))

// @todo move Map operations to cong/Map/c++/Lexical.hh ? be consistent with Seq API

#define CONG_LANG_CORE_LOCAL_FOLD_REK_INDIRECT()\
CONG_LANG_CORE_LOCAL_FOLD_REK

#define CONG_LANG_CORE_LOCAL_FOLD_REK_DISPATCH_NONEMPTY(FUN_, INIT_, ITEM_, ...)\
CONG_LANG_CORE_LOCAL_FOLD_REK_INDIRECT CONG_LANG_CORE_INTERN_PAREN(FUN_,\
                                                                   FUN_(INIT_,ITEM_),\
                                                                   __VA_ARGS__)

#define CONG_LANG_CORE_LOCAL_FOLD_REK_DISPATCH(FUN_, INIT_, ...)\
CONG_LANG_CORE_INTERN_UNPAREN(INIT_)

#define CONG_LANG_CORE_LOCAL_FOLD_REK(FUN_, INIT_, ...)\
CONG_LANG_CORE_LOCAL_FOLD_REK_DISPATCH##__VA_OPT__(_NONEMPTY)(FUN_,\
                                                              INIT_,\
                                                              __VA_ARGS__)

// `INIT_' must be a token enclosed in parentheses
// `FUN_' must take as arguments a parenthesized token `INIT_' and any item of 'SEQ_'
// and return a parenthesized token
#define CONG_LANG_CORE_FOLD(FUN_, INIT_, SEQ_)\
CONG_LANG_CORE_INTERN_EXPAND(CONG_LANG_CORE_LOCAL_FOLD_REK(FUN_,\
                                                           INIT_,\
                                                           CONG_LANG_CORE_INTERN_UNPAREN(SEQ_)))


#define CONG_LANG_CORE_LOCAL_FOLD1(FUN_, ITEM_, ...)\
CONG_LANG_CORE_LOCAL_FOLD(FUN_,\
                          (ITEM_),\
                          __VA_ARGS__)

#define CONG_LANG_CORE_FOLD1(FUN_, SEQ_)\
CONG_LANG_CORE_LOCAL_FOLD1(FUN_,\
                           CONG_LANG_CORE_INTERN_UNPAREN(SEQ_))


#define CONG_LANG_CORE_LOCAL_TRANSFORM_REK_INDIRECT() CONG_LANG_CORE_LOCAL_TRANSFORM_REK

#define CONG_LANG_CORE_LOCAL_TRANSFORM_REK(FUN_, ITEM_, ...)\
FUN_(ITEM_)\
__VA_OPT__(,CONG_LANG_CORE_LOCAL_TRANSFORM_REK_INDIRECT CONG_LANG_CORE_INTERN_PAREN(FUN_,\
                                                                                    __VA_ARGS__))

#define CONG_LANG_CORE_LOCAL_TRANSFORM(FUN_, ...)\
__VA_OPT__(CONG_LANG_CORE_INTERN_EXPAND(CONG_LANG_CORE_LOCAL_TRANSFORM_REK(FUN_,\
                                                                           __VA_ARGS__)))

// creates a new sequence of the results of applying 'FUN_' to each of 'SEQ_'s items
#define CONG_LANG_CORE_TRANSFORM(FUN_, SEQ_)\
(CONG_LANG_CORE_LOCAL_TRANSFORM(FUN_,\
                                CONG_LANG_CORE_INTERN_UNPAREN(SEQ_)))


// @todo currently unused - keep/replace?
// @todo convert to FOLD (similar to other repetitive macros) - actually different from FOLD,
//       rather a combination of TRANSFORM and CONCAT (define in terms of those?)
/*
#define CONG_LANG_CORE_FOR_EACH(FUN_, ...) \
__VA_OPT__(CONG_LANG_CORE_INTERN_EXPAND(CONG_LANG_CORE_LOCAL_FOR_EACH_HELPER(FUN_, __VA_ARGS__)))

#define CONG_LANG_CORE_LOCAL_FOR_EACH_HELPER(FUN_, a1, ...) \
FUN_(a1) \
__VA_OPT__(CONG_LANG_CORE_LOCAL_FOR_EACH_AGAIN CONG_LANG_CORE_INTERN_PAREN (FUN_, __VA_ARGS__))

#define CONG_LANG_CORE_LOCAL_FOR_EACH_AGAIN() CONG_LANG_CORE_LOCAL_FOR_EACH_HELPER
*/

#endif
