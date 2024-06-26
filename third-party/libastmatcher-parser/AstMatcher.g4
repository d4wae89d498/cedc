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
    nodePropertyElement (OR? nodePropertyElement)*
    ;

nodePropertyElement:
    nodeProperty
    |
    '(' nodePropertySequence ')'
    |
    NOT nodePropertyElement
    ;

nodeTypeSequence:
    nodeTypeElement (OR? nodeTypeElement)*
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
AND: 'and' -> skip;
