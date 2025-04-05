
// Generated from /Users/haschker/Arbeitsbereich/generic-prog-lang/grammar/Cong.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"
#include "CongParser.h"



/**
 * This class defines an abstract visitor for a parse tree
 * produced by CongParser.
 */
class  CongVisitor : public antlr4::tree::AbstractParseTreeVisitor {
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

    virtual std::any visitParameterList(CongParser::ParameterListContext *context) = 0;

    virtual std::any visitParameter(CongParser::ParameterContext *context) = 0;

    virtual std::any visitCallExpression(CongParser::CallExpressionContext *context) = 0;

    virtual std::any visitArithmeticExpression(CongParser::ArithmeticExpressionContext *context) = 0;

    virtual std::any visitLiteralExpression(CongParser::LiteralExpressionContext *context) = 0;

    virtual std::any visitParameterReferenceExpression(CongParser::ParameterReferenceExpressionContext *context) = 0;

    virtual std::any visitPlaceholderOrQualifiedId(CongParser::PlaceholderOrQualifiedIdContext *context) = 0;

    virtual std::any visitPlaceholder(CongParser::PlaceholderContext *context) = 0;

    virtual std::any visitQualifiedIdentifier(CongParser::QualifiedIdentifierContext *context) = 0;

    virtual std::any visitLiteral(CongParser::LiteralContext *context) = 0;


};

