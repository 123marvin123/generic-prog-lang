
// Generated from /Users/haschker/Arbeitsbereich/generic-prog-lang/grammar/Cong.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"




class  CongParser : public antlr4::Parser {
public:
  enum {
    T__0 = 1, T__1 = 2, T__2 = 3, T__3 = 4, T__4 = 5, T__5 = 6, T__6 = 7, 
    T__7 = 8, T__8 = 9, T__9 = 10, T__10 = 11, T__11 = 12, T__12 = 13, T__13 = 14, 
    T__14 = 15, T__15 = 16, T__16 = 17, T__17 = 18, T__18 = 19, T__19 = 20, 
    CONCEPT = 21, FUNCTION = 22, NAMESPACE = 23, DESCRIPTION = 24, GENERICIMPL = 25, 
    REQUIRES = 26, FAMILY = 27, LBRACE = 28, RBRACE = 29, VARARGS = 30, 
    REAL = 31, BOOL = 32, NUMBER = 33, STRING = 34, IDENTIFIER = 35, WHITESPACE = 36, 
    COMMENT = 37, LINE_COMMENT = 38, OTHER = 39
  };

  enum {
    RuleTranslationUnit = 0, RuleStmnt = 1, RuleFamilyStmnt = 2, RuleFamilyHeader = 3, 
    RuleFamilyBody = 4, RuleFamilyBodyStmnt = 5, RuleConceptDefinitionStmnt = 6, 
    RuleConceptDefinitionBases = 7, RuleNamespaceStmnt = 8, RuleFamilyFunctionStmnt = 9, 
    RuleFunctionStmnt = 10, RuleFunctionBody = 11, RuleFunctionBodyStmnt = 12, 
    RuleParameterList = 13, RuleParameter = 14, RuleExpression = 15, RulePlaceholderOrQualifiedId = 16, 
    RulePlaceholder = 17, RuleTypename = 18, RuleQualifiedIdentifier = 19, 
    RuleLiteral = 20
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
  class FamilyStmntContext;
  class FamilyHeaderContext;
  class FamilyBodyContext;
  class FamilyBodyStmntContext;
  class ConceptDefinitionStmntContext;
  class ConceptDefinitionBasesContext;
  class NamespaceStmntContext;
  class FamilyFunctionStmntContext;
  class FunctionStmntContext;
  class FunctionBodyContext;
  class FunctionBodyStmntContext;
  class ParameterListContext;
  class ParameterContext;
  class ExpressionContext;
  class PlaceholderOrQualifiedIdContext;
  class PlaceholderContext;
  class TypenameContext;
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
    FamilyStmntContext *familyStmnt();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  StmntContext* stmnt();

  class  FamilyStmntContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *name = nullptr;
    FamilyStmntContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *FAMILY();
    ConceptDefinitionBasesContext *conceptDefinitionBases();
    FamilyBodyContext *familyBody();
    antlr4::tree::TerminalNode *IDENTIFIER();
    std::vector<FamilyHeaderContext *> familyHeader();
    FamilyHeaderContext* familyHeader(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  FamilyStmntContext* familyStmnt();

  class  FamilyHeaderContext : public antlr4::ParserRuleContext {
  public:
    CongParser::TypenameContext *type = nullptr;
    FamilyHeaderContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IDENTIFIER();
    TypenameContext *typename_();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  FamilyHeaderContext* familyHeader();

  class  FamilyBodyContext : public antlr4::ParserRuleContext {
  public:
    FamilyBodyContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LBRACE();
    antlr4::tree::TerminalNode *RBRACE();
    std::vector<FamilyBodyStmntContext *> familyBodyStmnt();
    FamilyBodyStmntContext* familyBodyStmnt(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  FamilyBodyContext* familyBody();

  class  FamilyBodyStmntContext : public antlr4::ParserRuleContext {
  public:
    FamilyBodyStmntContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    FamilyFunctionStmntContext *familyFunctionStmnt();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  FamilyBodyStmntContext* familyBodyStmnt();

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

  class  FamilyFunctionStmntContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *name = nullptr;
    CongParser::QualifiedIdentifierContext *type = nullptr;
    FamilyFunctionStmntContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *FUNCTION();
    ParameterListContext *parameterList();
    antlr4::tree::TerminalNode *LBRACE();
    antlr4::tree::TerminalNode *RBRACE();
    antlr4::tree::TerminalNode *IDENTIFIER();
    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);
    QualifiedIdentifierContext *qualifiedIdentifier();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  FamilyFunctionStmntContext* familyFunctionStmnt();

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
    PlaceholderContext *placeholder();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  PlaceholderOrQualifiedIdContext* placeholderOrQualifiedId();

  class  PlaceholderContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *name = nullptr;
    PlaceholderContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IDENTIFIER();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  PlaceholderContext* placeholder();

  class  TypenameContext : public antlr4::ParserRuleContext {
  public:
    TypenameContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    PlaceholderContext *placeholder();
    QualifiedIdentifierContext *qualifiedIdentifier();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  TypenameContext* typename_();

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

