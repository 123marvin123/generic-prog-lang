
// Generated from /Users/haschker/Arbeitsbereich/generic-prog-lang/grammar/CongLexer.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"




class  CongLexer : public antlr4::Lexer {
public:
  enum {
    CONCEPT = 1, FUNCTION = 2, NAMESPACE = 3, LET = 4, DESCRIPTION = 5, 
    GENERICIMPL = 6, REQUIRES = 7, TIME = 8, SPACE = 9, LANG = 10, QUOTE = 11, 
    EVAL = 12, LBRACE = 13, RBRACE = 14, VARARGS = 15, LPAREN = 16, RPAREN = 17, 
    COLON = 18, SEMI = 19, AMP = 20, ARROW = 21, COMMA = 22, ASSIGN = 23, 
    PLUS = 24, MINUS = 25, MUL = 26, DIV = 27, MOD = 28, POW = 29, LT = 30, 
    GT = 31, DOUBLE_COLON = 32, OPEN_BINDING = 33, DYNAMIC_ANNOTATOR = 34, 
    REAL = 35, BOOL = 36, NUMBER = 37, STRING = 38, IDENTIFIER = 39, WHITESPACE = 40, 
    COMMENT = 41, LINE_COMMENT = 42, OTHER = 43
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

