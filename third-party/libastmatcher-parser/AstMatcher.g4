grammar AstMatcher;

// Lexer rules
DOLLAR: '$';
CAPTURE: 'capture';
SKIP_NODE: 'skip';
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
COMMENT: '#' ~[\r\n]* -> skip;

// Parser rules

pattern:
    astDescription* EOF; // The program can contain multiple astDescription statements

astDescription:
    (captureStmt | skipStmt)
    (LBRACKET astPropertyDescription* RBRACKET)?
    (LBRACE matchList RBRACE)?;

captureStmt:
    CAPTURE IDENTIFIER (AS IDENTIFIER)? (ARROW IDENTIFIER)?;

skipStmt:
    SKIP_NODE IDENTIFIER;

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
