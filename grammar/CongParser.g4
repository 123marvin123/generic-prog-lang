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
    | GENERICIMPL g=genericImplDetails
        (
          { $g.hasLangArg }?
            LBRACE
            body_native=rawTextContent
            RBRACE
        |
            LBRACE body_expr=expression RBRACE
        )
        # functionGenericImpl
    | REQUIRES (name=IDENTIFIER)? LBRACE expression RBRACE
        # functionExpRequires
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
    : left=expression op=(PLUS | MINUS | MUL | DIV | MOD) right=expression # arithmeticExpression
    | val=literal # literalExpression
    | fun=qualifiedIdentifier LPAREN (expression (COMMA expression)*)? RPAREN # callExpression
    | param=IDENTIFIER # parameterReferenceExpression
    | LET name=IDENTIFIER ASSIGN value=expression LBRACE body=expressionBlock RBRACE # letExpression
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
    : REAL
    | NUMBER
    | STRING
    | BOOL
    ;