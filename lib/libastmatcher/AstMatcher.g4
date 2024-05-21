grammar AstMatcher;

// Lexer rules
DOLLAR: '$';
CAPTURE: 'capture';
SKIP: 'skip';
AS: 'as';
ARROW: '->';
LPAREN: '(';
RPAREN: ')';
LBRACKET: '[';
RBRACKET: ']';
LBRACE: '{';
RBRACE: '}';
EQUAL: '=';
COMMA: ',';
IDENTIFIER: [a-zA-Z_][a-zA-Z_0-9]*;
STRING: '"' (~["\\] | '\\' .)* '"';
WHITESPACE: [ \t\r\n] -> skip;

// Parser rules

astDescription:
    (captureStmt | skipStmt)
    (LBRACKET astPropertyDescription* RBRACKET)?
    (LBRACE matchList RBRACE)?;

captureStmt:
    CAPTURE IDENTIFIER (AS IDENTIFIER)? (ARROW IDENTIFIER)?;

skipStmt:
    SKIP IDENTIFIER;

astPropertyDescription:
    STRING EQUAL STRING
    | STRING funcCall;

funcCall:
    IDENTIFIER LPAREN (DOLLAR (COMMA STRING)?)? RPAREN;

matchList:
    (matchStmt (COMMA matchStmt)*)?;

matchStmt:
    captureStmt
    | skipStmt
    | nestedCapture;

nestedCapture:
    IDENTIFIER LBRACE matchList RBRACE;
