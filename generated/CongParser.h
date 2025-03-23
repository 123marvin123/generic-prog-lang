
// Generated from /Users/haschker/CLionProjects/masterthesis-transpiler/grammar/Cong.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"




class  CongParser : public antlr4::Parser {
public:
  enum {
    T__0 = 1, T__1 = 2, T__2 = 3, T__3 = 4, T__4 = 5, T__5 = 6, T__6 = 7, 
    T__7 = 8, T__8 = 9, T__9 = 10, T__10 = 11, T__11 = 12, T__12 = 13, T__13 = 14, 
    T__14 = 15, CONCEPT = 16, FUNCTION = 17, NAMESPACE = 18, DESCRIPTION = 19, 
    GENERICIMPL = 20, REQUIRES = 21, LBRACE = 22, RBRACE = 23, VARARGS = 24, 
    REAL = 25, BOOL = 26, NUMBER = 27, STRING = 28, IDENTIFIER = 29, WHITESPACE = 30, 
    COMMENT = 31, LINE_COMMENT = 32, OTHER = 33
  };

  enum {
    RuleTranslationUnit = 0, RuleStmnt = 1, RuleConceptDefinitionStmnt = 2, 
    RuleConceptDefinitionBases = 3, RuleNamespaceStmnt = 4, RuleFunctionStmnt = 5, 
    RuleFunctionBody = 6, RuleFunctionBodyStmnt = 7, RuleParameterList = 8, 
    RuleParameter = 9, RuleExpression = 10, RulePlaceholderOrQualifiedId = 11, 
    RuleConceptPlaceholder = 12, RuleQualifiedIdentifier = 13, RuleLiteral = 14
  };

  explicit CongParser(antlr4::TokenStream *input);

  CongParser(antlr4::TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options);

  ~CongParser() override;

  std::string getGrammarFileName() const override;

  const antlr4::atn::ATN& getATN() const override;

  const std::vector<std::string>& getRuleNames() const override;

  const antlr4::dfa::Vocabulary& getVocabulary() const override;

  antlr4::atn::SerializedATNView getSerializedATN() const override;


  class TranslationUnitContext;
  class StmntContext;
  class ConceptDefinitionStmntContext;
  class ConceptDefinitionBasesContext;
  class NamespaceStmntContext;
  class FunctionStmntContext;
  class FunctionBodyContext;
  class FunctionBodyStmntContext;
  class ParameterListContext;
  class ParameterContext;
  class ExpressionContext;
  class PlaceholderOrQualifiedIdContext;
  class ConceptPlaceholderContext;
  class QualifiedIdentifierContext;
  class LiteralContext; 

  class  TranslationUnitContext : public antlr4::ParserRuleContext {
  public:
    TranslationUnitContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *EOF();
    std::vector<StmntContext *> stmnt();
    StmntContext* stmnt(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  TranslationUnitContext* translationUnit();

  class  StmntContext : public antlr4::ParserRuleContext {
  public:
    StmntContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ConceptDefinitionStmntContext *conceptDefinitionStmnt();
    NamespaceStmntContext *namespaceStmnt();
    FunctionStmntContext *functionStmnt();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  StmntContext* stmnt();

  class  ConceptDefinitionStmntContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *name = nullptr;
    antlr4::Token *desc = nullptr;
    ConceptDefinitionStmntContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *CONCEPT();
    antlr4::tree::TerminalNode *IDENTIFIER();
    antlr4::tree::TerminalNode *DESCRIPTION();
    ConceptDefinitionBasesContext *conceptDefinitionBases();
    antlr4::tree::TerminalNode *STRING();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ConceptDefinitionStmntContext* conceptDefinitionStmnt();

  class  ConceptDefinitionBasesContext : public antlr4::ParserRuleContext {
  public:
    ConceptDefinitionBasesContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<QualifiedIdentifierContext *> qualifiedIdentifier();
    QualifiedIdentifierContext* qualifiedIdentifier(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ConceptDefinitionBasesContext* conceptDefinitionBases();

  class  NamespaceStmntContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *name = nullptr;
    NamespaceStmntContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *NAMESPACE();
    antlr4::tree::TerminalNode *LBRACE();
    antlr4::tree::TerminalNode *RBRACE();
    antlr4::tree::TerminalNode *IDENTIFIER();
    std::vector<StmntContext *> stmnt();
    StmntContext* stmnt(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  NamespaceStmntContext* namespaceStmnt();

  class  FunctionStmntContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *name = nullptr;
    CongParser::QualifiedIdentifierContext *type = nullptr;
    FunctionStmntContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *FUNCTION();
    ParameterListContext *parameterList();
    FunctionBodyContext *functionBody();
    antlr4::tree::TerminalNode *IDENTIFIER();
    QualifiedIdentifierContext *qualifiedIdentifier();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  FunctionStmntContext* functionStmnt();

  class  FunctionBodyContext : public antlr4::ParserRuleContext {
  public:
    FunctionBodyContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LBRACE();
    antlr4::tree::TerminalNode *RBRACE();
    std::vector<FunctionBodyStmntContext *> functionBodyStmnt();
    FunctionBodyStmntContext* functionBodyStmnt(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  FunctionBodyContext* functionBody();

  class  FunctionBodyStmntContext : public antlr4::ParserRuleContext {
  public:
    FunctionBodyStmntContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    FunctionBodyStmntContext() = default;
    void copyFrom(FunctionBodyStmntContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  FunctionGenericImplContext : public FunctionBodyStmntContext {
  public:
    FunctionGenericImplContext(FunctionBodyStmntContext *ctx);

    antlr4::tree::TerminalNode *GENERICIMPL();
    antlr4::tree::TerminalNode *LBRACE();
    ExpressionContext *expression();
    antlr4::tree::TerminalNode *RBRACE();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  FunctionExpRequiresContext : public FunctionBodyStmntContext {
  public:
    FunctionExpRequiresContext(FunctionBodyStmntContext *ctx);

    antlr4::tree::TerminalNode *REQUIRES();
    antlr4::tree::TerminalNode *LBRACE();
    ExpressionContext *expression();
    antlr4::tree::TerminalNode *RBRACE();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  FunctionDescriptionContext : public FunctionBodyStmntContext {
  public:
    FunctionDescriptionContext(FunctionBodyStmntContext *ctx);

    antlr4::tree::TerminalNode *DESCRIPTION();
    antlr4::tree::TerminalNode *LBRACE();
    LiteralContext *literal();
    antlr4::tree::TerminalNode *RBRACE();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  FunctionBodyStmntContext* functionBodyStmnt();

  class  ParameterListContext : public antlr4::ParserRuleContext {
  public:
    ParameterListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ParameterContext *> parameter();
    ParameterContext* parameter(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ParameterListContext* parameterList();

  class  ParameterContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *name = nullptr;
    CongParser::PlaceholderOrQualifiedIdContext *type = nullptr;
    ParameterContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IDENTIFIER();
    PlaceholderOrQualifiedIdContext *placeholderOrQualifiedId();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ParameterContext* parameter();

  class  ExpressionContext : public antlr4::ParserRuleContext {
  public:
    ExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    ExpressionContext() = default;
    void copyFrom(ExpressionContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  CallExpressionContext : public ExpressionContext {
  public:
    CallExpressionContext(ExpressionContext *ctx);

    CongParser::QualifiedIdentifierContext *fun = nullptr;
    QualifiedIdentifierContext *qualifiedIdentifier();
    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ArithmeticExpressionContext : public ExpressionContext {
  public:
    ArithmeticExpressionContext(ExpressionContext *ctx);

    CongParser::ExpressionContext *left = nullptr;
    antlr4::Token *op = nullptr;
    CongParser::ExpressionContext *right = nullptr;
    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  LiteralExpressionContext : public ExpressionContext {
  public:
    LiteralExpressionContext(ExpressionContext *ctx);

    CongParser::LiteralContext *val = nullptr;
    LiteralContext *literal();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ParameterReferenceExpressionContext : public ExpressionContext {
  public:
    ParameterReferenceExpressionContext(ExpressionContext *ctx);

    antlr4::Token *param = nullptr;
    antlr4::tree::TerminalNode *IDENTIFIER();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  ExpressionContext* expression();
  ExpressionContext* expression(int precedence);
  class  PlaceholderOrQualifiedIdContext : public antlr4::ParserRuleContext {
  public:
    PlaceholderOrQualifiedIdContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    QualifiedIdentifierContext *qualifiedIdentifier();
    ConceptPlaceholderContext *conceptPlaceholder();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  PlaceholderOrQualifiedIdContext* placeholderOrQualifiedId();

  class  ConceptPlaceholderContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *name = nullptr;
    ConceptPlaceholderContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IDENTIFIER();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ConceptPlaceholderContext* conceptPlaceholder();

  class  QualifiedIdentifierContext : public antlr4::ParserRuleContext {
  public:
    QualifiedIdentifierContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> IDENTIFIER();
    antlr4::tree::TerminalNode* IDENTIFIER(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  QualifiedIdentifierContext* qualifiedIdentifier();

  class  LiteralContext : public antlr4::ParserRuleContext {
  public:
    LiteralContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *REAL();
    antlr4::tree::TerminalNode *NUMBER();
    antlr4::tree::TerminalNode *STRING();
    antlr4::tree::TerminalNode *BOOL();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  LiteralContext* literal();


  bool sempred(antlr4::RuleContext *_localctx, size_t ruleIndex, size_t predicateIndex) override;

  bool expressionSempred(ExpressionContext *_localctx, size_t predicateIndex);

  // By default the static state used to implement the parser is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:
};

