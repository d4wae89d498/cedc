# Cedilla: An Experimental Extensible Single-Pass Transpiler

Cedilla is an experimental initiative designed to push the boundaries of C++ syntax. This project furnishes a comprehensive suite of tools enabling enthusiasts and developers alike to craft their own programming languages, which can then be compiled back to C/C++ for broad applicability and integration.

## Compilation Requirements

To successfully compile the Cedilla project, a modern compiler capable of handling C++26 standards is necessary. Currently, we extend support to Clang 17 as our preferred compiler.

To build the project, execute the following command in your terminal:

```bash
make
```

## Usage

The usage instructions are currently under development and will be provided in future updates of this document.

## Contributing to Cedilla

For those looking to contribute to the Cedilla project, we recommend using Visual Studio Code (VSCode) with the clangd extension enabled for an enhanced coding experience. Please ensure the MS Makefile extension is disabled to avoid any conflicts with our project's build system.

Upon compilation, our Makefile generates a `compile_commands.json` file, which facilitates a more integrated and efficient development process. To utilize this feature fully, the installation of `jq` is required as it allows for manipulation and analysis of this JSON file in a more user-friendly manner.

### Setting Up Your Development Environment:

1. Install [Visual Studio Code](https://code.visualstudio.com/).
2. Enable the `clangd` extension within VSCode.
3. Ensure the MS Makefile extension is disabled to prevent any interference with our Makefile configurations.
4. Install `jq` for handling `compile_commands.json`. This can typically be done through your package manager (e.g., `apt` for Ubuntu, `brew` for macOS).
5. Create a new file association in VSCode settings, key: `*.cppm` value: `cpp`
   
We welcome contributions from all members of the community. Whether you're fixing bugs, adding new features, or improving documentation, your help is greatly appreciated in making Cedilla a more robust and versatile tool for developers everywhere.

For more detailed information on how to contribute, please refer to our contributing guidelines (link to guidelines).
