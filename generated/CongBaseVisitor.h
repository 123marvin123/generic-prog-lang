
// Generated from /Users/haschker/Arbeitsbereich/generic-prog-lang/grammar/Cong.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"
#include "CongVisitor.h"


/**
 * This class provides an empty implementation of CongVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  CongBaseVisitor : public CongVisitor {
public:

  virtual std::any visitTranslationUnit(CongParser::TranslationUnitContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStmnt(CongParser::StmntContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFamilyStmnt(CongParser::FamilyStmntContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFamilyHeader(CongParser::FamilyHeaderContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFamilyBody(CongParser::FamilyBodyContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFamilyBodyStmnt(CongParser::FamilyBodyStmntContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitConceptDefinitionStmnt(CongParser::ConceptDefinitionStmntContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitConceptDefinitionBases(CongParser::ConceptDefinitionBasesContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNamespaceStmnt(CongParser::NamespaceStmntContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFunctionStmnt(CongParser::FunctionStmntContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFunctionBody(CongParser::FunctionBodyContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFunctionDescription(CongParser::FunctionDescriptionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFunctionGenericImpl(CongParser::FunctionGenericImplContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFunctionExpRequires(CongParser::FunctionExpRequiresContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitParameterList(CongParser::ParameterListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitParameter(CongParser::ParameterContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCallExpression(CongParser::CallExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitArithmeticExpression(CongParser::ArithmeticExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLiteralExpression(CongParser::LiteralExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitParameterReferenceExpression(CongParser::ParameterReferenceExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPlaceholderOrQualifiedId(CongParser::PlaceholderOrQualifiedIdContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitConceptPlaceholder(CongParser::ConceptPlaceholderContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTypename(CongParser::TypenameContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitQualifiedIdentifier(CongParser::QualifiedIdentifierContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLiteral(CongParser::LiteralContext *ctx) override {
    return visitChildren(ctx);
  }


};

