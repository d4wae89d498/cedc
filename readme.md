# Extensible Syntax Framework

[![Build Status](https://github.com/d4wae89d498/cedc/actions/workflows/ci.yaml/badge.svg)](https://github.com/d4wae89d498/cedc/actions)
[![License: CC BY-NC-SA 4.0](https://img.shields.io/badge/License-CC%20BY--NC--SA%204.0-lightgrey.svg)](https://creativecommons.org/licenses/by-nc-sa/4.0/)
[![Contributions Welcome](https://img.shields.io/badge/contributions-welcome-brightgreen.svg)](contributing.md)
[![Work in Progress](https://img.shields.io/badge/status-work%20in%20progress-orange.svg)](https://github.com/d4wae89d498/cedc)


![Docker Pulls](https://img.shields.io/docker/pulls/whitehat101/cedc.svg)
![Docker Image Version](https://img.shields.io/docker/v/whitehat101/cedc/latest)
![Docker Image Size](https://img.shields.io/docker/image-size/whitehat101/cedc/latest)

## Overview

Welcome to an extensible syntax framework!

Imagine a world where you can bend the syntax to your will—no limits, just pure creative freedom. This framework is designed to be an AST (Abstract Syntax Tree) preprocessor that empowers developers to create and use powerful syntax extensions.

⚠️ **Heads up**: We're still in the early stages. That means the documentation, usage instructions, and tests are on their way. Stay tuned!

## Goals

- **Limitless Extensibility**: Create custom syntax extensions without boundaries.
- **AST Preprocessing**: Dive deep into the AST of your code and manipulate it to fit your needs.
- **Developer Freedom**: Whether you want to tweak the syntax or overhaul it completely, the choice is yours.

## Contributing

We'd love your help to make this project even better! If you're interested in contributing, take a look at our [Contributing Guidelines](contributing.md). Whether it's reporting a bug, suggesting a feature, or writing code, your input is welcome.

## Compilation instructions

### MacOS
```bash
brew install antlr4
git submodule update --init
make
```

### Debian
```bash
apt-get install antlr4
git submodule update --init
make
```

## License

This project is licensed under the CC BY-NC 4.0 License. For more details, see the [licence.txt](licence.txt) file.

## Links

- [GitHub Repository](https://github.com/d4wae89d498/cedc)
- [Contributing Guidelines](contributing.md)
- [License](licence.txt)

Stay tuned for more updates and happy coding!
