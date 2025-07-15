
// Generated from /Users/haschker/Arbeitsbereich/generic-prog-lang/grammar/CongLexer.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"




class  CongLexer : public antlr4::Lexer {
public:
  enum {
    CONCEPT = 1, FUNCTION = 2, NAMESPACE = 3, LET = 4, NAME = 5, DESCRIPTION = 6, 
    GENERICIMPL = 7, REQUIRES = 8, TIME = 9, SPACE = 10, LANG = 11, QUOTE = 12, 
    EVAL = 13, LBRACE = 14, RBRACE = 15, LPAREN = 16, RPAREN = 17, COLON = 18, 
    QUESTION_MARK = 19, SEMI = 20, AMP = 21, ARROW = 22, COMMA = 23, ASSIGN = 24, 
    EQUAL = 25, NOT_EQUAL = 26, PLUS = 27, MINUS = 28, MUL = 29, DIV = 30, 
    MOD = 31, POW = 32, LT = 33, LESS_EQUAL = 34, GT = 35, GREATER_EQUAL = 36, 
    DOUBLE_COLON = 37, LAMBDA_ARROW = 38, OPEN_BINDING = 39, DYNAMIC_ANNOTATOR = 40, 
    REAL = 41, BOOL = 42, INTEGER = 43, STRING = 44, IDENTIFIER = 45, WHITESPACE = 46, 
    COMMENT = 47, LINE_COMMENT = 48, OTHER = 49
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

