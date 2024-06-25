grammar AstMatcher;

astPatternDescription:
    nodeTypeOr+;

nodeType:
	(IDENTIFIER (AS IDENTIFIER)?)
	('[' nodePropertiesDescriptionOr* ']')?
	('{' nodeTypeOr* '}')?
	SCOL*;

nodePropertiesDescription:
    (IDENTIFIER EQUAL STRING)
    |
	(IDENTIFIER IDENTIFIER '(' STRING ')')
	|
	(IDENTIFIER '{' nodeType* '}')
	;

nodePropertiesDescriptionOr:
	('(' nodePropertiesDescription+ (OR nodePropertiesDescriptionOr)? ')')
	|
	(nodePropertiesDescription+ (OR nodePropertiesDescriptionOr)?);

nodeTypeOr:
	('(' nodeType+ (OR nodeTypeOr)? ')')
	|
	nodeType+ (OR nodeTypeOr)?;

// Lexer rules
OR: ('|' | 'OR' | 'or');
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
