grammar AstMatcher;

astPatternDescription:
    astRoot=nodeTypeSequence
    ;

// Should as be on nodeTypeElement instead ?
nodeType:
    (IDENTIFIER | ANY)
        (AS IDENTIFIER)?
    ('[' nodePropertySequence ']')?
    ('{' nodeTypeSequence '}')?
    ';'*
    ;

nodeProperty:
    STRING EQUAL STRING
    |
    IDENTIFIER EQUAL STRING
    |
    IDENTIFIER IDENTIFIER '(' STRING ')'
    |
    IDENTIFIER '{' nodeTypeSequence '}'
    ;

nodePropertySequence:
    elem=nodePropertyElement
    |
	nodePropertySequence isor=OR nodePropertySequence
    |
	nodePropertySequence nodePropertySequence
    ;

nodePropertyElement:
    nodeProperty
    |
    '(' nodePropertySequence ')'
    |
    NOT nodePropertyElement
    ;

nodeTypeSequence:
    elem=nodeTypeElement
    | nodeTypeSequence isor=OR nodeTypeSequence
    | nodeTypeSequence nodeTypeSequence
    ;

nodeTypeElement:
    node=nodeType
    |
    '(' nodeTypeSequence ')'
    |
    NOT nodeTypeElement
	|
	nodeTypeElement PLUS
	|
	nodeTypeElement STAR
	|
	nodeTypeElement QUESTION_MARK
    ;

// Lexer rules
QUESTION_MARK:	'?';
ANY:			'.' 	| 'ANY' 		| 'any' 	| 'Any';
PLUS:			'+';
STAR: 			'*';
EQUAL: 			'='		| 'IS' 			| 'is';
OR: 			'|' 	| 'OR' 			| 'or';
NOT: 			'!' 	| 'NOT' 		| 'not';
AS: 			'=>'  	| 'AS'			| 'as';
IDENTIFIER: 	[a-zA-Z_][a-zA-Z_0-9]*;
STRING: 		'"' (ESC | ~["\\])* '"';
fragment ESC: 	'\\' .;
COMMENT: 		'#' ~[\r\n]* -> skip;
WHITESPACE: 	[ \t\r\n]+ -> skip;
