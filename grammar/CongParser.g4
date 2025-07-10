// File: CongParser.g4
parser grammar CongParser;

options {
    tokenVocab = CongLexer;
}

@header {
#include "CongLexer.h"
}

translationUnit
    : stmnt* EOF
    ;

stmnt
    : conceptDefinitionStmnt
    | namespaceStmnt
    | functionStmnt
    ;

conceptDefinitionStmnt
    : CONCEPT name=IDENTIFIER (LPAREN DESCRIPTION COLON desc=STRING RPAREN)? conceptDefinitionBases? SEMI
    ;

conceptDefinitionBases
    : COLON qualifiedIdentifier (AMP qualifiedIdentifier)*
    ;

namespaceStmnt
    : NAMESPACE name=IDENTIFIER LBRACE stmnt* RBRACE
    ;

functionStmnt
    : FUNCTION name=IDENTIFIER parameterList ARROW type=qualifiedIdentifier functionBody
    ;

functionBody
    : LBRACE functionBodyStmnt* RBRACE
    ;

functionBodyStmnt
    : DESCRIPTION LBRACE literal RBRACE
        # functionDescription
    | GENERICIMPL (g=genericImplDetails)
        (
          { $g.hasLangArg }?
            LBRACE
            body_native=rawTextContent
            RBRACE
        |
            LBRACE body_expr=expression RBRACE
        )
        # functionGenericImpl
    | REQUIRES (details=requirementDetails)? LBRACE expression RBRACE # functionExpRequires
    ;

rawTextContent
    : element*
    ;

element
    : LBRACE rawTextContent RBRACE
    | ~(LBRACE | RBRACE)
    ;

parameterList
    : LPAREN (parameter (COMMA parameter)*)? RPAREN
    ;

genericImplDetail returns [bool isLangAttr]
    : TIME COLON expression        { $isLangAttr = false; }
    | SPACE COLON expression       { $isLangAttr = false; }
    | LANG COLON targetLang=STRING { $isLangAttr = true; }
    ;

requirementDetail
    : NAME COLON name=STRING
    | DESCRIPTION COLON desc=STRING
    ;

requirementDetails
    : LPAREN (requirementDetail (COMMA requirementDetail)*)? RPAREN
    ;

genericImplDetails returns [bool hasLangArg]
  :  { $hasLangArg = false; }
     LPAREN (
         first_detail=genericImplDetail { if ($first_detail.isLangAttr) $hasLangArg = true; }
         (COMMA next_detail=genericImplDetail { if ($next_detail.isLangAttr) $hasLangArg = true; } )*
     )? RPAREN
  ;

parameter
    : name=IDENTIFIER COLON type=placeholderOrQualifiedId
    ;

expression
    :
    LPAREN expression RPAREN # parenthesizedExpression
    | left=expression op=(PLUS | MINUS | MUL | DIV | MOD | POW) right=expression # arithmeticExpression
    | left=expression op=(LT | LESS_EQUAL | GT | GREATER_EQUAL | EQUAL | NOT_EQUAL) right=expression # comparisonExpression
    | val=literal # literalExpression
    | cond=expression QUESTION_MARK left=expression COLON right=expression # conditionalExpression
    | QUOTE LPAREN expression RPAREN # quoteExpression
    | EVAL LPAREN expression RPAREN # evalExpression
    | REQUIRES LPAREN STRING RPAREN # requiresCallExpression
    | fun=qualifiedIdentifier LPAREN (expression (COMMA expression)*)? RPAREN # callExpression
    | paramOrConcept=qualifiedIdentifier # parameterOrConceptReferenceExpression
    | LET name=IDENTIFIER ASSIGN value=expression LBRACE body=expressionBlock RBRACE # letExpression
    | OPEN_BINDING # openBindingExpression
    ;

expressionBlock
    : (expression SEMI)* expression
    ;

placeholderOrQualifiedId
    : qualifiedIdentifier
    | placeholder
    ;

placeholder
    : LT name=IDENTIFIER GT
    ;

qualifiedIdentifier: (DOUBLE_COLON)? IDENTIFIER (DOUBLE_COLON IDENTIFIER)*;

literal
    : REAL DYNAMIC_ANNOTATOR?
    | INTEGER DYNAMIC_ANNOTATOR?
    | STRING
    | BOOL DYNAMIC_ANNOTATOR?
    ;