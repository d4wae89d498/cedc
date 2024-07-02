## Build System Improvements
- [x] **Makefile**: Add module generation path prefix to avoid name collisions.
- [x] **Makefile**: Integrate modules as libraries.
- [ ] **Makefile**: Develop a function to translate source files to final PCM destinations. Investigate and resolve issues requiring frequent deletions of lib/bin directories, potentially leveraging cedpm.

## AST Matcher DSL Enhancements
- [ ] **AST Matcher DSL / Nodes**: Implement a `replace_with()` function on AST nodes to facilitate AST manipulation.
- [ ] **AST Matcher DSL**: Ensure robust testing for the DSL.

## Extensibility and Examples
- [ ] **Extension Loading**: Implement functionality for loading extensions.
- [ ] **DSL Examples**: Use the DSL to create examples that demonstrate mixing multiple languages.

## Compiler Frontend/Backend Development
- [ ] **C Compiler Frontend/Backend**: Implement the basic frontend and backend for the C language.
- [ ] **Backend IR Selection**: Choose an appropriate backend Intermediate Representation (IR). Decide if the IR should be in Static Single Assignment (SSA) form at this stage or consider it for a later phase.
