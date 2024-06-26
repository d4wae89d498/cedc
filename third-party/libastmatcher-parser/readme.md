# AST Node Matcher DSL Specification

## Overview

This document specifies the ANTLR grammar for the AST Node Matcher DSL. This DSL allows users to define patterns for matching nodes in an Abstract Syntax Tree (AST). Each node contains properties and children, where properties may be strings or other AST nodes. The goal of this project is to provide a flexible and expressive way to define and match complex patterns within an AST.

## Lexer Rules

The lexer rules define the tokens used in the DSL:

- **AS**: The keyword `as`.
- **EQUAL**: Represents the `=` character.
- **OR**: Represents the `|`, `OR`, or `or` characters.
- **NOT**: Represents the `!`, `NOT`, or `not` characters.
- **IDENTIFIER**: Matches alphanumeric identifiers (letters, digits, and underscores) starting with a letter.
- **STRING**: Matches double-quoted string literals.
- **ESC**: Matches escape sequences within strings.
- **COMMENT**: Skips comments starting with `#`.
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

The `nodeType` rule defines a node type statement, which may optionally specify an alias using the `as` keyword. It may also include property descriptions, nested node types, and support for the OR operator to provide alternatives.

```antlr
nodeType:
    IDENTIFIER
        (AS IDENTIFIER)?
    ('[' nodePropertySequence ']')?
    ('{' nodeTypeSequence '}')?
    ';'*
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

The `nodePropertySequence` rule describes sequences of node properties. It supports nested properties and alternatives using the OR operator.

```antlr
nodePropertySequence:
    elem=nodePropertyElement
    |
    nodePropertySequence isor=OR nodePropertySequence
    |
    nodePropertySequence nodePropertySequence
    ;
```

### Node Property Element: `nodePropertyElement`

The `nodePropertyElement` rule describes individual node properties or nested property sequences.

```antlr
nodePropertyElement:
    nodeProperty
    |
    '(' nodePropertySequence ')'
    |
    NOT nodePropertyElement
    ;
```

### Node Type Sequence: `nodeTypeSequence`

The `nodeTypeSequence` rule describes sequences of node types. It supports nested types and alternatives using the OR operator.

```antlr
nodeTypeSequence:
    elem=nodeTypeElement
    |
    nodeTypeSequence isor=OR nodeTypeSequence
    |
    nodeTypeSequence nodeTypeSequence
    ;
```

### Node Type Element: `nodeTypeElement`

The `nodeTypeElement` rule describes individual node types or nested type sequences.

```antlr
nodeTypeElement:
    nodeType
    |
    '(' nodeTypeSequence ')'
    |
    NOT nodeTypeElement
    ;
```

## Example

The following is an example of the DSL and how it conforms to the specified grammar:

```plaintext
Symbol["value" = "." | "value" = "!"];
Expr["type"="int"] as number {
    Value["val"="10"] | Value["val"="20"];
};
```

In this example:

- `Symbol["value" = "." | "value" = "!"]` captures the `Symbol` node if its `value` property matches either `.` or `!`.
- `Expr["type"="int"] as number { ... }` captures the `Expr` node if it has a property `type` with the value `int` and assigns it the alias `number`. Inside this node, it matches either `Value["val"="10"]` or `Value["val"="20"]`.

The structure showcases how to define node types with properties, nested node types, and alternatives, supporting recursive and flexible pattern matching in the AST.
