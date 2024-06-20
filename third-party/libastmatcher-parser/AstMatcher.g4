grammar AstMatcher;

astPatternDescription:
    nodeType*;

nodeType:
	(IDENTIFIER (AS IDENTIFIER)?)
	(LBRACKET nodePropertiesDescription* RBRACKET)?
	(LBRACE nodeType* RBRACE)?
	SCOL*;

nodePropertiesDescription:
    (STRING EQUAL STRING)
    |
	(STRING IDENTIFIER LPARENTHESE STRING RPARENTHESE)
	|
	(LBRACE nodeType* RBRACE)
	;

nodePropertiesDescriptionOr:
	nodePropertiesDescription	OR 	 OrExpr;

nodeTypeOr:
	nodeType	OR 	 OrExpr;

// Lexer rules
OR: '|';
AS: 'as';
LPARENTHESE: '(';
RPARENTHESE: ')';
LBRACKET: '[';
RBRACKET: ']';
LBRACE: '{';
RBRACE: '}';
EQUAL: '=';
SCOL: ';';
IDENTIFIER: [a-zA-Z_][a-zA-Z_0-9]*;
STRING: '"' (ESC | ~["\\])* '"';
fragment ESC: '\\' .;
COMMENT: '#' ~[\r\n]* -> skip;
WHITESPACE: [ \t\r\n]+ -> skip;
