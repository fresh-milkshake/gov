# Gov Language Support

A Visual Studio Code extension that provides syntax highlighting for the Gov programming language.

## Features

- Syntax highlighting for Gov language files (`.gov`)
- Support for Gov keywords, operators, strings, numbers, and comments
- Auto-closing pairs for brackets and quotes
- Line comment support with `//`

## Gov Language Keywords

The extension highlights the following Gov language constructs:

### Control Flow
- `I_LOVE_GOVERNMENT` - Program start declaration
- `FOR_THE_PEOPLE` / `END_FOR_THE_PEOPLE` - For loops
- `WHILE` / `END_WHILE` - While loops
- `IF` / `THEN` / `ELSE` / `ELSE_IF` / `END_IF` - Conditional statements
- `DO` - Loop body marker

### Commands
- `PRAISE_LEADER` - Output/print statement
- `OBEY_PARTY_LINE` - Comment declaration
- `PLEASE` - Polite command prefix
- `DECLARE_VARIABLE` - Variable declaration
- `SET` - Variable assignment
- `READ` - Input statement
- `INCREMENT` - Increment operation
- `DENOUNCE_IMPERIALIST_ERRORS` - Error handling

### Types and Operators
- `AS`, `INTEGER`, `STRING`, `ARRAY_OF_STRING`, `SIZE` - Type declarations
- `EQUALS`, `NOT_EQUALS`, `LESS_THAN` - Comparison operators
- `AND`, `OR` - Logical operators
- `TO`, `BY` - Assignment and increment keywords
- `+`, `-`, `*`, `/` - Arithmetic operators

## Installation

1. Copy the extension folder to your VS Code extensions directory
2. Reload VS Code
3. Open any `.gov` file to see syntax highlighting

## Example

```gov
!I_LOVE_GOVERNMENT

PRAISE_LEADER "Hello, World!"

PLEASE DECLARE_VARIABLE "Counter" AS INTEGER
PLEASE SET Counter TO 0

FOR_THE_PEOPLE Counter LESS_THAN 5 DO
    PRAISE_LEADER "Count: " + Counter
    PLEASE INCREMENT Counter BY 1
END_FOR_THE_PEOPLE
```

## License

This extension is provided as-is for educational and development purposes.