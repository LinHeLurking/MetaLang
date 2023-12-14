lexer grammar CommonLexRules;

// identifiers
ID: [a-zA-Z][0-9a-zA-Z]*;

// literals
NUM_LITERAL: [0-9]+;

// operators

MUL: '*';
DIV: '/';
ADD: '+';
SUB: '-';
ASSIGN: '=';

//
SEMICOLON: ';' ;
LEFT_PAREN: '(' ;
RIGHT_PAREN: ')' ;

// whitespaces & EOL
NEWLINE: '\r'? '\n';
WS: [ \t]+ -> skip;
