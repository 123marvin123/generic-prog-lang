
// Generated from /Users/haschker/Arbeitsbereich/generic-prog-lang/grammar/Cong.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"




class  CongLexer : public antlr4::Lexer {
public:
  enum {
    T__0 = 1, T__1 = 2, T__2 = 3, T__3 = 4, T__4 = 5, T__5 = 6, T__6 = 7, 
    T__7 = 8, T__8 = 9, T__9 = 10, T__10 = 11, T__11 = 12, T__12 = 13, T__13 = 14, 
    T__14 = 15, T__15 = 16, CONCEPT = 17, FUNCTION = 18, NAMESPACE = 19, 
    LET = 20, DESCRIPTION = 21, GENERICIMPL = 22, REQUIRES = 23, TIME = 24, 
    SPACE = 25, LBRACE = 26, RBRACE = 27, VARARGS = 28, REAL = 29, BOOL = 30, 
    NUMBER = 31, STRING = 32, IDENTIFIER = 33, WHITESPACE = 34, COMMENT = 35, 
    LINE_COMMENT = 36, OTHER = 37
  };

  explicit CongLexer(antlr4::CharStream *input);

  ~CongLexer() override;


  std::string getGrammarFileName() const override;

  const std::vector<std::string>& getRuleNames() const override;

  const std::vector<std::string>& getChannelNames() const override;

  const std::vector<std::string>& getModeNames() const override;

  const antlr4::dfa::Vocabulary& getVocabulary() const override;

  antlr4::atn::SerializedATNView getSerializedATN() const override;

  const antlr4::atn::ATN& getATN() const override;

  // By default the static state used to implement the lexer is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:

  // Individual action functions triggered by action() above.

  // Individual semantic predicate functions triggered by sempred() above.

};

