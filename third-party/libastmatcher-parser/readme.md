# AST Node Matcher DSL Specification

## Overview

This document specifies the ANTLR grammar for the AST Node Matcher DSL. This DSL allows users to define patterns for matching nodes in an Abstract Syntax Tree (AST). Each node contains properties and children, where properties may be strings or other AST nodes.

## Lexer Rules

The lexer rules define the tokens used in the DSL:

- **AS**: The keyword `as`.
- **LPARENTHESE**: Represents the `(` character.
- **RPARENTHESE**: Represents the `)` character.
- **LBRACKET**: Represents the `[` character.
- **RBRACKET**: Represents the `]` character.
- **LBRACE**: Represents the `{` character.
- **RBRACE**: Represents the `}` character.
- **EQUAL**: Represents the `=` character.
- **COMMA**: Represents the `,` character.
- **SCOL**: Represents the `;` character.
- **IDENTIFIER**: Matches alphanumeric identifiers (letters, digits, and underscores) starting with a letter.
- **STRING**: Matches double-quoted string literals.
- **COMMENT**: Skips comments starting with `#`.
- **WHITESPACE**: Skips whitespace characters (space, tab, newline).

## Grammar Rules

The grammar rules define the structure and hierarchy of the DSL.

### Root Rule: `astPatternDescription`

The `astPatternDescription` rule is the entry point for parsing the DSL. It describes the list of node types.

```antlr
astPatternDescription:
    nodeType*;
```

### Node Type: `nodeType`

The `nodeType` rule defines a node type statement, which may optionally specify an alias using the `as` keyword. It may also include property descriptions and nested node types.

```antlr
nodeType:
    IDENTIFIER (AS IDENTIFIER)?
    (LBRACKET nodePropertiesDescription* RBRACKET)?
    (LBRACE nodeType* RBRACE)?
    SCOL*;
```

### Node Properties Description: `nodePropertiesDescription`

The `nodePropertiesDescription` rule describes properties of a node, which can be either a string assignment or a function call.

```antlr
nodePropertiesDescription:
    STRING EQUAL STRING
    | STRING funcCall;
```

### Function Call: `funcCall`

The `funcCall` rule defines a function call that that takes a string argument.

```antlr
funcCall:
    IDENTIFIER LPARENTHESE STRING RPARENTHESE;
```

## Example

The following is an example of the DSL and how it conforms to the specified grammar:

```dsl
Symbol["value" is(".")]; // This is equivalent to Symbol["value" = "."].
Expr["type"="int"] as number;
Symbol["value"="!"];
```

In this example:
- `Symbol["value" is(".")]` captures the `Symbol` node if its `value` property, processed by the `is` function, matches the string `"."`.
- `Expr["type"="int"] as number` captures the `Expr` node if it has a property `type` with the value `int` and assigns it the alias `number`.
- `Symbol["value"="!"]` captures the `Symbol` node if it has a property `value` with the value `!`.

The structure showcases how to define node types with properties and nested node types, supporting recursive pattern matching in the AST.
