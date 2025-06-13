// File: CongLexer.g4
lexer grammar CongLexer;

// All your existing token definitions
CONCEPT: 'concept';
FUNCTION: 'fun';
NAMESPACE: 'namespace';
LET: 'let';

DESCRIPTION: 'description';
GENERICIMPL: 'generic';
REQUIRES: 'requires';
TIME: 'time';
SPACE: 'space';
LANG: 'lang';

LBRACE: '{';
RBRACE: '}';
VARARGS: '...';

// New tokens for literals previously implicit in parser
LPAREN: '(';
RPAREN: ')';
COLON: ':';
SEMI: ';';
AMP: '&';
ARROW: '->';
COMMA: ',';
ASSIGN: '='; // For let expressions
PLUS: '+';
MINUS: '-'; // For arithmetic operator, distinct from negative numbers
MUL: '*';
DIV: '/';
MOD: '%';
LT: '<'; // For placeholders
GT: '>'; // For placeholders
DOUBLE_COLON: '::';


REAL
    : '0' '.' [0-9]+
    | [1-9][0-9]* '.' [0-9]+
    ;

BOOL
    : 'true'
    | 'false'
    ;

NUMBER // This rule already handles negative numbers like -5
    : [1-9][0-9]*
    | '0'
    | '-' [1-9][0-9]*
    | '-0'
    ;

STRING
    : '"' ~["]* '"'
    ;

IDENTIFIER: [a-zA-Z_][a-zA-Z_0-9]*;

WHITESPACE
    : [ \t\n\r]+ -> skip
    ;

COMMENT: '/*' .*? '*/' -> channel(HIDDEN);
LINE_COMMENT: '//' ~[\r\n]* -> channel(HIDDEN);
OTHER: .;