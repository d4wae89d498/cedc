# AST Node Matcher DSL Specification

## Overview

This document specifies the ANTLR grammar for the AST Node Matcher DSL. This DSL allows users to define patterns for matching nodes in an Abstract Syntax Tree (AST). Each node contains properties and children, where properties may be strings or other AST nodes.

## Lexer Rules

The lexer rules define the tokens used in the DSL:

- **DOLLAR**: Represents the `$` character.
- **CAPTURE**: The keyword `capture`.
- **SKIP**: The keyword `skip`.
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

The `astDescription` rule is the entry point for parsing the DSL. It describes the capture and skip statements, along with optional property descriptions and match lists.

```antlr
astDescription:
    (captureStmt | skipStmt)
    (LBRACKET astPropertyDescription* RBRACKET)?
    (LBRACE matchList RBRACE)?;
```

### Capture Statement: `captureStmt`

The `captureStmt` rule defines a `capture` statement, which may optionally specify an alias using the `as` keyword.

```antlr
captureStmt:
    CAPTURE IDENTIFIER (AS IDENTIFIER)?;
```

### Skip Statement: `skipStmt`

The `skipStmt` rule defines a `skip` statement.

```antlr
skipStmt:
    SKIP IDENTIFIER;
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

The `matchStmt` rule can be a capture statement, skip statement, or nested capture.

```antlr
matchStmt:
    captureStmt
    | skipStmt
    | nestedCapture;
```

### Nested Capture: `nestedCapture`

The `nestedCapture` rule allows for nested captures within braces, containing a match list.

```antlr
nestedCapture:
    IDENTIFIER LBRACE matchList RBRACE;
```

## Example

The following is an example of the DSL and how it conforms to the specified grammar:

```dsl
capture Type [
    "prop1" = "str"
    "prop2" islower($)
    "prop3" contains($, "needle"),
    "prop4" {
        capture SubType
    }
] {
	# Childs ...
}

skip Type

capture Identifier as id1
capture Parenthesis
capture Braces
capture Raw[value=async]
capture Func[
	"body"= {
		skip Braces {
			capture Expr {
				capture Raw[value=await]
				capture Call
			}
		}
	}
]
```

In this example:
- The `capture` and `skip` statements define patterns for matching AST nodes.
- Property descriptions include string assignments and function calls.
- Nested captures are defined within braces, allowing for recursive pattern matching.

