
// Generated from /Users/haschker/Arbeitsbereich/generic-prog-lang/grammar/CongLexer.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"




class  CongLexer : public antlr4::Lexer {
public:
  enum {
    CONCEPT = 1, FUNCTION = 2, NAMESPACE = 3, LET = 4, DESCRIPTION = 5, 
    GENERICIMPL = 6, REQUIRES = 7, TIME = 8, SPACE = 9, LANG = 10, LBRACE = 11, 
    RBRACE = 12, VARARGS = 13, LPAREN = 14, RPAREN = 15, COLON = 16, SEMI = 17, 
    AMP = 18, ARROW = 19, COMMA = 20, ASSIGN = 21, PLUS = 22, MINUS = 23, 
    MUL = 24, DIV = 25, MOD = 26, LT = 27, GT = 28, DOUBLE_COLON = 29, OPEN_BINDING = 30, 
    DYNAMIC_ANNOTATOR = 31, REAL = 32, BOOL = 33, NUMBER = 34, STRING = 35, 
    IDENTIFIER = 36, WHITESPACE = 37, COMMENT = 38, LINE_COMMENT = 39, OTHER = 40
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

