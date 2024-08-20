grammar AstMatcher;

// -------------------------------------------------------
// 		R O O T
// -------------------------------------------------------

astPatternDescription:
    astRoot=nodeTypeSequence
    ;

// -------------------------------------------------------
// 		N O D E    T Y P E
// -------------------------------------------------------

nodeType:
    (IDENTIFIER | ANY)
        (AS IDENTIFIER)?
    ('[' nodePropertySequence ']')?
    ('{' nodeTypeSequence '}')?
    ';'*
    ;

nodeTypeSequence:
    node=nodeType
    |
    '(' nodeTypeSequence ')'
    |
    NOT nodeTypeSequence
	|
	nodeTypeSequence PLUS
	|
	nodeTypeSequence STAR
	|
	nodeTypeSequence QUESTION_MARK
    |
	nodeTypeSequence isor=OR nodeTypeSequence
    |
	nodeTypeSequence nodeTypeSequence
    ;

// -------------------------------------------------------
// 		N O D E    P R O P E R T I E S
// -------------------------------------------------------

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
    nodeProperty
    |
    '(' nodePropertySequence ')'
    |
    NOT nodePropertySequence
    |
	nodePropertySequence isor=OR nodePropertySequence
    |
	nodePropertySequence nodePropertySequence
    ;


// -------------------------------------------------------
// 		L E X E R       R U L E S
// -------------------------------------------------------

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
