
#include "CongLexer.h"


// Generated from /Users/haschker/Arbeitsbereich/generic-prog-lang/grammar/CongParser.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"




class  CongParser : public antlr4::Parser {
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

  enum {
    RuleTranslationUnit = 0, RuleStmnt = 1, RuleConceptDefinitionStmnt = 2, 
    RuleConceptDefinitionBases = 3, RuleNamespaceStmnt = 4, RuleFunctionStmnt = 5, 
    RuleFunctionBody = 6, RuleFunctionBodyStmnt = 7, RuleRawTextContent = 8, 
    RuleElement = 9, RuleParameterList = 10, RuleGenericImplDetail = 11, 
    RuleRequirementDetail = 12, RuleRequirementDetails = 13, RuleGenericImplDetails = 14, 
    RuleParameter = 15, RuleExpression = 16, RuleLetBinding = 17, RuleExpressionBlock = 18, 
    RulePlaceholderOrQualifiedId = 19, RulePlaceholder = 20, RuleQualifiedIdentifier = 21, 
    RuleLiteral = 22
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
  class RawTextContentContext;
  class ElementContext;
  class ParameterListContext;
  class GenericImplDetailContext;
  class RequirementDetailContext;
  class RequirementDetailsContext;
  class GenericImplDetailsContext;
  class ParameterContext;
  class ExpressionContext;
  class LetBindingContext;
  class ExpressionBlockContext;
  class PlaceholderOrQualifiedIdContext;
  class PlaceholderContext;
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
    antlr4::tree::TerminalNode *SEMI();
    antlr4::tree::TerminalNode *IDENTIFIER();
    antlr4::tree::TerminalNode *LPAREN();
    antlr4::tree::TerminalNode *DESCRIPTION();
    antlr4::tree::TerminalNode *COLON();
    antlr4::tree::TerminalNode *RPAREN();
    ConceptDefinitionBasesContext *conceptDefinitionBases();
    antlr4::tree::TerminalNode *STRING();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ConceptDefinitionStmntContext* conceptDefinitionStmnt();

  class  ConceptDefinitionBasesContext : public antlr4::ParserRuleContext {
  public:
    ConceptDefinitionBasesContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *COLON();
    std::vector<QualifiedIdentifierContext *> qualifiedIdentifier();
    QualifiedIdentifierContext* qualifiedIdentifier(size_t i);
    std::vector<antlr4::tree::TerminalNode *> AMP();
    antlr4::tree::TerminalNode* AMP(size_t i);


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
    antlr4::tree::TerminalNode *ARROW();
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

    CongParser::GenericImplDetailsContext *g = nullptr;
    CongParser::RawTextContentContext *body_native = nullptr;
    CongParser::ExpressionContext *body_expr = nullptr;
    antlr4::tree::TerminalNode *GENERICIMPL();
    antlr4::tree::TerminalNode *LBRACE();
    antlr4::tree::TerminalNode *RBRACE();
    GenericImplDetailsContext *genericImplDetails();
    RawTextContentContext *rawTextContent();
    ExpressionContext *expression();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  FunctionExpRequiresContext : public FunctionBodyStmntContext {
  public:
    FunctionExpRequiresContext(FunctionBodyStmntContext *ctx);

    CongParser::RequirementDetailsContext *details = nullptr;
    antlr4::tree::TerminalNode *REQUIRES();
    antlr4::tree::TerminalNode *LBRACE();
    ExpressionContext *expression();
    antlr4::tree::TerminalNode *RBRACE();
    RequirementDetailsContext *requirementDetails();

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

  class  RawTextContentContext : public antlr4::ParserRuleContext {
  public:
    RawTextContentContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ElementContext *> element();
    ElementContext* element(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  RawTextContentContext* rawTextContent();

  class  ElementContext : public antlr4::ParserRuleContext {
  public:
    ElementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LBRACE();
    RawTextContentContext *rawTextContent();
    antlr4::tree::TerminalNode *RBRACE();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ElementContext* element();

  class  ParameterListContext : public antlr4::ParserRuleContext {
  public:
    ParameterListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LPAREN();
    antlr4::tree::TerminalNode *RPAREN();
    std::vector<ParameterContext *> parameter();
    ParameterContext* parameter(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ParameterListContext* parameterList();

  class  GenericImplDetailContext : public antlr4::ParserRuleContext {
  public:
    bool isLangAttr;
    antlr4::Token *targetLang = nullptr;
    GenericImplDetailContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *TIME();
    antlr4::tree::TerminalNode *COLON();
    ExpressionContext *expression();
    antlr4::tree::TerminalNode *SPACE();
    antlr4::tree::TerminalNode *LANG();
    antlr4::tree::TerminalNode *STRING();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  GenericImplDetailContext* genericImplDetail();

  class  RequirementDetailContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *name = nullptr;
    antlr4::Token *desc = nullptr;
    RequirementDetailContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *NAME();
    antlr4::tree::TerminalNode *COLON();
    antlr4::tree::TerminalNode *STRING();
    antlr4::tree::TerminalNode *DESCRIPTION();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  RequirementDetailContext* requirementDetail();

  class  RequirementDetailsContext : public antlr4::ParserRuleContext {
  public:
    RequirementDetailsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LPAREN();
    antlr4::tree::TerminalNode *RPAREN();
    std::vector<RequirementDetailContext *> requirementDetail();
    RequirementDetailContext* requirementDetail(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  RequirementDetailsContext* requirementDetails();

  class  GenericImplDetailsContext : public antlr4::ParserRuleContext {
  public:
    bool hasLangArg;
    CongParser::GenericImplDetailContext *first_detail = nullptr;
    CongParser::GenericImplDetailContext *next_detail = nullptr;
    GenericImplDetailsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LPAREN();
    antlr4::tree::TerminalNode *RPAREN();
    std::vector<GenericImplDetailContext *> genericImplDetail();
    GenericImplDetailContext* genericImplDetail(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  GenericImplDetailsContext* genericImplDetails();

  class  ParameterContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *name = nullptr;
    CongParser::PlaceholderOrQualifiedIdContext *type = nullptr;
    ParameterContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *COLON();
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

  class  ParameterOrConceptReferenceExpressionContext : public ExpressionContext {
  public:
    ParameterOrConceptReferenceExpressionContext(ExpressionContext *ctx);

    CongParser::QualifiedIdentifierContext *paramOrConcept = nullptr;
    QualifiedIdentifierContext *qualifiedIdentifier();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  LambdaExpressionContext : public ExpressionContext {
  public:
    LambdaExpressionContext(ExpressionContext *ctx);

    CongParser::ExpressionContext *body = nullptr;
    ParameterListContext *parameterList();
    antlr4::tree::TerminalNode *LAMBDA_ARROW();
    antlr4::tree::TerminalNode *LBRACE();
    antlr4::tree::TerminalNode *RBRACE();
    ExpressionContext *expression();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  OpenBindingExpressionContext : public ExpressionContext {
  public:
    OpenBindingExpressionContext(ExpressionContext *ctx);

    antlr4::tree::TerminalNode *OPEN_BINDING();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ConditionalExpressionContext : public ExpressionContext {
  public:
    ConditionalExpressionContext(ExpressionContext *ctx);

    CongParser::ExpressionContext *cond = nullptr;
    CongParser::ExpressionContext *left = nullptr;
    CongParser::ExpressionContext *right = nullptr;
    antlr4::tree::TerminalNode *QUESTION_MARK();
    antlr4::tree::TerminalNode *COLON();
    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  EvalExpressionContext : public ExpressionContext {
  public:
    EvalExpressionContext(ExpressionContext *ctx);

    antlr4::tree::TerminalNode *EVAL();
    antlr4::tree::TerminalNode *LPAREN();
    ExpressionContext *expression();
    antlr4::tree::TerminalNode *RPAREN();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ComparisonExpressionContext : public ExpressionContext {
  public:
    ComparisonExpressionContext(ExpressionContext *ctx);

    CongParser::ExpressionContext *left = nullptr;
    antlr4::Token *op = nullptr;
    CongParser::ExpressionContext *right = nullptr;
    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);
    antlr4::tree::TerminalNode *LT();
    antlr4::tree::TerminalNode *LESS_EQUAL();
    antlr4::tree::TerminalNode *GT();
    antlr4::tree::TerminalNode *GREATER_EQUAL();
    antlr4::tree::TerminalNode *EQUAL();
    antlr4::tree::TerminalNode *NOT_EQUAL();

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
    antlr4::tree::TerminalNode *PLUS();
    antlr4::tree::TerminalNode *MINUS();
    antlr4::tree::TerminalNode *MUL();
    antlr4::tree::TerminalNode *DIV();
    antlr4::tree::TerminalNode *MOD();
    antlr4::tree::TerminalNode *POW();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ParenthesizedExpressionContext : public ExpressionContext {
  public:
    ParenthesizedExpressionContext(ExpressionContext *ctx);

    antlr4::tree::TerminalNode *LPAREN();
    ExpressionContext *expression();
    antlr4::tree::TerminalNode *RPAREN();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  RequiresCallExpressionContext : public ExpressionContext {
  public:
    RequiresCallExpressionContext(ExpressionContext *ctx);

    antlr4::tree::TerminalNode *REQUIRES();
    antlr4::tree::TerminalNode *LPAREN();
    antlr4::tree::TerminalNode *STRING();
    antlr4::tree::TerminalNode *RPAREN();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  CallExpressionContext : public ExpressionContext {
  public:
    CallExpressionContext(ExpressionContext *ctx);

    CongParser::QualifiedIdentifierContext *fun = nullptr;
    antlr4::tree::TerminalNode *LPAREN();
    antlr4::tree::TerminalNode *RPAREN();
    QualifiedIdentifierContext *qualifiedIdentifier();
    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  LetExpressionContext : public ExpressionContext {
  public:
    LetExpressionContext(ExpressionContext *ctx);

    CongParser::ExpressionBlockContext *body = nullptr;
    antlr4::tree::TerminalNode *LET();
    antlr4::tree::TerminalNode *LBRACE();
    antlr4::tree::TerminalNode *RBRACE();
    ExpressionBlockContext *expressionBlock();
    std::vector<LetBindingContext *> letBinding();
    LetBindingContext* letBinding(size_t i);

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  QuoteExpressionContext : public ExpressionContext {
  public:
    QuoteExpressionContext(ExpressionContext *ctx);

    antlr4::tree::TerminalNode *QUOTE();
    antlr4::tree::TerminalNode *LPAREN();
    ExpressionContext *expression();
    antlr4::tree::TerminalNode *RPAREN();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  LiteralExpressionContext : public ExpressionContext {
  public:
    LiteralExpressionContext(ExpressionContext *ctx);

    CongParser::LiteralContext *val = nullptr;
    LiteralContext *literal();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  ExpressionContext* expression();
  ExpressionContext* expression(int precedence);
  class  LetBindingContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *name = nullptr;
    CongParser::ExpressionContext *value = nullptr;
    LetBindingContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ASSIGN();
    antlr4::tree::TerminalNode *IDENTIFIER();
    ExpressionContext *expression();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  LetBindingContext* letBinding();

  class  ExpressionBlockContext : public antlr4::ParserRuleContext {
  public:
    ExpressionBlockContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);
    std::vector<antlr4::tree::TerminalNode *> SEMI();
    antlr4::tree::TerminalNode* SEMI(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ExpressionBlockContext* expressionBlock();

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
    antlr4::tree::TerminalNode *LT();
    antlr4::tree::TerminalNode *GT();
    antlr4::tree::TerminalNode *IDENTIFIER();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  PlaceholderContext* placeholder();

  class  QualifiedIdentifierContext : public antlr4::ParserRuleContext {
  public:
    QualifiedIdentifierContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> IDENTIFIER();
    antlr4::tree::TerminalNode* IDENTIFIER(size_t i);
    std::vector<antlr4::tree::TerminalNode *> DOUBLE_COLON();
    antlr4::tree::TerminalNode* DOUBLE_COLON(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  QualifiedIdentifierContext* qualifiedIdentifier();

  class  LiteralContext : public antlr4::ParserRuleContext {
  public:
    LiteralContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *REAL();
    antlr4::tree::TerminalNode *DYNAMIC_ANNOTATOR();
    antlr4::tree::TerminalNode *INTEGER();
    antlr4::tree::TerminalNode *STRING();
    antlr4::tree::TerminalNode *BOOL();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  LiteralContext* literal();


  bool sempred(antlr4::RuleContext *_localctx, size_t ruleIndex, size_t predicateIndex) override;

  bool functionBodyStmntSempred(FunctionBodyStmntContext *_localctx, size_t predicateIndex);
  bool expressionSempred(ExpressionContext *_localctx, size_t predicateIndex);

  // By default the static state used to implement the parser is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:
};

