grammar Cong;

translationUnit
    : stmnt* EOF
    ;

stmnt
    : conceptDefinitionStmnt
    | namespaceStmnt
    | functionStmnt
    | familyStmnt
    ;

familyStmnt
    : FAMILY name=IDENTIFIER ('(' familyHeader (',' familyHeader)* ')')? conceptDefinitionBases familyBody
    ;

familyHeader
    : IDENTIFIER ':' type=typename
    ;

familyBody
    : LBRACE familyBodyStmnt* RBRACE
    ;

familyBodyStmnt
    : familyFunctionStmnt
    ;

conceptDefinitionStmnt
    : CONCEPT name=IDENTIFIER ('(' 'description' ':' desc=STRING ')')? conceptDefinitionBases?';'
    ;

conceptDefinitionBases
    : ':' qualifiedIdentifier ('&' qualifiedIdentifier)*
    ;

namespaceStmnt
    : NAMESPACE name=IDENTIFIER LBRACE stmnt* RBRACE
    ;

// in the body of the function, we should also allow statements (e.g. changing the state)
familyFunctionStmnt
    : FUNCTION name=IDENTIFIER parameterList ('->' type=qualifiedIdentifier)? LBRACE expression+ RBRACE
    ;

functionStmnt
    : FUNCTION name=IDENTIFIER parameterList '->' type=qualifiedIdentifier functionBody
    ;

functionBody
    : LBRACE functionBodyStmnt* RBRACE
    ;

functionBodyStmnt
    : DESCRIPTION LBRACE literal RBRACE # functionDescription
    | GENERICIMPL LBRACE expression RBRACE # functionGenericImpl
    | REQUIRES LBRACE expression RBRACE # functionExpRequires
    ;

parameterList
    : '(' (parameter (',' parameter)*)? ')'
    ;

parameter
    : name=IDENTIFIER ':' type=placeholderOrQualifiedId
    ;

expression
    : left=expression op=('+' | '-' | '*' | '/' | '%') right=expression # arithmeticExpression
    | val=literal # literalExpression
    | fun=qualifiedIdentifier '(' (expression (',' expression)*)? ')' # callExpression
    | param=IDENTIFIER # parameterReferenceExpression
    ;

placeholderOrQualifiedId
    : qualifiedIdentifier
    | placeholder
    ;

placeholder
    : '<' name=IDENTIFIER '>'
    ;

typename
    : 'String'
    | 'Number'
    | 'Real'
    | 'Bool'
    | 'Void'
    | placeholder
    | qualifiedIdentifier
    ;

// Allows for a qualified identifier, e.g., ::Math::Family
qualifiedIdentifier: ('::')? IDENTIFIER ('::' IDENTIFIER)*;

literal
    : REAL
    | NUMBER
    | STRING
    | BOOL
    ;

CONCEPT: 'concept';
FUNCTION: 'fun';
NAMESPACE: 'namespace';

DESCRIPTION: 'description';
GENERICIMPL: 'generic';
REQUIRES: 'requires';
FAMILY: 'family';

LBRACE: '{';
RBRACE: '}';
VARARGS: '...';

REAL
    : '0' '.' [0-9]+
    | [1-9][0-9]* '.' [0-9]+
    ;

BOOL
    : 'true'
    | 'false'
    ;

NUMBER
    : [1-9][0-9]*
    | '0'
    | '-' [1-9][0-9]*
    | '-0'
    ;

STRING
    : '"' ~["]* '"'
    ;

IDENTIFIER: [a-zA-Z_] [a-zA-Z_0-9]*;

WHITESPACE
    : [ \t\n\r]+ -> skip
    ;


COMMENT: '/*' .*? '*/' -> channel(HIDDEN);

LINE_COMMENT: '//' ~[\r\n]* -> channel(HIDDEN);

OTHER: .;