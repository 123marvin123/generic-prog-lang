
// Generated from /Users/haschker/Arbeitsbereich/generic-prog-lang/grammar/CongLexer.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"




class  CongLexer : public antlr4::Lexer {
public:
  enum {
    CONCEPT = 1, FUNCTION = 2, NAMESPACE = 3, LET = 4, NAME = 5, DESCRIPTION = 6, 
    GENERICIMPL = 7, REQUIRES = 8, TIME = 9, SPACE = 10, LANG = 11, QUOTE = 12, 
    EVAL = 13, LBRACE = 14, RBRACE = 15, VARARGS = 16, LPAREN = 17, RPAREN = 18, 
    COLON = 19, SEMI = 20, AMP = 21, ARROW = 22, COMMA = 23, ASSIGN = 24, 
    PLUS = 25, MINUS = 26, MUL = 27, DIV = 28, MOD = 29, POW = 30, LT = 31, 
    GT = 32, DOUBLE_COLON = 33, OPEN_BINDING = 34, DYNAMIC_ANNOTATOR = 35, 
    REAL = 36, BOOL = 37, INTEGER = 38, STRING = 39, IDENTIFIER = 40, WHITESPACE = 41, 
    COMMENT = 42, LINE_COMMENT = 43, OTHER = 44
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

