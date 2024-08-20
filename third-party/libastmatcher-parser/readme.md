# AST Node Matcher DSL Specification

## Overview

This document specifies the ANTLR grammar for the AST Node Matcher DSL. This DSL enables users to define patterns for matching nodes in an Abstract Syntax Tree (AST). Each node contains properties and children, where properties may be strings or other AST nodes. The goal of this project is to provide a flexible and expressive way to define and match complex patterns within an AST.

## Lexer Rules

The lexer rules define the tokens used in the DSL:

- **QUESTION_MARK**: Represents the `?` character, used to indicate optional elements.
- **ANY**: Represents the `.` character or the keywords `ANY`, `any`, `Any`, used as a wildcard.
- **PLUS**: Represents the `+` character, indicating one or more occurrences.
- **STAR**: Represents the `*` character, indicating zero or more occurrences.
- **EQUAL**: Represents the `=`, `IS`, or `is` characters, used for assignments.
- **OR**: Represents the `|`, `OR`, or `or` characters, used for alternatives.
- **NOT**: Represents the `!`, `NOT`, or `not` characters, used for negations.
- **AS**: Represents the `=>`, `AS`, or `as` characters, used for aliasing.
- **IDENTIFIER**: Matches alphanumeric identifiers (letters, digits, and underscores) starting with a letter.
- **STRING**: Matches double-quoted string literals.
- **ESC**: Matches escape sequences within strings.
- **COMMENT**: Skips comments starting with `#`, `//`, or enclosed in `/* */`.
- **WHITESPACE**: Skips whitespace characters (space, tab, newline).

## Grammar Rules

The grammar rules define the structure and hierarchy of the DSL.

### Root Rule: `astPatternDescription`

The `astPatternDescription` rule is the entry point for parsing the DSL. It describes the list of node types.

```antlr
astPatternDescription:
    astRoot=nodeTypeSequence
    ;
```

### Node Type: `nodeType`

The `nodeType` rule defines a node type statement, which may optionally specify an alias using the `as` keyword. It may also include property descriptions, nested node types, and support for various modifiers like `OR`, `NOT`, `PLUS`, `STAR`, and `QUESTION_MARK`.

```antlr
nodeType:
    (IDENTIFIER | ANY)
        (AS IDENTIFIER)?
    ('[' nodePropertySequence ']')?
    ('{' nodeTypeSequence '}')?
    ';'*
    ;
```

### Node Type Sequence: `nodeTypeSequence`

The `nodeTypeSequence` rule describes sequences of node types. It supports nested types and alternatives using the `OR` operator, negations with `NOT`, repetitions with `PLUS` and `STAR`, and optional elements with `QUESTION_MARK`.

```antlr
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
```

### Node Property: `nodeProperty`

The `nodeProperty` rule describes properties of a node, which can be either a string assignment, a function call, or nested node types.

```antlr
nodeProperty:
    STRING EQUAL STRING
    |
    IDENTIFIER EQUAL STRING
    |
    IDENTIFIER IDENTIFIER '(' STRING ')'
    |
    IDENTIFIER '{' nodeTypeSequence '}'
    ;
```

### Node Property Sequence: `nodePropertySequence`

The `nodePropertySequence` rule describes sequences of node properties. It supports nested properties, alternatives using the `OR` operator, and negations with `NOT`.

```antlr
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
```

## Key Behavioral Subtleties

1. **NOT Operator**:
   - The `NOT` operator negates a pattern but does not advance the iterator when matching against the AST. This means it checks the current node but does not move to the next node, allowing subsequent patterns to match from the same position.

2. **OR Operator**:
   - The `OR` operator captures the last successful match when multiple patterns are provided. Unlike standard AST matching, which typically captures the first match, this behavior ensures the most recent successful pattern is retained.

## Example Usage

Here is an example of the DSL and how it conforms to the specified grammar:

```plaintext
Word as id1 [ test = "yoo" ] {
    Word as id1_child1 [ test2 = "yoo2" ]*
    Word as id1_child2 [ test3 = "yoo3" ] {
        Word as id1_child2_grandchild1 [ test4 = "yoo4" ]+
        Word as id1_child2_grandchild2 [ test5 = "yoo5" ]
    }+
}
```

In this example:

- **Word as id1 [ test = "yoo" ]**: Captures the `Word` node with the `test` property set to `"yoo"` and assigns it the alias `id1`.
- **Word as id1_child1 [ test2 = "yoo2" ]***: Matches zero or more `Word` nodes with `test2` property set to `"yoo2"` as children of `id1`, assigning them the alias `id1_child1`.
- **Word as id1_child2 [ test3 = "yoo3" ]**: Captures the `Word` node with `test3` property set to `"yoo3"` and assigns it the alias `id1_child2`.
- **Word as id1_child2_grandchild1 [ test4 = "yoo4" ]+**: Captures one or more `Word` nodes with `test4` property set to `"yoo4"` as grandchildren of `id1_child2`, assigning them the alias `id1_child2_grandchild1`.
- **Word as id1_child2_grandchild2 [ test5 = "yoo5" ]**: Captures the `Word` node with `test5` property set to `"yoo5"` as another grandchild of `id1_child2`, assigning it the alias `id1_child2_grandchild2`.

This example illustrates the flexibility of the DSL in defining complex patterns with nested structures, repetitions, and alternatives.
