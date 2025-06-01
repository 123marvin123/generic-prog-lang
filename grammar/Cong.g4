grammar Cong;

translationUnit
    : stmnt* EOF
    ;

stmnt
    : conceptDefinitionStmnt
    | namespaceStmnt
    | functionStmnt
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

functionStmnt
    : FUNCTION name=IDENTIFIER parameterList '->' type=qualifiedIdentifier functionBody
    ;

functionBody
    : LBRACE functionBodyStmnt* RBRACE
    ;

functionBodyStmnt
    : DESCRIPTION LBRACE literal RBRACE # functionDescription
    | GENERICIMPL genericImplDetails? LBRACE expression RBRACE # functionGenericImpl
    | REQUIRES (name=IDENTIFIER)? LBRACE expression RBRACE # functionExpRequires
    ;

parameterList
    : '(' (parameter (',' parameter)*)? ')'
    ;

genericImplDetails
    : '(' (genericImplDetail (',' genericImplDetail)*)? ')'
    ;

genericImplDetail
    : TIME ':' expression
    | SPACE ':' expression
    ;


parameter
    : name=IDENTIFIER ':' type=placeholderOrQualifiedId
    ;

expression
    : left=expression op=('+' | '-' | '*' | '/' | '%') right=expression # arithmeticExpression
    | val=literal # literalExpression
    | fun=qualifiedIdentifier '(' (expression (',' expression)*)? ')' # callExpression
    | param=IDENTIFIER # parameterReferenceExpression
    | LET name=IDENTIFIER '=' value=expression LBRACE body=expressionBlock RBRACE # letExpression
    ;

expressionBlock
    : (expression ';')* expression
    ;

placeholderOrQualifiedId
    : qualifiedIdentifier
    | placeholder
    ;

placeholder
    : '<' name=IDENTIFIER '>'
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
LET: 'let';

DESCRIPTION: 'description';
GENERICIMPL: 'generic';
REQUIRES: 'requires';
TIME: 'time';
SPACE: 'space';

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