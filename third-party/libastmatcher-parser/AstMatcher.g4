grammar AstMatcher;

astPatternDescription:
    astRoot=nodeTypeSequence
    ;

nodeType:
    IDENTIFIER
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
    ;

// Lexer rules
EQUAL: '=';
OR: ('|' | 'OR' | 'or');
NOT: ('!' | 'NOT' | 'not');
AS: 'as';
IDENTIFIER: [a-zA-Z_][a-zA-Z_0-9]*;
STRING: '"' (ESC | ~["\\])* '"';
fragment ESC: '\\' .;
COMMENT: '#' ~[\r\n]* -> skip;
WHITESPACE: [ \t\r\n]+ -> skip;
