CONG_LANG_CORE_OPERATOR_1(Number, Succ,succ,(+1)+,AUTO); // @todo  where do the Spec's for Succ and Pred come from?
CONG_LANG_CORE_OPERATOR_1(Number, Pred,pred,(-1)+,AUTO); // @todo  same as Succ

CONG_LANG_CORE_OPERATOR_2(Number, Add,add,+,AUTO);
CONG_LANG_CORE_OPERATOR_2(Number, Sub,sub,-,AUTO);
CONG_LANG_CORE_OPERATOR_2(Number, Mul,mul,*,AUTO);
CONG_LANG_CORE_OPERATOR_2(Number, Div,div,/,AUTO);
CONG_LANG_CORE_OPERATOR_2(Number, Mod,mod,%,AUTO);

CONG_LANG_CORE_OPERATOR_2(Ordered, IsLess,isLess,<,AUTO);
CONG_LANG_CORE_OPERATOR_2(Ordered, IsLessEqual,isLessEqual,<=,AUTO);

CONG_LANG_CORE_OPERATOR_2(Ordered, IsGreater,isGreater,>,AUTO);
CONG_LANG_CORE_OPERATOR_2(Ordered, IsGreaterEqual,isGreaterEqual,>=,AUTO);