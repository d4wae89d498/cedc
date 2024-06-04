grammar AstMatcher;

astPatternDescription:
    nodeType*;

nodeTypeList:
    (nodeType (SCOL)*);

nodeType:
	(IDENTIFIER (AS IDENTIFIER)?)
	(LBRACKET nodePropertiesDescription* RBRACKET)?
	(LBRACE nodeTypeList RBRACE)?;

nodePropertiesDescription:
    STRING EQUAL STRING
    |
	STRING funcCall;

funcCall:
    IDENTIFIER LPARENTHESE (DOLLAR (COMMA STRING)?)? RPARENTHESE;


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
SCOL: ';';
IDENTIFIER: [a-zA-Z_][a-zA-Z_0-9]*;
STRING: '"' (ESC | ~["\\])* '"';
fragment ESC: '\\' .;
COMMENT: '#' ~[\r\n]* -> skip;
WHITESPACE: [ \t\r\n]+ -> skip;
