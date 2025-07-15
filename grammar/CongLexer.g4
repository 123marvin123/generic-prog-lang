
lexer grammar CongLexer;

CONCEPT: 'concept';
FUNCTION: 'fun';
NAMESPACE: 'namespace';
LET: 'let';

NAME: 'name';
DESCRIPTION: 'description';
GENERICIMPL: 'generic';
REQUIRES: 'requires';
TIME: 'time';
SPACE: 'space';
LANG: 'lang';

QUOTE: 'quote';
EVAL: 'eval';

LBRACE: '{';
RBRACE: '}';

LPAREN: '(';
RPAREN: ')';
COLON: ':';
QUESTION_MARK: '?';
SEMI: ';';
AMP: '&';
ARROW: '->';
COMMA: ',';
ASSIGN: '=';
EQUAL: '==';
NOT_EQUAL: '!=';
PLUS: '+';
MINUS: '-';
MUL: '*';
DIV: '/';
MOD: '%';
POW: '^';
LT: '<';
LESS_EQUAL: '<=';
GT: '>';
GREATER_EQUAL: '>=';
DOUBLE_COLON: '::';
LAMBDA_ARROW: '=>';

OPEN_BINDING: '_' [1-9][0-9]*;
DYNAMIC_ANNOTATOR: '_d';

REAL
    : '0' '.' [0-9]+
    | [1-9][0-9]* '.' [0-9]+
    ;

BOOL
    : 'true'
    | 'false'
    ;

INTEGER
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