#pragma once

#define CONG_LANG_INTERN_APPLYMEMBER_DEFAULT \
CONG_LANG_CORE_FUN_PROPAGATE \
(ApplyMember, \
(Spec__,Offset_,Dummy_ = void),(), \
( \
(Base__, (typename Base_::template ApplyMember<Spec__, Offset_>)) \
), \
Base__ \
)