#include "Fun.hh"

#define CONG_LANG_CORE_OPERATOR_1(NS_, Name_, name_, OP_, MODE_) \
  CONG_LANG_CORE_FUN_1(CLASS_, NS_, Name_, name_, MODE_, (OP_ native_))

#define CONG_LANG_CORE_OPERATOR_2(NS_, Name_, name_, OP_, MODE_) \
  CONG_LANG_CORE_FUN_2(CLASS_, NS_, Name_, name_, MODE_, (native1_ OP_ native2_))