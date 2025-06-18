#include "Number/core/NaturalStatic.hh"

#include "ApplyMember.hh"
#include "Exp.hh"

#include "Traits.hh"
#include "core/Lexical.hh"

// @todo hidden dependency on Exp/core::BooleanStatic, core::NaturalStatic, core::Plain

// @todo ensure that DIR_ / STAGE_ / CONCEPT_ are defined

#define CONG_LANG_LOCAL_OPERATOR_TEMP_PAR_Static() \
  template <typename Native_, Native_ native_>

#define CONG_LANG_LOCAL_OPERATOR_TEMP_PAR_Dynamic() \
  template <typename Native_>


#define CONG_LANG_LOCAL_OPERATOR_TEMP_ARG_Static() \
  <Native_, native_>

#define CONG_LANG_LOCAL_OPERATOR_TEMP_ARG_Dynamic() \
  <Native_>


#define CONG_LANG_LOCAL_OPERATOR_TYPE_BOOL_Static(TEMP_, PAREN_CONST_) \
  ::cong::lang::B<PAREN_CONST_>

#define CONG_LANG_LOCAL_OPERATOR_TYPE_BOOL_Dynamic(TEMP_, PAREN_CONST_) \
  ::cong::lang::BooleanDynamic

// @todo for binary operations, use common/major type if Native_ differs between arguments
#define CONG_LANG_LOCAL_OPERATOR_TYPE_SAME_Static(TEMP_, PAREN_CONST_) \
  ::cong::lang::intern::Exp<::cong::lang::local::TEMP_<Native_, PAREN_CONST_>>;

#define CONG_LANG_LOCAL_OPERATOR_TYPE_SAME_Dynamic(TEMP_, PAREN_CONST_) \
  ::cong::lang::intern::Exp<::cong::lang::local::TEMP_<Native_>>;


#define CONG_LANG_LOCAL_OPERATOR_CONST_1(OP_) \
  OP_ \
  ::cong::lang::core::Plain::Call<typename ::cong::lang::intern::Eval::Call<Arg1_>::Type>::Type::native()

#define CONG_LANG_LOCAL_OPERATOR_CONST_2(OP_) \
  ::cong::lang::core::Plain::Call<typename ::cong::lang::intern::Eval::Call<Arg1_>::Type>::Type::native() \
  OP_ \
  ::cong::lang::core::Plain::Call<typename ::cong::lang::intern::Eval::Call<Arg2_>::Type>::Type::native()


#define CONG_LANG_LOCAL_OPERATOR_VALUE_Static_1(OP_) \
  /* empty */

#define CONG_LANG_LOCAL_OPERATOR_VALUE_Static_2(OP_) \
  /* empty */

#define CONG_LANG_LOCAL_OPERATOR_VALUE_Dynamic_1(OP_) \
  static_cast<typename Type::Native>(OP_ p1.native())

#define CONG_LANG_LOCAL_OPERATOR_VALUE_Dynamic_2(OP_) \
  static_cast<typename Type::Native>(p1.native() OP_ p2.native())


#define CONG_LANG_LOCAL_OPERATOR_APPLYMEMBER(PAREN_TEMP_PAR_, TEMP_, PAREN_TEMP_ARG_, NS_, Name_, name_, Op_, ARITY_, OFFSET_, PAREN_TYPE_, PAREN_VALUE_) \
  CONG_LANG_CORE_INTERN_UNPAREN(PAREN_TEMP_PAR_) \
  CONG_LANG_INTERN_APPLYMEMBER((TEMP_ CONG_LANG_CORE_INTERN_UNPAREN(PAREN_TEMP_ARG_)), \
                               NS_, Name_, OFFSET_, ARITY_, \
                               (CONG_LANG_CORE_INTERN_UNPAREN(PAREN_TYPE_)), \
                               (return {CONG_LANG_CORE_INTERN_UNPAREN(PAREN_VALUE_)}))

// Boolean/c++/core/operator.hh

#define CONG_LANG_LOCAL_OPERATOR_1(PAREN_TEMP_PAR_, TEMP_, PAREN_TEMP_ARG_, NS_, Name_, name_, OP_, ARITY_, PAREN_TYPE_, PAREN_VALUE_) \
  CONG_LANG_LOCAL_OPERATOR_APPLYMEMBER(PAREN_TEMP_PAR_, TEMP_, PAREN_TEMP_ARG_, NS_, Name_, name_, OP_, ARITY_, 1, PAREN_TYPE_, PAREN_VALUE_)
  
#define CONG_LANG_LOCAL_OPERATOR_2(PAREN_TEMP_PAR_, TEMP_, PAREN_TEMP_ARG_, NS_, Name_, name_, OP_, ARITY_, PAREN_TYPE_, PAREN_VALUE_) \
  CONG_LANG_LOCAL_OPERATOR_APPLYMEMBER(PAREN_TEMP_PAR_, TEMP_, PAREN_TEMP_ARG_, NS_, Name_, name_, OP_, ARITY_, 1, PAREN_TYPE_, PAREN_VALUE_); \
  CONG_LANG_LOCAL_OPERATOR_APPLYMEMBER(PAREN_TEMP_PAR_, TEMP_, PAREN_TEMP_ARG_, NS_, Name_, name_, OP_, ARITY_, 2, PAREN_TYPE_, PAREN_VALUE_)
  
#define CONG_LANG_LOCAL_OPERATOR(NEXT_, TEMP_PAR_STAGE_, TEMP_, TEMP_ARG_STAGE_, NS_, Name_, name_, OP_, ARITY_, TYPE_RESULT_STAGE_, CONST_ARITY_, VALUE_STAGE_ARITY_) \
  NEXT_((TEMP_PAR_STAGE_()), \
        TEMP_, \
        (TEMP_ARG_STAGE_()), \
        NS_, Name_, name_, OP_, ARITY_, \
        (TYPE_RESULT_STAGE_(TEMP_, (CONST_ARITY_(OP_)))), \
        (VALUE_STAGE_ARITY_(OP_)))

#define CONG_LANG_CORE_OPERATOR(NS_, Name_, name_, OP_, ARITY_, RESULT_) \
  CONG_LANG_LOCAL_OPERATOR(CONG_LANG_CORE_INTERN_PASTE(CONG_LANG_LOCAL_OPERATOR_,ARITY_), \
                 CONG_LANG_CORE_INTERN_PASTE(CONG_LANG_LOCAL_OPERATOR_TEMP_PAR_,STAGE_), \
                 CONG_LANG_CORE_INTERN_PASTE(CONCEPT_,STAGE_)/* yields TEMP_ */, \
                 CONG_LANG_CORE_INTERN_PASTE(CONG_LANG_LOCAL_OPERATOR_TEMP_ARG_,STAGE_), \
                 NS_, Name_, name_, OP_, ARITY_, \
                 CONG_LANG_CORE_INTERN_PASTE4(CONG_LANG_LOCAL_OPERATOR_TYPE_,RESULT_,_,STAGE_), \
                 CONG_LANG_CORE_INTERN_PASTE(CONG_LANG_LOCAL_OPERATOR_CONST_,ARITY_), \
                 CONG_LANG_CORE_INTERN_PASTE4(CONG_LANG_LOCAL_OPERATOR_VALUE_,STAGE_,_,ARITY_))


#define CONG_LANG_CORE_OPERATOR_1(NS_, Name_, name_, OP_, MODE_) \
  CONG_LANG_CORE_OPERATOR(NS_, Name_, name_, OP_, 1, SAME)

#define CONG_LANG_CORE_OPERATOR_2(NS_, Name_, name_, OP_, MODE_) \
  CONG_LANG_CORE_OPERATOR(NS_, Name_, name_, OP_, 2, SAME)

#define CONG_LANG_CORE_OPERATOR_2_2(NS_, Name_, name_, OP_, MODE_) \


// @todo quick workaround from https://stackoverflow.com/questions/32066204/ - improve if permanent
#define IDENT(x) x
#define PATH(x,y,z) IDENT(x)IDENT(y)IDENT(z)
#define PREFIX_ <
#define POSTFIX_ /core/operator.hh>
#include PATH(PREFIX_,DIR_,POSTFIX_)
#undef POSTFIX_
#undef PREFIX_
#undef PATH
#undef IDENT


#undef CONG_LANG_CORE_OPERATOR_2_2
#undef CONG_LANG_CORE_OPERATOR_2
#undef CONG_LANG_CORE_OPERATOR_1
#undef CONG_LANG_CORE_OPERATOR
#undef CONG_LANG_LOCAL_OPERATOR
#undef CONG_LANG_LOCAL_OPERATOR_2
#undef CONG_LANG_LOCAL_OPERATOR_1
#undef CONG_LANG_LOCAL_OPERATOR_APPLYMEMBER
#undef CONG_LANG_LOCAL_OPERATOR_VALUE_Dynamic_2
#undef CONG_LANG_LOCAL_OPERATOR_VALUE_Dynamic_1
#undef CONG_LANG_LOCAL_OPERATOR_VALUE_Static_2
#undef CONG_LANG_LOCAL_OPERATOR_VALUE_Static_1
#undef CONG_LANG_LOCAL_OPERATOR_CONST_2
#undef CONG_LANG_LOCAL_OPERATOR_CONST_1
#undef CONG_LANG_LOCAL_OPERATOR_TYPE_SAME_Dynamic
#undef CONG_LANG_LOCAL_OPERATOR_TYPE_SAME_Static
#undef CONG_LANG_LOCAL_OPERATOR_TYPE_BOOL_Dynamic
#undef CONG_LANG_LOCAL_OPERATOR_TYPE_BOOL_Static
#undef CONG_LANG_LOCAL_OPERATOR_TEMP_ARG_Dynamic
#undef CONG_LANG_LOCAL_OPERATOR_TEMP_ARG_Static
#undef CONG_LANG_LOCAL_OPERATOR_TEMP_PAR_Dynamic
#undef CONG_LANG_LOCAL_OPERATOR_TEMP_PAR_Static


#undef DIR_
#undef STAGE_
#undef CONCEPT_
