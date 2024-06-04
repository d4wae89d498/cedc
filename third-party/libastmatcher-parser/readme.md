# AST Node Matcher DSL Specification

## Overview

This document specifies the ANTLR grammar for the AST Node Matcher DSL. This DSL allows users to define patterns for matching nodes in an Abstract Syntax Tree (AST). Each node contains properties and children, where properties may be strings or other AST nodes.

## Lexer Rules

The lexer rules define the tokens used in the DSL:

- **DOLLAR**: Represents the `$` character.
- **AS**: The keyword `as`.
- **LPARENTHESE**: Represents the `(` character.
- **RPARENTHESE**: Represents the `)` character.
- **LBRACKET**: Represents the `[` character.
- **RBRACKET**: Represents the `]` character.
- **LBRACE**: Represents the `{` character.
- **RBRACE**: Represents the `}` character.
- **EQUAL**: Represents the `=` character.
- **COMMA**: Represents the `,` character.
- **IDENTIFIER**: Matches alphanumeric identifiers (letters, digits, and underscores) starting with a letter.
- **STRING**: Matches double-quoted string literals.
- **WHITESPACE**: Skips whitespace characters (space, tab, newline).

## Grammar Rules

The grammar rules define the structure and hierarchy of the DSL.

### Root Rule: `astDescription`

The `astDescription` rule is the entry point for parsing the DSL. It describes the node type statements, along with optional property descriptions and match lists.

```antlr
astDescription:
    nodeTypeStmt
    (LBRACKET astPropertyDescription* RBRACKET)?
    (LBRACE matchList RBRACE)?;
```

### Node Type Statement: `nodeTypeStmt`

The `nodeTypeStmt` rule defines a node type statement, which may optionally specify an alias using the `as` keyword.

```antlr
nodeTypeStmt:
    IDENTIFIER (AS IDENTIFIER)?;
```

### Property Description: `astPropertyDescription`

The `astPropertyDescription` rule describes properties of a node, which can be either a string assignment or a function call.

```antlr
astPropertyDescription:
    STRING EQUAL STRING
    | STRING funcCall;
```

### Function Call: `funcCall`

The `funcCall` rule defines a function call that may include a dollar sign and an optional string argument.

```antlr
funcCall:
    IDENTIFIER LPARENTHESE (DOLLAR COMMA? STRING?)? RPARENTHESE;
```

### Match List: `matchList`

The `matchList` rule defines a list of match statements separated by commas.

```antlr
matchList:
    (matchStmt (COMMA matchStmt)*)?;
```

### Match Statement: `matchStmt`

The `matchStmt` rule can be a node type statement or nested node type.

```antlr
matchStmt:
    nodeTypeStmt
    | nestedNodeType;
```

### Nested Node Type: `nestedNodeType`

The `nestedNodeType` rule allows for nested node types within braces, containing a match list.

```antlr
nestedNodeType:
    IDENTIFIER LBRACE matchList RBRACE;
```

## Example

The following is an example of the DSL and how it conforms to the specified grammar:

```dsl

	Expr["type"="int"] as number
	Symbol["value"="!"]

```

In this example:
- Capture the `Expr` node if it has a property `"type"="int"`, and name it as `number`.
- Skip the `Symbol` node if it has a property `"value"="!"`
- The structure showcases how to define node types with properties and nested node types, supporting recursive pattern matching in the AST.
