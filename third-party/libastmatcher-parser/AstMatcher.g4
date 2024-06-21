grammar AstMatcher;

astPatternDescription:
    nodeTypeOr*;

nodeType:
	(IDENTIFIER (AS IDENTIFIER)?)
	(LBRACKET nodePropertiesDescriptionOr* RBRACKET)?
	(LBRACE nodeTypeOr* RBRACE)?
	SCOL*;

nodePropertiesDescription:
    (IDENTIFIER EQUAL STRING)
    |
	(IDENTIFIER IDENTIFIER LPARENTHESE STRING RPARENTHESE)
	|
	(IDENTIFIER LBRACE nodeType* RBRACE)
	;

nodePropertiesDescriptionOr:
	nodePropertiesDescription	(OR 	nodePropertiesDescriptionOr)?;

nodeTypeOr:
	nodeType	(OR 	 nodeTypeOr)?;

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
