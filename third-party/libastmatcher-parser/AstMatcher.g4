grammar AstMatcher;

astDescription:
    nodeTypeStmt
    (LBRACKET astPropertyDescription* RBRACKET)?
    (LBRACE matchList RBRACE)?;

nodeTypeStmt:
    IDENTIFIER (AS IDENTIFIER)?;

astPropertyDescription:
    STRING EQUAL STRING
    | STRING funcCall;

funcCall:
    IDENTIFIER LPARENTHESE (DOLLAR (COMMA STRING)?)? RPARENTHESE;

matchList:
    (matchStmt (COMMA matchStmt)*)?;

matchStmt:
    nodeTypeStmt
    | nestedNodeType;

nestedNodeType:
    IDENTIFIER LBRACE matchList RBRACE;

// Lexer rules
DOLLAR: '$';
AS: 'as';
LPARENTHESE: '(';
RPARENTHESE: ')';
LBRACKET: '[';
RBRACKET: ']';
LBRACE: '{';
RBRACE: '}';
EQUAL: '=';
COMMA: ',';
IDENTIFIER: [a-zA-Z_][a-zA-Z_0-9]*;
STRING: '"' (ESC | ~["\\])* '"';
fragment ESC: '\\' .;
COMMENT: '#' ~[\r\n]* -> skip;
WHITESPACE: [ \t\r\n]+ -> skip;
