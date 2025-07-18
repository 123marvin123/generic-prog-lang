
#include "CongLexer.h"


// Generated from /Users/haschker/Arbeitsbereich/generic-prog-lang/grammar/CongParser.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"
#include "CongParser.h"



/**
 * This class defines an abstract visitor for a parse tree
 * produced by CongParser.
 */
class  CongParserVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by CongParser.
   */
    virtual std::any visitTranslationUnit(CongParser::TranslationUnitContext *context) = 0;

    virtual std::any visitStmnt(CongParser::StmntContext *context) = 0;

    virtual std::any visitConceptDefinitionStmnt(CongParser::ConceptDefinitionStmntContext *context) = 0;

    virtual std::any visitConceptDefinitionBases(CongParser::ConceptDefinitionBasesContext *context) = 0;

    virtual std::any visitNamespaceStmnt(CongParser::NamespaceStmntContext *context) = 0;

    virtual std::any visitFunctionStmnt(CongParser::FunctionStmntContext *context) = 0;

    virtual std::any visitFunctionBody(CongParser::FunctionBodyContext *context) = 0;

    virtual std::any visitFunctionDescription(CongParser::FunctionDescriptionContext *context) = 0;

    virtual std::any visitFunctionGenericImpl(CongParser::FunctionGenericImplContext *context) = 0;

    virtual std::any visitFunctionExpRequires(CongParser::FunctionExpRequiresContext *context) = 0;

    virtual std::any visitRawTextContent(CongParser::RawTextContentContext *context) = 0;

    virtual std::any visitElement(CongParser::ElementContext *context) = 0;

    virtual std::any visitParameterList(CongParser::ParameterListContext *context) = 0;

    virtual std::any visitGenericImplDetail(CongParser::GenericImplDetailContext *context) = 0;

    virtual std::any visitRequirementDetail(CongParser::RequirementDetailContext *context) = 0;

    virtual std::any visitRequirementDetails(CongParser::RequirementDetailsContext *context) = 0;

    virtual std::any visitGenericImplDetails(CongParser::GenericImplDetailsContext *context) = 0;

    virtual std::any visitParameter(CongParser::ParameterContext *context) = 0;

    virtual std::any visitParameterOrConceptReferenceExpression(CongParser::ParameterOrConceptReferenceExpressionContext *context) = 0;

    virtual std::any visitLambdaExpression(CongParser::LambdaExpressionContext *context) = 0;

    virtual std::any visitOpenBindingExpression(CongParser::OpenBindingExpressionContext *context) = 0;

    virtual std::any visitConditionalExpression(CongParser::ConditionalExpressionContext *context) = 0;

    virtual std::any visitEvalExpression(CongParser::EvalExpressionContext *context) = 0;

    virtual std::any visitComparisonExpression(CongParser::ComparisonExpressionContext *context) = 0;

    virtual std::any visitArithmeticExpression(CongParser::ArithmeticExpressionContext *context) = 0;

    virtual std::any visitParenthesizedExpression(CongParser::ParenthesizedExpressionContext *context) = 0;

    virtual std::any visitRequiresCallExpression(CongParser::RequiresCallExpressionContext *context) = 0;

    virtual std::any visitCallExpression(CongParser::CallExpressionContext *context) = 0;

    virtual std::any visitLetExpression(CongParser::LetExpressionContext *context) = 0;

    virtual std::any visitQuoteExpression(CongParser::QuoteExpressionContext *context) = 0;

    virtual std::any visitLiteralExpression(CongParser::LiteralExpressionContext *context) = 0;

    virtual std::any visitLetBinding(CongParser::LetBindingContext *context) = 0;

    virtual std::any visitExpressionBlock(CongParser::ExpressionBlockContext *context) = 0;

    virtual std::any visitPlaceholderOrQualifiedId(CongParser::PlaceholderOrQualifiedIdContext *context) = 0;

    virtual std::any visitPlaceholder(CongParser::PlaceholderContext *context) = 0;

    virtual std::any visitQualifiedIdentifier(CongParser::QualifiedIdentifierContext *context) = 0;

    virtual std::any visitLiteral(CongParser::LiteralContext *context) = 0;


};

