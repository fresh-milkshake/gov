# Gov Programming Language Reference

## Table of Contents
1. [Introduction](#introduction)
2. [Language Philosophy](#language-philosophy)
3. [Lexical Structure](#lexical-structure)
4. [Keywords and Commands](#keywords-and-commands)
5. [Data Types](#data-types)
6. [Variables](#variables)
7. [Expressions](#expressions)
8. [Operators](#operators)
9. [Statements](#statements)
10. [Control Flow](#control-flow)
11. [Input/Output](#inputoutput)
12. [Comments](#comments)
13. [Arrays](#arrays)
14. [Error Handling](#error-handling)
15. [Program Structure](#program-structure)
16. [Standard Library](#standard-library)
17. [Implementation Details](#implementation-details)
18. [Examples](#examples)
19. [Interpreter Usage](#interpreter-usage)
20. [Language Grammar](#language-grammar)

## Introduction

Gov is a domain-specific programming language designed with satirical authoritarian and bureaucratic terminology. The language implements a complete imperative programming paradigm with static typing, lexical scoping, and structured control flow.

**Language Classification:**
- **Paradigm**: Imperative, procedural
- **Type System**: Static, strong typing with implicit conversions
- **Memory Management**: Automatic (interpreter-managed)
- **Execution Model**: Tree-walking interpreter
- **File Extension**: `.gov`

**Design Goals:**
- Provide complete programming functionality with satirical syntax
- Maintain readability despite verbose keyword structure  
- Implement familiar programming constructs with thematic naming
- Support educational use for programming concept demonstration

## Language Philosophy

Gov embraces verbose, politically-themed keywords that make programming feel like navigating government bureaucracy. Every program must show proper respect to the state, and all operations require polite requests using "PLEASE".

## Lexical Structure

### Character Set
Gov uses the ASCII character set. The language is case-sensitive for identifiers but keywords are defined in uppercase.

### Tokens
The lexical analyzer recognizes the following token categories:

**Keywords**: Reserved identifiers with special meaning
**Identifiers**: User-defined names for variables
**Literals**: Integer and string constants
**Operators**: Arithmetic, comparison, and logical operators
**Punctuation**: Brackets, parentheses, quotes
**Whitespace**: Spaces, tabs, newlines (significant for statement separation)
**Comments**: Single-line comments beginning with `//`

### Program Declaration
Every Gov program must begin with the mandatory program header:

```gov
!I_LOVE_GOVERNMENT
```

**Syntax**: `!I_LOVE_GOVERNMENT`
**Semantics**: Declares the beginning of a Gov program. This token must appear as the first non-comment, non-whitespace token in the source file.
**Implementation**: Parsed as `TokenType::I_LOVE_GOVERNMENT` by the lexer.

### Statement Termination
Statements are terminated by newlines. Multiple statements cannot appear on the same line.

```gov
PRAISE_LEADER "First statement"
PRAISE_LEADER "Second statement"  // Correct

PRAISE_LEADER "First" PRAISE_LEADER "Second"  // Error: Invalid syntax
```

### Whitespace Sensitivity
- Leading whitespace is ignored for parsing but recommended for readability
- Trailing whitespace is ignored
- Empty lines are permitted and ignored
- Newlines serve as statement separators

### String Literals
String literals are enclosed in double quotes and support basic escape sequences:

```gov
"Simple string"
"String with \"escaped quotes\""
"String with\nnewline"  // Note: Actual escape sequence support depends on implementation
```

## Keywords and Commands

### Core Keywords

#### Program Structure
- `!I_LOVE_GOVERNMENT` - Mandatory program start declaration
- `OBEY_PARTY_LINE` - Comment declaration (followed by comment text)

#### Polite Operations
- `PLEASE` - Required prefix for most operations

#### Output
- `PRAISE_LEADER` - Print/output statement

#### Variable Operations
- `DECLARE_VARIABLE` - Variable declaration
- `SET` - Variable assignment
- `READ` - Input statement
- `INCREMENT` - Increment a variable

#### Control Flow
- `FOR_THE_PEOPLE` / `END_FOR_THE_PEOPLE` - For loop
- `WHILE` / `END_WHILE` - While loop
- `IF` / `THEN` / `ELSE` / `ELSE_IF` / `END_IF` - Conditional statements
- `DO` - Loop body marker

#### Type System
- `AS` - Type declaration keyword
- `INTEGER` - Integer type
- `STRING` - String type
- `ARRAY_OF_STRING` - String array type
- `SIZE` - Array size specifier

#### Operators and Keywords
- `TO` - Assignment operator
- `BY` - Increment amount specifier
- `EQUALS` - Equality comparison
- `NOT_EQUALS` - Inequality comparison
- `LESS_THAN` - Less than comparison
- `AND` - Logical AND
- `OR` - Logical OR

#### Error Handling
- `DENOUNCE_IMPERIALIST_ERRORS` - Error handling/debugging statement

## Data Types

Gov implements a static type system with three fundamental data types. All variables must be explicitly declared with their type before use.

### Integer Type

**Declaration**: `AS INTEGER`
**Storage**: 32-bit signed integer (implementation-dependent)
**Range**: Typically -2,147,483,648 to 2,147,483,647
**Default Value**: 0 (when declared but not initialized)

```gov
PLEASE DECLARE_VARIABLE "Counter" AS INTEGER
PLEASE DECLARE_VARIABLE "NegativeValue" AS INTEGER
PLEASE SET Counter TO 42
PLEASE SET NegativeValue TO -17
```

**Literal Syntax**:
- Decimal integers: `42`, `-17`, `0`
- No support for hexadecimal, octal, or binary literals
- No support for integer suffixes or type specifiers

**Arithmetic Behavior**:
- Standard integer arithmetic with potential overflow (implementation-defined)
- Division truncates toward zero: `7 / 3` results in `2`
- Division by zero behavior is implementation-defined

### String Type

**Declaration**: `AS STRING`
**Storage**: Variable-length string (implementation manages memory)
**Encoding**: ASCII (implementation-dependent)
**Default Value**: Empty string `""` (when declared but not initialized)

```gov
PLEASE DECLARE_VARIABLE "Message" AS STRING
PLEASE DECLARE_VARIABLE "EmptyString" AS STRING
PLEASE SET Message TO "Glory to the state!"
// EmptyString remains ""
```

**Literal Syntax**:
- Enclosed in double quotes: `"Hello, World!"`
- Escape sequences (implementation-dependent):
  - `\"` - Double quote
  - `\\` - Backslash
  - `\n` - Newline (if supported)

**String Operations**:
- Concatenation using `+` operator
- Automatic conversion from integer to string in concatenation contexts
- Immutable (assignment creates new string)

### Array Type

**Declaration**: `AS ARRAY_OF_STRING SIZE n`
**Element Type**: String only (no integer arrays supported)
**Size**: Fixed at declaration time, must be positive integer literal
**Indexing**: Zero-based, bounds checking implementation-dependent
**Default Value**: All elements initialized to empty string `""`

```gov
PLEASE DECLARE_VARIABLE "Names" AS ARRAY_OF_STRING SIZE 5
PLEASE DECLARE_VARIABLE "Board" AS ARRAY_OF_STRING SIZE 9

// Access elements
PLEASE SET Names[0] TO "First element"
PLEASE SET Names[4] TO "Last element"
PRAISE_LEADER Names[0]  // Outputs: First element
```

**Array Indexing**:
- Index must be integer expression
- Valid indices: `0` to `size-1`
- Out-of-bounds access behavior is implementation-defined
- Dynamic indexing supported: `Array[variable]`

**Limitations**:
- No multi-dimensional arrays
- No array resizing after declaration
- No array-to-array assignment
- No array literals for initialization

### Type Conversion

**Implicit Conversions**:
- Integer to String: Automatic in concatenation contexts
- String to Integer: Automatic in `READ` operations for integer variables

```gov
PLEASE DECLARE_VARIABLE "Number" AS INTEGER
PLEASE DECLARE_VARIABLE "Text" AS STRING

PLEASE SET Number TO 42
PLEASE SET Text TO "Value: " + Number  // Number implicitly converted to "42"
```

**Explicit Conversions**:
- No explicit cast operators available
- Type conversion occurs automatically in appropriate contexts

### Type Compatibility

**Assignment Compatibility**:
- Integer ← Integer: Direct assignment
- String ← String: Direct assignment  
- String ← Integer: Implicit conversion in concatenation
- Array[i] ← String: Element assignment
- No other cross-type assignments permitted

**Expression Compatibility**:
- Arithmetic operators: Integer × Integer → Integer
- Comparison operators: Same type × Same type → Boolean (internal)
- Concatenation: String + (String|Integer) → String

## Variables

### Variable Declaration

**Syntax**: `PLEASE DECLARE_VARIABLE "identifier" AS type [SIZE n]`

Variables must be explicitly declared before first use. The declaration specifies the variable's name, type, and for arrays, the size.

```gov
// Basic variable declarations
PLEASE DECLARE_VARIABLE "Counter" AS INTEGER
PLEASE DECLARE_VARIABLE "UserName" AS STRING
PLEASE DECLARE_VARIABLE "GameBoard" AS ARRAY_OF_STRING SIZE 9
```

**Declaration Rules**:
- Must appear before any use of the variable
- Cannot redeclare the same variable name
- Array size must be positive integer literal (not variable)
- Declaration does not require initial value (uses default)

**Scope**: All variables have global scope within the program. No block scoping is implemented.

### Variable Assignment

**Syntax**: `PLEASE SET identifier TO expression`
**Array Syntax**: `PLEASE SET identifier[index] TO expression`

```gov
// Scalar assignment
PLEASE SET Counter TO 42
PLEASE SET UserName TO "Comrade Smith"

// Array element assignment  
PLEASE SET GameBoard[0] TO "X"
PLEASE SET GameBoard[Counter] TO "O"  // Dynamic indexing

// Expression assignment
PLEASE SET Counter TO Counter + 1
PLEASE SET UserName TO "Hello, " + UserName
```

**Assignment Semantics**:
- Right-hand side expression is fully evaluated before assignment
- Type compatibility is enforced (with implicit conversions)
- Array bounds checking depends on implementation
- Assignment to undeclared variable causes compile-time error

### Identifier Rules

**Naming Conventions**:
- Enclosed in double quotes during declaration: `"VariableName"`
- Used without quotes in expressions: `VariableName`
- Case-sensitive: `"Counter"` and `"counter"` are different variables

**Valid Identifier Characters**:
- Must start with letter (a-z, A-Z) or underscore (_)
- Subsequent characters can be letters, digits (0-9), or underscores
- No length limit specified (implementation-dependent)

**Valid Examples**:
```gov
PLEASE DECLARE_VARIABLE "Counter" AS INTEGER
PLEASE DECLARE_VARIABLE "user_name" AS STRING  
PLEASE DECLARE_VARIABLE "Player1Score" AS INTEGER
PLEASE DECLARE_VARIABLE "_privateVar" AS STRING
PLEASE DECLARE_VARIABLE "MAX_SIZE" AS INTEGER
```

**Invalid Examples**:
```gov
PLEASE DECLARE_VARIABLE "123invalid" AS INTEGER  // Cannot start with digit
PLEASE DECLARE_VARIABLE "user-name" AS STRING    // Hyphen not allowed
PLEASE DECLARE_VARIABLE "user name" AS STRING    // Space not allowed
PLEASE DECLARE_VARIABLE "" AS INTEGER            // Empty name not allowed
```

### Variable Initialization

**Default Initialization**:
- `INTEGER`: Initialized to `0`
- `STRING`: Initialized to empty string `""`
- `ARRAY_OF_STRING`: All elements initialized to `""`

```gov
PLEASE DECLARE_VARIABLE "Count" AS INTEGER
PLEASE DECLARE_VARIABLE "Name" AS STRING
PLEASE DECLARE_VARIABLE "Items" AS ARRAY_OF_STRING SIZE 3

PRAISE_LEADER Count      // Outputs: 0
PRAISE_LEADER Name       // Outputs: (empty string)
PRAISE_LEADER Items[0]   // Outputs: (empty string)
```

**Explicit Initialization**:
Variables can be assigned immediately after declaration:

```gov
PLEASE DECLARE_VARIABLE "Count" AS INTEGER
PLEASE SET Count TO 100

PLEASE DECLARE_VARIABLE "Greeting" AS STRING  
PLEASE SET Greeting TO "Welcome, Comrade!"
```

### Variable Usage

**In Expressions**:
```gov
PLEASE DECLARE_VARIABLE "A" AS INTEGER
PLEASE DECLARE_VARIABLE "B" AS INTEGER
PLEASE DECLARE_VARIABLE "Result" AS INTEGER

PLEASE SET A TO 10
PLEASE SET B TO 20
PLEASE SET Result TO A + B * 2  // Result = 50
```

**In Control Flow**:
```gov
PLEASE DECLARE_VARIABLE "Counter" AS INTEGER
PLEASE SET Counter TO 0

WHILE Counter LESS_THAN 5 DO
    PRAISE_LEADER "Count: " + Counter
    PLEASE INCREMENT Counter BY 1
END_WHILE
```

**Array Variable Usage**:
```gov
PLEASE DECLARE_VARIABLE "Names" AS ARRAY_OF_STRING SIZE 3
PLEASE DECLARE_VARIABLE "Index" AS INTEGER

PLEASE SET Names[0] TO "Alice"
PLEASE SET Names[1] TO "Bob"  
PLEASE SET Names[2] TO "Charlie"

PLEASE SET Index TO 1
PRAISE_LEADER Names[Index]  // Outputs: Bob
```

### Variable Lifetime

**Storage Duration**: All variables exist for the entire program execution
**Initialization**: Variables are initialized when declared
**Destruction**: Variables are automatically destroyed when program terminates
**Persistence**: No persistent storage between program runs

## Expressions

Gov supports various expression types including literals, identifiers, binary operations, and array access. Expressions are evaluated according to operator precedence and associativity rules.

### Primary Expressions

**Integer Literals**:
```gov
42          // Decimal integer
-17         // Negative integer  
0           // Zero
2147483647  // Maximum typical value
```

**String Literals**:
```gov
"Hello, World!"           // Simple string
"The state approves"      // String with spaces
""                        // Empty string
"Quote: \"Hello\""        // String with escaped quotes
```

**Identifiers**:
```gov
Counter                   // Variable reference
UserName                  // String variable
GameBoard                 // Array variable (not element access)
```

**Array Access**:
```gov
GameBoard[0]              // Constant index
GameBoard[Counter]        // Variable index
GameBoard[Index + 1]      // Expression index
```

### Binary Expressions

Binary expressions combine two operands with an operator. Evaluation follows standard precedence rules.

## Operators

### Arithmetic Operators

**Addition (`+`)**:
- **Operands**: Integer + Integer → Integer, String + String → String, String + Integer → String
- **Precedence**: 6 (left-to-right associative)
- **Semantics**: Numeric addition or string concatenation

```gov
PLEASE DECLARE_VARIABLE "A" AS INTEGER
PLEASE DECLARE_VARIABLE "B" AS INTEGER
PLEASE DECLARE_VARIABLE "Result" AS INTEGER
PLEASE DECLARE_VARIABLE "Message" AS STRING

PLEASE SET A TO 10
PLEASE SET B TO 20
PLEASE SET Result TO A + B        // Result = 30

PLEASE SET Message TO "Count: " + A  // Message = "Count: 10"
```

**Subtraction (`-`)**:
- **Operands**: Integer - Integer → Integer
- **Precedence**: 6 (left-to-right associative)
- **Semantics**: Numeric subtraction, overflow behavior implementation-defined

```gov
PLEASE SET Result TO 50 - 30      // Result = 20
PLEASE SET Result TO 10 - 20      // Result = -10
```

**Multiplication (`*`)**:
- **Operands**: Integer * Integer → Integer
- **Precedence**: 7 (left-to-right associative)
- **Semantics**: Numeric multiplication, overflow behavior implementation-defined

```gov
PLEASE SET Result TO 6 * 7        // Result = 42
PLEASE SET Result TO -3 * 4       // Result = -12
```

**Division (`/`)**:
- **Operands**: Integer / Integer → Integer
- **Precedence**: 7 (left-to-right associative)
- **Semantics**: Integer division (truncation toward zero), division by zero implementation-defined

```gov
PLEASE SET Result TO 15 / 3       // Result = 5
PLEASE SET Result TO 16 / 3       // Result = 5 (truncated)
PLEASE SET Result TO -7 / 3       // Result = -2 (truncated toward zero)
```

### Comparison Operators

**Equality (`EQUALS`)**:
- **Operands**: Integer EQUALS Integer → Boolean, String EQUALS String → Boolean
- **Precedence**: 4 (left-to-right associative)
- **Semantics**: Value equality comparison

```gov
IF Counter EQUALS 10 THEN
    PRAISE_LEADER "Counter reached target"
END_IF

IF UserName EQUALS "admin" THEN
    PRAISE_LEADER "Administrator access granted"
END_IF
```

**Inequality (`NOT_EQUALS`)**:
- **Operands**: Integer NOT_EQUALS Integer → Boolean, String NOT_EQUALS String → Boolean
- **Precedence**: 4 (left-to-right associative)
- **Semantics**: Value inequality comparison

```gov
IF Counter NOT_EQUALS 0 THEN
    PRAISE_LEADER "Counter is not zero"
END_IF
```

**Less Than (`LESS_THAN`)**:
- **Operands**: Integer LESS_THAN Integer → Boolean
- **Precedence**: 5 (left-to-right associative)
- **Semantics**: Numeric less-than comparison
- **Note**: No string comparison support

```gov
IF Age LESS_THAN 18 THEN
    PRAISE_LEADER "Too young for military service"
END_IF
```

### Logical Operators

**Logical AND (`AND`)**:
- **Operands**: Boolean AND Boolean → Boolean
- **Precedence**: 2 (left-to-right associative)
- **Semantics**: Short-circuit evaluation (right operand not evaluated if left is false)

```gov
IF Age LESS_THAN 65 AND Age NOT_EQUALS 0 THEN
    PRAISE_LEADER "Working age citizen"
END_IF
```

**Logical OR (`OR`)**:
- **Operands**: Boolean OR Boolean → Boolean
- **Precedence**: 1 (left-to-right associative)
- **Semantics**: Short-circuit evaluation (right operand not evaluated if left is true)

```gov
IF Status EQUALS "admin" OR Status EQUALS "moderator" THEN
    PRAISE_LEADER "Elevated privileges granted"
END_IF
```

### Operator Precedence Table

| Precedence | Operator | Associativity | Description |
|------------|----------|---------------|-------------|
| 7 (highest) | `*`, `/` | Left-to-right | Multiplication, Division |
| 6 | `+`, `-` | Left-to-right | Addition, Subtraction |
| 5 | `LESS_THAN` | Left-to-right | Relational comparison |
| 4 | `EQUALS`, `NOT_EQUALS` | Left-to-right | Equality comparison |
| 3 | `AND` | Left-to-right | Logical AND |
| 2 (lowest) | `OR` | Left-to-right | Logical OR |

### Expression Evaluation

**Evaluation Order**:
1. Parentheses (highest precedence)
2. Operator precedence (as listed above)
3. Left-to-right associativity for same precedence
4. Short-circuit evaluation for logical operators

**Complex Expression Examples**:
```gov
// Arithmetic with precedence
PLEASE SET Result TO 2 + 3 * 4        // Result = 14 (not 20)
PLEASE SET Result TO (2 + 3) * 4       // Result = 20

// Mixed comparison and logical
IF (Age LESS_THAN 18 OR Age EQUALS 65) AND Status EQUALS "citizen" THEN
    PRAISE_LEADER "Special status citizen"
END_IF

// String concatenation with arithmetic
PLEASE SET Message TO "Result: " + (A + B)  // Concatenates "Result: " with sum
```

### Type Coercion in Expressions

**Automatic Conversions**:
- Integer to String in concatenation contexts
- String to Integer in arithmetic contexts (if parseable)

```gov
PLEASE DECLARE_VARIABLE "Count" AS INTEGER
PLEASE DECLARE_VARIABLE "Message" AS STRING

PLEASE SET Count TO 42
PLEASE SET Message TO "Items: " + Count    // Count converted to "42"
```

**Invalid Type Combinations**:
```gov
// These would cause type errors:
// PLEASE SET Result TO "hello" + 42        // Error: Cannot add string and integer
// IF "text" LESS_THAN 5 THEN              // Error: Cannot compare string and integer
```

## Statements

Statements are the executable units of Gov programs. Each statement performs an action and must be terminated by a newline.

### Expression Statements

Currently, Gov does not support standalone expression statements. All expressions must be part of other statement types.

### Assignment Statement

**Syntax**: `PLEASE SET identifier TO expression`
**Array Syntax**: `PLEASE SET identifier[index_expression] TO expression`

```gov
// Scalar assignment
PLEASE SET Counter TO 42
PLEASE SET Message TO "Hello, " + UserName

// Array assignment
PLEASE SET Board[0] TO "X"
PLEASE SET Board[CurrentPlayer] TO PlayerSymbol
```

**Semantics**:
- Evaluates right-hand expression completely before assignment
- Performs type checking and implicit conversions
- For arrays, evaluates index expression and performs bounds checking

### Print Statement

**Syntax**: `PRAISE_LEADER expression`

```gov
PRAISE_LEADER "Hello, World!"
PRAISE_LEADER Counter
PRAISE_LEADER "Count is: " + Counter
PRAISE_LEADER Board[0]
```

**Semantics**:
- Evaluates expression and outputs result to standard output
- Automatically converts integers to string representation
- Outputs newline after the value

### Input Statement

**Syntax**: `PLEASE READ identifier`

```gov
PLEASE DECLARE_VARIABLE "UserInput" AS INTEGER
PLEASE DECLARE_VARIABLE "UserName" AS STRING

PLEASE READ UserInput    // Reads integer from stdin
PLEASE READ UserName     // Reads string from stdin
```

**Semantics**:
- Reads input from standard input until newline
- For INTEGER variables: attempts to parse input as integer
- For STRING variables: stores input as-is (excluding newline)
- Invalid integer input behavior is implementation-defined

### Increment Statement

**Syntax**: `PLEASE INCREMENT identifier BY integer_literal`

```gov
PLEASE INCREMENT Counter BY 1
PLEASE INCREMENT Score BY 10
PLEASE INCREMENT Index BY -1    // Decrement
```

**Semantics**:
- Adds the specified amount to the variable
- Variable must be of INTEGER type
- Amount must be integer literal (not expression)
- Equivalent to: `PLEASE SET identifier TO identifier + amount`

### Variable Declaration Statement

**Syntax**: 
- `PLEASE DECLARE_VARIABLE "identifier" AS INTEGER`
- `PLEASE DECLARE_VARIABLE "identifier" AS STRING`
- `PLEASE DECLARE_VARIABLE "identifier" AS ARRAY_OF_STRING SIZE integer_literal`

```gov
PLEASE DECLARE_VARIABLE "Counter" AS INTEGER
PLEASE DECLARE_VARIABLE "PlayerName" AS STRING
PLEASE DECLARE_VARIABLE "GameBoard" AS ARRAY_OF_STRING SIZE 9
```

**Semantics**:
- Creates new variable with specified name and type
- Initializes variable to default value for type
- Variable name must be unique within program
- Array size must be positive integer literal

## Control Flow

Control flow statements alter the sequential execution of statements based on conditions or iteration requirements.

### Conditional Statements

#### If Statement

**Syntax**:
```
IF condition THEN
    statement_list
[ELSE_IF condition THEN
    statement_list]...
[ELSE
    statement_list]
END_IF
```

**Semantics**:
- Evaluates condition expression (must result in boolean value)
- Executes first matching branch
- Supports multiple ELSE_IF clauses
- ELSE clause is optional
- Only one branch is executed per IF statement

**Examples**:
```gov
// Simple if
IF Counter EQUALS 10 THEN
    PRAISE_LEADER "Target reached!"
END_IF

// If-else
IF Age LESS_THAN 18 THEN
    PRAISE_LEADER "Minor citizen"
ELSE
    PRAISE_LEADER "Adult citizen"
END_IF

// Multiple conditions
IF Score LESS_THAN 60 THEN
    PRAISE_LEADER "Needs improvement"
ELSE_IF Score LESS_THAN 80 THEN
    PRAISE_LEADER "Satisfactory performance"
ELSE_IF Score LESS_THAN 95 THEN
    PRAISE_LEADER "Excellent work"
ELSE
    PRAISE_LEADER "Outstanding achievement"
END_IF

// Complex conditions
IF (Age LESS_THAN 65 AND Status EQUALS "active") OR Rank EQUALS "officer" THEN
    PRAISE_LEADER "Eligible for duty"
END_IF
```

**Nested If Statements**:
```gov
IF UserType EQUALS "admin" THEN
    IF SecurityLevel EQUALS "high" THEN
        PRAISE_LEADER "Full access granted"
    ELSE
        PRAISE_LEADER "Limited admin access"
    END_IF
ELSE
    PRAISE_LEADER "Regular user access"
END_IF
```

### Iteration Statements

#### For Loop

**Syntax**:
```
FOR_THE_PEOPLE variable LESS_THAN limit_expression DO
    statement_list
END_FOR_THE_PEOPLE
```

**Semantics**:
- Variable must be previously declared INTEGER variable
- Limit expression evaluated once at loop start
- Loop continues while variable < limit
- Variable must be manually incremented within loop body
- No automatic increment (unlike traditional for loops)

**Examples**:
```gov
PLEASE DECLARE_VARIABLE "I" AS INTEGER
PLEASE SET I TO 0

FOR_THE_PEOPLE I LESS_THAN 5 DO
    PRAISE_LEADER "Iteration: " + I
    PLEASE INCREMENT I BY 1
END_FOR_THE_PEOPLE
// Outputs: Iteration: 0, 1, 2, 3, 4

// Dynamic limit
PLEASE DECLARE_VARIABLE "Limit" AS INTEGER
PLEASE SET Limit TO 3
PLEASE SET I TO 0

FOR_THE_PEOPLE I LESS_THAN Limit DO
    PRAISE_LEADER "Count: " + I
    PLEASE INCREMENT I BY 1
END_FOR_THE_PEOPLE
```

**Important Notes**:
- Loop variable is not automatically incremented
- Forgetting to increment creates infinite loop
- Limit expression evaluated only once at loop entry
- Loop variable can be modified by any amount

#### While Loop

**Syntax**:
```
WHILE condition DO
    statement_list
END_WHILE
```

**Semantics**:
- Condition evaluated before each iteration
- Loop continues while condition is true
- Condition must be boolean expression
- Loop body may not execute if condition initially false

**Examples**:
```gov
PLEASE DECLARE_VARIABLE "Count" AS INTEGER
PLEASE SET Count TO 0

WHILE Count LESS_THAN 5 DO
    PRAISE_LEADER "Count: " + Count
    PLEASE INCREMENT Count BY 1
END_WHILE

// Input validation loop
PLEASE DECLARE_VARIABLE "Input" AS INTEGER
PLEASE SET Input TO -1

WHILE Input LESS_THAN 1 OR Input NOT_EQUALS Input DO  // Note: Second condition always false
    PRAISE_LEADER "Enter positive number:"
    PLEASE READ Input
END_WHILE
```

**Infinite Loop Prevention**:
```gov
// Dangerous: potential infinite loop
WHILE Counter LESS_THAN 10 DO
    PRAISE_LEADER "This might run forever"
    // Missing: PLEASE INCREMENT Counter BY 1
END_WHILE

// Safe: guaranteed termination
PLEASE DECLARE_VARIABLE "Safety" AS INTEGER
PLEASE SET Safety TO 0

WHILE Counter LESS_THAN 10 AND Safety LESS_THAN 1000 DO
    PRAISE_LEADER "Iteration: " + Counter
    PLEASE INCREMENT Counter BY 1
    PLEASE INCREMENT Safety BY 1
END_WHILE
```

### Control Flow Nesting

All control flow statements can be nested arbitrarily:

```gov
PLEASE DECLARE_VARIABLE "I" AS INTEGER
PLEASE DECLARE_VARIABLE "J" AS INTEGER

PLEASE SET I TO 0
FOR_THE_PEOPLE I LESS_THAN 3 DO
    PLEASE SET J TO 0
    WHILE J LESS_THAN 2 DO
        IF I EQUALS J THEN
            PRAISE_LEADER "Diagonal: " + I + "," + J
        ELSE
            PRAISE_LEADER "Off-diagonal: " + I + "," + J
        END_IF
        PLEASE INCREMENT J BY 1
    END_WHILE
    PLEASE INCREMENT I BY 1
END_FOR_THE_PEOPLE
```

### Boolean Context

Expressions used in conditional contexts (IF, WHILE conditions) must evaluate to boolean values. Gov uses the following truthiness rules:

**Integer Values**:
- `0` is false
- Any non-zero value is true

**String Values**:
- Empty string `""` is false  
- Any non-empty string is true

**Comparison Results**:
- Comparison operators (`EQUALS`, `NOT_EQUALS`, `LESS_THAN`) produce boolean values
- Logical operators (`AND`, `OR`) produce boolean values

## Input/Output

### Output
Use `PRAISE_LEADER` to display output:
```gov
PRAISE_LEADER "Hello, World!"
PRAISE_LEADER variable_name
PRAISE_LEADER "Value: " + variable_name
```

### Input
Use `PLEASE READ` to get user input:
```gov
PLEASE READ variable_name
```
The input will be automatically converted to the variable's declared type.

## Comments

### Line Comments
```gov
// This is a line comment
PRAISE_LEADER "This code runs"
```

### Party Line Comments
```gov
OBEY_PARTY_LINE "This is a comment explaining the state's position"
```

## Arrays

Arrays in Gov are fixed-size, homogeneous collections of strings. They provide indexed access to elements and are zero-based.

### Array Declaration

**Syntax**: `PLEASE DECLARE_VARIABLE "identifier" AS ARRAY_OF_STRING SIZE integer_literal`

```gov
PLEASE DECLARE_VARIABLE "PlayerNames" AS ARRAY_OF_STRING SIZE 4
PLEASE DECLARE_VARIABLE "GameBoard" AS ARRAY_OF_STRING SIZE 9
PLEASE DECLARE_VARIABLE "MenuOptions" AS ARRAY_OF_STRING SIZE 10
```

**Declaration Semantics**:
- Size must be positive integer literal (compile-time constant)
- All elements initialized to empty string `""`
- Array size cannot be changed after declaration
- Memory allocated for entire array at declaration time

**Size Limitations**:
- Minimum size: 1
- Maximum size: Implementation-dependent (typically limited by available memory)
- Size must be known at compile time

### Array Access

**Syntax**: `identifier[index_expression]`

```gov
PLEASE DECLARE_VARIABLE "Names" AS ARRAY_OF_STRING SIZE 5
PLEASE DECLARE_VARIABLE "Index" AS INTEGER

// Constant index access
PRAISE_LEADER Names[0]        // First element
PRAISE_LEADER Names[4]        // Last element (size-1)

// Variable index access
PLEASE SET Index TO 2
PRAISE_LEADER Names[Index]    // Third element

// Expression index access
PRAISE_LEADER Names[Index + 1]     // Fourth element
PRAISE_LEADER Names[Index * 2]     // Fifth element (if Index=2)
```

**Index Expression Requirements**:
- Must evaluate to integer value
- Evaluated at runtime for each access
- Can be any valid integer expression

### Array Assignment

**Element Assignment Syntax**: `PLEASE SET identifier[index_expression] TO expression`

```gov
PLEASE DECLARE_VARIABLE "Scores" AS ARRAY_OF_STRING SIZE 3
PLEASE DECLARE_VARIABLE "PlayerIndex" AS INTEGER

// Direct assignment
PLEASE SET Scores[0] TO "100"
PLEASE SET Scores[1] TO "85"
PLEASE SET Scores[2] TO "92"

// Dynamic assignment
PLEASE SET PlayerIndex TO 1
PLEASE SET Scores[PlayerIndex] TO "95"

// Expression-based assignment
PLEASE SET Scores[PlayerIndex + 1] TO "88"
```

**Assignment Semantics**:
- Right-hand expression fully evaluated before assignment
- Index expression evaluated before assignment
- Bounds checking implementation-dependent
- Only string values can be assigned to array elements

### Array Indexing

**Zero-Based Indexing**:
- First element: `Array[0]`
- Last element: `Array[size-1]`
- Valid range: `0` to `size-1` inclusive

```gov
PLEASE DECLARE_VARIABLE "Items" AS ARRAY_OF_STRING SIZE 5

// Valid indices: 0, 1, 2, 3, 4
PLEASE SET Items[0] TO "First"    // Valid
PLEASE SET Items[4] TO "Last"     // Valid
PLEASE SET Items[5] TO "Invalid"  // Out of bounds - behavior undefined
```

**Bounds Checking**:
- Implementation may or may not check array bounds
- Out-of-bounds access behavior is undefined
- Negative indices are invalid
- Accessing beyond array size is invalid

**Dynamic Indexing Examples**:
```gov
PLEASE DECLARE_VARIABLE "Board" AS ARRAY_OF_STRING SIZE 9
PLEASE DECLARE_VARIABLE "Row" AS INTEGER
PLEASE DECLARE_VARIABLE "Col" AS INTEGER
PLEASE DECLARE_VARIABLE "Position" AS INTEGER

// 2D-like access using 1D array
PLEASE SET Row TO 1
PLEASE SET Col TO 2
PLEASE SET Position TO Row * 3 + Col  // Convert 2D to 1D index
PLEASE SET Board[Position] TO "X"

// Loop-based access
PLEASE DECLARE_VARIABLE "I" AS INTEGER
PLEASE SET I TO 0

FOR_THE_PEOPLE I LESS_THAN 9 DO
    PLEASE SET Board[I] TO "empty"
    PLEASE INCREMENT I BY 1
END_FOR_THE_PEOPLE
```

### Array Initialization Patterns

**Manual Initialization**:
```gov
PLEASE DECLARE_VARIABLE "Days" AS ARRAY_OF_STRING SIZE 7

PLEASE SET Days[0] TO "Monday"
PLEASE SET Days[1] TO "Tuesday"
PLEASE SET Days[2] TO "Wednesday"
PLEASE SET Days[3] TO "Thursday"
PLEASE SET Days[4] TO "Friday"
PLEASE SET Days[5] TO "Saturday"
PLEASE SET Days[6] TO "Sunday"
```

**Loop-Based Initialization**:
```gov
PLEASE DECLARE_VARIABLE "Numbers" AS ARRAY_OF_STRING SIZE 10
PLEASE DECLARE_VARIABLE "I" AS INTEGER
PLEASE SET I TO 0

FOR_THE_PEOPLE I LESS_THAN 10 DO
    PLEASE SET Numbers[I] TO "Number " + I
    PLEASE INCREMENT I BY 1
END_FOR_THE_PEOPLE
```

**Conditional Initialization**:
```gov
PLEASE DECLARE_VARIABLE "Grid" AS ARRAY_OF_STRING SIZE 9
PLEASE DECLARE_VARIABLE "I" AS INTEGER
PLEASE SET I TO 0

FOR_THE_PEOPLE I LESS_THAN 9 DO
    IF I EQUALS 4 THEN
        PLEASE SET Grid[I] TO "center"
    ELSE
        PLEASE SET Grid[I] TO "edge"
    END_IF
    PLEASE INCREMENT I BY 1
END_FOR_THE_PEOPLE
```

### Array Limitations

**Type Restrictions**:
- Only `ARRAY_OF_STRING` type supported
- No integer arrays or mixed-type arrays
- No array of arrays (multi-dimensional arrays)

**Size Restrictions**:
- Fixed size at declaration time
- No dynamic resizing operations
- No array growth or shrinking

**Operation Restrictions**:
- No array-to-array assignment
- No array comparison operations
- No array concatenation
- No built-in array search or sort functions

**Memory Model**:
- Arrays are value types (not reference types)
- Each array element is independent
- No array aliasing or sharing

### Common Array Patterns

**Tic-Tac-Toe Board**:
```gov
PLEASE DECLARE_VARIABLE "Board" AS ARRAY_OF_STRING SIZE 9
PLEASE DECLARE_VARIABLE "I" AS INTEGER

// Initialize empty board
PLEASE SET I TO 0
FOR_THE_PEOPLE I LESS_THAN 9 DO
    PLEASE SET Board[I] TO " "
    PLEASE INCREMENT I BY 1
END_FOR_THE_PEOPLE

// Make moves
PLEASE SET Board[0] TO "X"  // Top-left
PLEASE SET Board[4] TO "O"  // Center
PLEASE SET Board[8] TO "X"  // Bottom-right
```

**Menu System**:
```gov
PLEASE DECLARE_VARIABLE "MenuItems" AS ARRAY_OF_STRING SIZE 4
PLEASE DECLARE_VARIABLE "Choice" AS INTEGER
PLEASE DECLARE_VARIABLE "I" AS INTEGER

// Setup menu
PLEASE SET MenuItems[0] TO "1. New Game"
PLEASE SET MenuItems[1] TO "2. Load Game"
PLEASE SET MenuItems[2] TO "3. Settings"
PLEASE SET MenuItems[3] TO "4. Exit"

// Display menu
PLEASE SET I TO 0
FOR_THE_PEOPLE I LESS_THAN 4 DO
    PRAISE_LEADER MenuItems[I]
    PLEASE INCREMENT I BY 1
END_FOR_THE_PEOPLE
```

**Data Storage**:
```gov
PLEASE DECLARE_VARIABLE "PlayerScores" AS ARRAY_OF_STRING SIZE 5
PLEASE DECLARE_VARIABLE "PlayerIndex" AS INTEGER

// Store scores as strings
PLEASE SET PlayerScores[0] TO "1250"
PLEASE SET PlayerScores[1] TO "980"
PLEASE SET PlayerScores[2] TO "1100"

// Access and display
PLEASE SET PlayerIndex TO 0
FOR_THE_PEOPLE PlayerIndex LESS_THAN 3 DO
    PRAISE_LEADER "Player " + PlayerIndex + " score: " + PlayerScores[PlayerIndex]
    PLEASE INCREMENT PlayerIndex BY 1
END_FOR_THE_PEOPLE
```

## Error Handling

Gov provides basic error handling through the `DENOUNCE_IMPERIALIST_ERRORS` statement:
```gov
DENOUNCE_IMPERIALIST_ERRORS "Custom error message"
```

## Program Structure

A typical Gov program follows this structure:

```gov
!I_LOVE_GOVERNMENT

OBEY_PARTY_LINE "Program description"

// Variable declarations
PLEASE DECLARE_VARIABLE "Variable1" AS INTEGER
PLEASE DECLARE_VARIABLE "Variable2" AS STRING

// Main program logic
PLEASE SET Variable1 TO 0
PRAISE_LEADER "Program starting..."

// Control flow and operations
FOR_THE_PEOPLE Variable1 LESS_THAN 5 DO
    PRAISE_LEADER "Iteration: " + Variable1
    PLEASE INCREMENT Variable1 BY 1
END_FOR_THE_PEOPLE

PRAISE_LEADER "Program completed successfully!"
```

## Examples

### Hello World
```gov
!I_LOVE_GOVERNMENT

PRAISE_LEADER "Hello, World!"
PRAISE_LEADER "Long live the Supreme Leader!"
```

### Simple Calculator
```gov
!I_LOVE_GOVERNMENT

PLEASE DECLARE_VARIABLE "FirstNumber" AS INTEGER
PLEASE DECLARE_VARIABLE "SecondNumber" AS INTEGER
PLEASE DECLARE_VARIABLE "Result" AS INTEGER

PRAISE_LEADER "Enter first number:"
PLEASE READ FirstNumber

PRAISE_LEADER "Enter second number:"
PLEASE READ SecondNumber

PLEASE SET Result TO FirstNumber + SecondNumber
PRAISE_LEADER "Sum: " + Result
```

### Counting Loop
```gov
!I_LOVE_GOVERNMENT

PLEASE DECLARE_VARIABLE "Counter" AS INTEGER
PLEASE SET Counter TO 0

FOR_THE_PEOPLE Counter LESS_THAN 5 DO
    PRAISE_LEADER "Count: " + Counter
    PLEASE INCREMENT Counter BY 1
END_FOR_THE_PEOPLE
```

### Conditional Logic
```gov
!I_LOVE_GOVERNMENT

PLEASE DECLARE_VARIABLE "Age" AS INTEGER
PRAISE_LEADER "Enter your age:"
PLEASE READ Age

IF Age LESS_THAN 18 THEN
    PRAISE_LEADER "You are too young to serve the state directly"
ELSE_IF Age LESS_THAN 65 THEN
    PRAISE_LEADER "You are of prime age to serve the people!"
ELSE
    PRAISE_LEADER "Your wisdom will guide the next generation"
END_IF
```

### Array Example
```gov
!I_LOVE_GOVERNMENT

PLEASE DECLARE_VARIABLE "Names" AS ARRAY_OF_STRING SIZE 3
PLEASE DECLARE_VARIABLE "Index" AS INTEGER

PLEASE SET Names[0] TO "Comrade Alpha"
PLEASE SET Names[1] TO "Comrade Beta"
PLEASE SET Names[2] TO "Comrade Gamma"

PLEASE SET Index TO 0
FOR_THE_PEOPLE Index LESS_THAN 3 DO
    PRAISE_LEADER "Citizen: " + Names[Index]
    PLEASE INCREMENT Index BY 1
END_FOR_THE_PEOPLE
```

## Interpreter Usage

The Gov interpreter supports several modes of operation:

### Basic Execution
```bash
gov program.gov
gov run program.gov
```

### Parse Mode (Show AST)
```bash
gov parse program.gov
```

### Debug Mode
```bash
gov debug program.gov
gov debug -v 2 program.gov          # Higher verbosity
gov debug -v 2 -s program.gov       # Step-by-step execution
```

### Command Line Options
- `-h, --help` - Show help message
- `-v, --verbose LEVEL` - Set debug verbosity (0-3)
- `-s, --step` - Enable step-by-step execution in debug mode

### Debug Levels
- **Level 0**: No debug output (default for run)
- **Level 1**: Basic execution info (default for debug)
- **Level 2**: Include token information
- **Level 3**: Maximum verbosity with detailed execution traces

## Language Features Summary

### Supported Features
- ✅ Variable declarations and assignments
- ✅ Integer and string data types
- ✅ String arrays with fixed size
- ✅ Arithmetic operations (+, -, *, /)
- ✅ Comparison operations (==, !=, <)
- ✅ Logical operations (AND, OR)
- ✅ If/else if/else statements
- ✅ For loops with increment
- ✅ While loops
- ✅ String concatenation
- ✅ Array access and assignment
- ✅ User input and output
- ✅ Line comments
- ✅ Complex boolean expressions
- ✅ Nested control structures

### Limitations
- No floating-point numbers
- No dynamic arrays or lists
- No functions or procedures
- No object-oriented features
- No file I/O operations
- No advanced string manipulation
- No exception handling beyond basic error messages

## Best Practices

1. **Always start with `!I_LOVE_GOVERNMENT`**
2. **Use descriptive variable names** that fit the theme
3. **Declare all variables before use**
4. **Use `OBEY_PARTY_LINE` for documentation**
5. **Be polite - use `PLEASE` for operations**
6. **Structure code with proper indentation**
7. **Test boundary conditions** especially with arrays
8. **Use meaningful output messages** with `PRAISE_LEADER`

## Conclusion

Gov is a unique programming language that combines functional programming capabilities with satirical political commentary. While the syntax may seem verbose and unusual, it provides all the essential features needed for basic programming tasks, making it both educational and entertaining.

The language serves as an excellent introduction to programming concepts while maintaining a humorous perspective on authority and bureaucracy. Whether you're learning programming fundamentals or just want to have fun with code, Gov offers a distinctive and memorable experience.

Remember: In Gov, every program serves the state, every variable serves the people, and every programmer serves the greater good of the collective!