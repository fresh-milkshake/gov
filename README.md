<div align="center">

<a href="https://github.com/fresh-milkshake/gov"><picture>
<img alt="Gov Logo" src="assets/gov-building-circle.png" width="160px">
</picture></a>

<p align="center">
  <h1>Gov Programming Language</h1>
</p>

<p>
A satirical programming language with bureaucratic syntax and strong static typing.
</p>

[![cpp](https://img.shields.io/badge/C++-17-00599C?style=for-the-badge&logo=cplusplus&logoColor=white)](https://isocpp.org/)
[![License: MIT](https://img.shields.io/badge/License-MIT-blue.svg?style=for-the-badge)](LICENSE.txt)
[![Build and Release](https://img.shields.io/github/actions/workflow/status/fresh-milkshake/gov/ci.yml?label=Build%20%26%20Release&logo=github&style=for-the-badge)](https://github.com/fresh-milkshake/gov/actions/workflows/ci.yml)

<p align="center">
    <a href="" target="_blank" rel="noopener noreferrer">Website</a> •
    <a href="#installation" target="_blank" rel="noopener noreferrer">Installation</a> •
    <a href="GOV_LANGUAGE_DOCUMENTATION.md" target="_blank" rel="noopener noreferrer">Docs</a> •
    <a href="extension/README.md" target="_blank" rel="noopener noreferrer">VS Code Extension</a>
</p>


</div>

# Overview

**Gov** is a satirical programming language that uses bureaucratic terminology to create fully functional programs. Every program must start with a declaration of love for the government and use polite requests "PLEASE" for some operations.

## Features

- **Full programming language**: Variables, loops, conditions, functions
- **Static typing**: Strong type system with automatic conversions
- **Satirical syntax**: All commands use bureaucratic terminology
- **Ready interpreter**: Includes debugger and AST parser
- **VS Code support**: Syntax highlighting extension

## Quick Start

### Installation

#### Using CMake

```bash
# Create build directory
mkdir build && cd build

# Configure and build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build . --config Release

# Run a program
./bin/gov examples/hello_world.gov
```

### Example Program

```gov
!I_LOVE_GOVERNMENT

PRAISE_LEADER "Hello, World!"

PLEASE DECLARE_VARIABLE "Counter" AS INTEGER
PLEASE SET Counter TO 0

FOR_THE_PEOPLE Counter LESS_THAN 3 DO
    PRAISE_LEADER "Long live the Supreme Leader!"
    PLEASE INCREMENT Counter BY 1
END_FOR_THE_PEOPLE
```

## Interpreter Commands

- `./gov <file.gov>` - run program
- `./gov parse <file.gov>` - show AST structure
- `./gov debug <file.gov>` - debug mode
- `./gov --help` / `./gov -h` - help

## Documentation

Full Documentation: [GOV_LANGUAGE_DOCUMENTATION.md](GOV_LANGUAGE_DOCUMENTATION.md)

## Examples

Ready programs in `examples/` folder:
- [`hello_world.gov`](examples/hello_world.gov) - classic "Hello World"
- [`calculator.gov`](examples/calculator.gov) - simple calculator
- [`number_guessing.gov`](examples/number_guessing.gov) - number guessing game
- [`tic_tac_toe.gov`](examples/tic_tac_toe.gov) - tic tac toe game

## VS Code Support

Install the extension from `extension/` folder for `.gov` file syntax highlighting.

## License

This project is licensed under the MIT License. See [LICENSE](LICENSE.txt) for details.
