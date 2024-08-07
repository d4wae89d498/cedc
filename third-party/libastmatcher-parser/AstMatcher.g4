grammar AstMatcher;

astPatternDescription:
    astRoot=nodeTypeSequence
    ;

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
    nodeType
    |
    '(' nodeTypeSequence ')'
    |
    NOT nodeTypeElement
	|
	nodeTypeElement UNTIL nodeTypeElement?
	|
	nodeTypeElement REPEAT nodeTypeElement?
	|
	nodeTypeElement OPT
    ;

// Lexer rules
BEEING:			'BEEING' | 'beeing';
OPT:			'?' 	| (BEEING? 'OPTIONAL') 	| (BEEING? 'optional');
ANY:			'.' 	| 'ANY' 		| 'any';
REPEAT:			'+' 	| 'REPEAT'		| 'repeat';
UNTIL: 			'*' 	| 'UNTIL' 		| 'until';
EQUAL: 			'='		| 'IS' 			| 'is';
OR: 			'|' 	| 'OR' 			| 'or';
NOT: 			'!' 	| 'NOT' 		| 'not';
AS: 			'=>'  	| 'AS'			| 'as';
IDENTIFIER: 	[a-zA-Z_][a-zA-Z_0-9]*;
STRING: 		'"' (ESC | ~["\\])* '"';
fragment ESC: 	'\\' .;
COMMENT: 		'#' ~[\r\n]* -> skip;
WHITESPACE: 	[ \t\r\n]+ -> skip;
