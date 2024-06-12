# Extensible Syntax Framework

[![Build Status](https://github.com/d4wae89d498/cedc/actions/workflows/ci.yaml/badge.svg)](https://github.com/d4wae89d498/cedc/actions)
[![License: CC BY-NC-SA 4.0](https://img.shields.io/badge/License-CC%20BY--NC--SA%204.0-lightgrey.svg)](https://creativecommons.org/licenses/by-nc-sa/4.0/)
[![Contributions Welcome](https://img.shields.io/badge/contributions-welcome-brightgreen.svg)](contributing.md)
[![Work in Progress](https://img.shields.io/badge/status-work%20in%20progress-orange.svg)](https://github.com/d4wae89d498/cedc)


![Docker Image Version](https://img.shields.io/docker/v/whitehat101/cedc/latest)
![Docker Image Size](https://img.shields.io/docker/image-size/whitehat101/cedc/latest)
![Docker Pulls](https://img.shields.io/docker/pulls/whitehat101/cedc.svg)

## Overview

Welcome to an extensible syntax framework!

Imagine a world where you can bend the syntax to your will—no limits, just pure creative freedom. This framework is designed to be an AST (Abstract Syntax Tree) preprocessor that empowers developers to create and use powerful syntax extensions.

⚠️ **Heads up**: We're still in the early stages. That means the documentation, usage instructions, and tests are on their way. Stay tuned!

## Goals

- **Limitless Extensibility**: Create custom syntax extensions without boundaries.
- **AST Preprocessing**: Dive deep into the AST of your code and manipulate it to fit your needs.
- **Developer Freedom**: Whether you want to tweak the syntax or overhaul it completely, the choice is yours.

### Building and Running the Project with Docker

To build and run the project using Docker, follow these steps:

1. **Build the Docker Image for Third-Party Dependencies**:
    This step creates a Docker image containing all the necessary third-party dependencies for the project. This image will serve as the base for the main project image.
    ```sh
    docker build -f dockerfile-system -t my-project-deps .
    ```

2. **Build the Docker Image for the Main Project**:
    Now, create the Docker image for the main project, using the previously built `my-project-deps` image as the base.
    ```sh
    docker build -f dockerfile -t my-project .
    ```

3. **Run the Project in Docker**:
    Finally, run the Docker container from the `my-project` image, which includes both the project and its dependencies.
    ```sh
    docker run -it my-project
    ```

These steps ensure that the environment is consistently set up with all required dependencies, making it easy to build and run the project in a controlled and reproducible Docker container.

### Non-Docker Instructions

#### Building and Running without Docker

1. **Install Dependencies**:
    Ensure you have all necessary dependencies installed on your system. This includes:
    - git
    - make
    - cmake
    - ninja-build
    - jq
    - antlr4 (see third-party/.versions for the needed version)
    - llvm (see third-party/.versions for the needed version)

2. **Clone the Repository**:
    ```sh
    git clone <repository-url>
    cd project-root

    ```
3. **Build the Project**:
    ```sh
    make
    ```

4. **Run Tests**:
    ```sh
    make test
    ```

By following these instructions, you can set up and run the project either using Docker for a containerized environment or directly on your local machine.


## Project Folder Structure

The following is an overview of the project's folder structure, illustrating the organization and purpose of each directory and file:

```
project-root/
├── bin/                        # Directory for compiled executables
├── lib/                        # Directory for compiled libraries
├── src/                        # Source code directory
│   ├── cli/                    # Command-line interface sources
│   ├── include/                # Header files
│   ├── module/                 # Modules source files
│   └── test/                   # Unit test source files
├── third-party/                # Third-party libraries and dependencies
│   ├── antlr/                  # ANTLR library
│   │   └── runtime/            # ANTLR runtime
│   ├── cppmodsort/             # Custom tool for module sorting
│   ├── libastmatcher-parser/   # AST Matcher Parser library
│   ├── llvm-project/           # LLVM project for C++ runtime
│   ├── ...                     # Other third-party packages
│   ├── makefile                # Makefile for third-party dependencies
│   ├── submodule.sh            # Tool script to move/delete submodules
│   └── .versions/              # Contains versions of dependencies
│       ├── antlr               # File containing version information (e.g., '4.13.1')
│       └── ...                 # Other version files
├── tmp/                        # Temporary files and build artifacts
│   ├── .cache/                 # Folder for tools cachings (clangd...)
│   ├── .marker/                # Folder containing build markers for dependencies
│   ├── dep/                    # Dependency files
│   ├── obj/                    # Object files
│   ├── pcm/                    # Precompiled module files
│   ├── pch/                    # Precompiled header files
│   └── .compile_commands       # Compilation database
├── test/                       # Contains test files for the Docker image (end-to-end tests)
├── common.mk                   # Common Makefile variables and settings
├── makefile                    # Main Makefile
├── dockerfile                  # Main Dockerfile for building the project environment
└── dockerfile-system           # Base image for the main Dockerfile
```

## Make Commands Summary

### General Make Commands

- `make`: Triggers a multi-threaded build.
- `make all`: Builds all targets, including third-party dependencies, project library, and executables.
- `make test`: Runs the unit test executables.
- `make clean`: Removes all dependency files, object files, and the compilation database.
- `make fclean`: Performs a clean operation and additionally removes compiled libraries, executables, precompiled modules, and headers.
- `make re`: Cleans the project and rebuilds everything from scratch.

### Submodules Make Commands

- `make deps`: Builds all third-party dependencies.
- `make llvm`: Specifically builds the LLVM dependency.
- `make std_pcm`: Builds the standard precompiled modules (libcxx pcm).
- `make antlr`: Specifically builds the ANTLR dependency.
- `make update_antlr`: Updates the ANTLR submodule to the latest version.
- `make update_llvm`: Updates the LLVM submodule to the latest version.
- `make update_deps`: Updates all submodules to their latest versions.
- `make clean_deps`: Cleans all third-party dependencies.

## Contributing

We'd love your help to make this project even better! If you're interested in contributing, take a look at our [Contributing Guidelines](contributing.md). Whether it's reporting a bug, suggesting a feature, or writing code, your input is welcome.

## License

This project is licensed under the CC BY-NC 4.0 License. For more details, see the [licence.txt](licence.txt) file.

## Links

- [GitHub Repository](https://github.com/d4wae89d498/cedc)
- [Contributing Guidelines](contributing.md)
- [License](licence.txt)

Stay tuned for more updates and happy coding!
