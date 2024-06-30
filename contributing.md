# Contributing Guidelines

Thank you for considering contributing to our project! Here are some guidelines and best practices to help you get started and ensure a smooth collaboration process.

## Table of Contents

1. [Coding Style](#coding-style)
2. [Editor Configuration](#editor-configuration)
3. [Code Formatting and Linting](#code-formatting-and-linting)
4. [Modules and Modern C++ Practices](#modules-and-modern-cpp-practices)
5. [Commit Messages](#commit-messages)
6. [Pull Requests](#pull-requests)

## Coding Style

### Naming Conventions

#### Cases

- **UPPER_SNAKE_CASE**: Macros, enum items, `constexpr` names.
- **lower_snake_case**: Variable names (prefer one letter where applicable), function names, namespaces, module partition names.
- **PascalCase**: User-defined class names, template arguments (prefer one letter where applicable).
- **Module Names**: Defined as `organisation_name.module_name` reflecting the structure in the `src/module` folder.
- **Module Partition Names**: Reflect the folder structure. For example, `src/module/vendor1/package1/some/file.cppm` corresponds to `vendor1.package1:some.file`.
- **Namespaces**: Always use `vendor::package`, with no nested namespaces except in rare cases.

#### Prefixes

- **Global variables**: `g_`
- **Static variables**: `s_`
- **No prefixes** for members or types.

### Braces

- Always use ANSI C++ style.

### Function Keyword

- Use the `fn` keyword (C++ `auto` alias) everywhere to allow proper alignment of function names.

## Editor Configuration

To maintain consistency across different editors and IDEs, we use the following tools and extensions:

### VS Code Extensions

We recommend the following VS Code extensions:

```json
"recommendations": [
    "llvm-vs-code-extensions.vscode-clangd",
    "editorconfig.editorconfig",
    "Gruntfuggly.todo-tree"
]
```

#### Extensions Usage

- **clangd**: Provides smart code completion, diagnostics, formatting, and linting (including `clang-tidy` and `clang-format`) based on the Clang compiler.
- **EditorConfig**: Maintains consistent coding styles between different editors and IDEs.
- **TODO Tree**: Highlights TODO comments, making it easier to track and manage tasks directly within your codebase.

### EditorConfig Rules

Our project uses `.editorconfig` to define rules such as UTF-8 charset, tabs with a width of 4 spaces for indentation, trimming trailing whitespace, and inserting a final newline for specific file types.

## Code Formatting and Linting

We follow specific rules to ensure consistency and modern C++ practices across the codebase. These rules are enforced and applied using `clangd` tools, which provide integrated support for `clang-format` and `clang-tidy`.

## Modules and Modern C++ Practices

### Module Structure

- Use modules by default and the most modern C++ features wherever possible.
- Exceptions are made for specific cases like integration with ANTLR for our pattern matching domain-specific language.
- Module names and partition names must reflect the folder structure. For example, `src/module/vendor1/package1/some/file.cppm` corresponds to `vendor1.package1:some.file`.
- Implementation files (`.cpp`) should be placed next to their interfaces (`.cppm`).

### Implementation Guidelines

- Do not use private fragments; instead, use a separate implementation file for easier build system integration that uses timestamps.
- Use `.cpp` for implementation modules and `.cppm` for interfaces.
- Keep one class per module (or one function and its primitives is acceptable).

## Commit Messages

Write clear, concise commit messages that describe the changes made. Commit messages should include one of the following keywords to clearly indicate the nature of the change:

- **Create**: For adding new features or files.
- **Read**: For adding or updating read operations or documentation.
- **Update**: For updating existing features or files.
- **Delete**: For removing features or files.
- **Fix**: For bug fixes.
- **WIP**: For work-in-progress commits.

Format:
```
Keyword: Short description of the change

Detailed description of the change if necessary.
References issue #XYZ if applicable.
```

Examples:
```
Create: Add new logging functionality

This adds a new logging utility to help track application events.
References issue #123.
```

```
Fix: Resolve crash when loading configuration

Fixed a null pointer exception that caused a crash when loading configuration files.
```

## Pull Requests

When submitting a pull request, please ensure:

1. Your code adheres to our coding style guidelines.
2. You have tested your changes thoroughly.
3. You have updated or added documentation if necessary.
4. Your commit messages are clear and follow the specified format.

We appreciate your contributions and are here to help you succeed in making valuable improvements to our project! If you have any questions, feel free to reach out to the maintainers.
