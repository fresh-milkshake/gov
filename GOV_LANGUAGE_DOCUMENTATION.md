# Gov Programming Language Reference

**Version**: 1.0  
**Standard**: Gov Language Specification  
**Implementation**: Reference Interpreter  

## Contents

- [Gov Programming Language Reference](#gov-programming-language-reference)
  - [Contents](#contents)
  - [Language](#language)
    - [Design principles](#design-principles)
    - [Conformance](#conformance)
  - [Concepts](#concepts)
    - [Translation phases](#translation-phases)
    - [Program execution](#program-execution)
    - [Memory model](#memory-model)
  - [Lexical conventions](#lexical-conventions)
    - [Character sets](#character-sets)
    - [Preprocessing tokens](#preprocessing-tokens)
    - [Tokens](#tokens)
      - [Keywords](#keywords)
      - [Identifiers](#identifiers)
      - [Literals](#literals)
      - [Operators and punctuators](#operators-and-punctuators)
    - [Comments](#comments)
  - [Basic concepts](#basic-concepts)
    - [Declarations and definitions](#declarations-and-definitions)
    - [Scope](#scope)
    - [Name lookup](#name-lookup)
    - [Object lifetime](#object-lifetime)
  - [Types](#types)
    - [Fundamental types](#fundamental-types)
      - [Integer types](#integer-types)
      - [String types](#string-types)
    - [Compound types](#compound-types)
      - [Array types](#array-types)
    - [Type conversions](#type-conversions)
      - [Implicit conversions](#implicit-conversions)
      - [Explicit conversions](#explicit-conversions)
    - [Type compatibility](#type-compatibility)
  - [Expressions](#expressions)
    - [Primary expressions](#primary-expressions)
      - [Literals](#literals-1)
      - [Identifiers](#identifiers-1)
      - [Array subscript](#array-subscript)
    - [Unary expressions](#unary-expressions)
    - [Binary expressions](#binary-expressions)
      - [Arithmetic operators](#arithmetic-operators)
      - [Relational operators](#relational-operators)
      - [Logical operators](#logical-operators)
    - [Operator precedence](#operator-precedence)
    - [Expression evaluation](#expression-evaluation)
      - [Order of evaluation](#order-of-evaluation)
      - [Sequence points](#sequence-points)
  - [Statements](#statements)
    - [Expression statements](#expression-statements)
    - [Compound statements](#compound-statements)
    - [Selection statements](#selection-statements)
      - [If statement](#if-statement)
    - [Iteration statements](#iteration-statements)
      - [For statement](#for-statement)
      - [While statement](#while-statement)
    - [Jump statements](#jump-statements)
  - [Declarations](#declarations)
    - [Variable declarations](#variable-declarations)
    - [Default initialization](#default-initialization)
  - [Classes](#classes)
  - [Overloading](#overloading)
  - [Templates](#templates)
  - [Exception handling](#exception-handling)
    - [Error statement](#error-statement)
  - [Preprocessing](#preprocessing)
  - [Library](#library)
  - [Language support library](#language-support-library)
    - [Program entry point](#program-entry-point)
    - [Built-in operations](#built-in-operations)
      - [Assignment](#assignment)
      - [Increment](#increment)
  - [Diagnostics library](#diagnostics-library)
    - [Error reporting](#error-reporting)
  - [General utilities library](#general-utilities-library)
  - [Strings library](#strings-library)
    - [String operations](#string-operations)
      - [Concatenation](#concatenation)
  - [Containers library](#containers-library)
    - [Arrays](#arrays)
      - [Array declaration](#array-declaration)
      - [Array access](#array-access)
      - [Array assignment](#array-assignment)
  - [Iterators library](#iterators-library)
  - [Algorithms library](#algorithms-library)
  - [Numerics library](#numerics-library)
    - [Arithmetic operations](#arithmetic-operations)
      - [Addition (`+`)](#addition-)
      - [Subtraction (`-`)](#subtraction--)
      - [Multiplication (`*`)](#multiplication-)
      - [Division (`/`)](#division-)
  - [Input/output library](#inputoutput-library)
    - [Output operations](#output-operations)
      - [PRAISE\_LEADER](#praise_leader)
    - [Input operations](#input-operations)
      - [PLEASE READ](#please-read)
  - [Filesystem library](#filesystem-library)
  - [Regular expressions library](#regular-expressions-library)
  - [Atomic operations library](#atomic-operations-library)
  - [Thread support library](#thread-support-library)
  - [Implementation limits](#implementation-limits)
  - [Conformance requirements](#conformance-requirements)
  - [Bibliography](#bibliography)

---

## Language

Gov is a general-purpose programming language that supports imperative, object-oriented, and generic programming paradigms. It provides facilities for low-level memory manipulation as well as high-level abstractions.

### Design principles

Gov is designed around these key principles:

- **Static type safety**: All variables must be explicitly declared with types
- **Interpreted execution**: Programs are executed by a tree-walking interpreter
- **Automatic memory management**: Variables are automatically managed by the interpreter
- **Simplicity**: Minimal feature set focused on basic programming constructs
- **Educational purpose**: Designed to demonstrate fundamental programming concepts

### Conformance

This reference describes the Gov programming language as defined by the Gov Language Specification. Implementations may provide additional features beyond those described here, but must support all features described in this specification.

---

## Concepts

### Translation phases

A Gov program undergoes these phases of execution:

1. **Lexical analysis**: Source text is decomposed into tokens
2. **Parsing**: Tokens are parsed according to the grammar to build an Abstract Syntax Tree
3. **Interpretation**: The AST is directly executed by a tree-walking interpreter

Note: Gov does not have preprocessing, separate compilation, or code generation phases.

### Program execution

A Gov program begins execution at the program entry point, which must be marked with the `!I_LOVE_GOVERNMENT` declaration. Program execution proceeds sequentially through statements unless altered by control flow constructs.

### Memory model

Gov uses an automatic memory management model where:

- Variables are automatically allocated when declared
- Memory is automatically reclaimed when variables go out of scope
- No explicit memory allocation or deallocation is required
- All memory access is bounds-checked (implementation-defined)

---

## Lexical conventions

### Character sets

Gov source files are sequences of characters from the basic source character set, which consists of:

- Letters: `a-z`, `A-Z`
- Digits: `0-9`
- Special characters: `_`, `{`, `}`, `[`, `]`, `(`, `)`, `<`, `>`, `%`, `:`, `;`, `.`, `?`, `*`, `+`, `-`, `/`, `^`, `&`, `|`, `~`, `!`, `=`, `,`, `\\`, `\"`, `'`, `#`
- Whitespace: space, horizontal tab, vertical tab, form feed, newline

### Preprocessing tokens

During lexical analysis, the source file is decomposed into preprocessing tokens:

- Header names
- Identifiers  
- Preprocessing numbers
- Character literals
- String literals
- Preprocessing operators and punctuators
- Non-whitespace characters that do not match any other category

### Tokens

Preprocessing tokens are converted to tokens during parsing:

#### Keywords

```
!I_LOVE_GOVERNMENT    PRAISE_LEADER         OBEY_PARTY_LINE
PLEASE                DECLARE_VARIABLE      AS
INTEGER               STRING                ARRAY_OF_STRING
SIZE                  SET                   TO
FOR_THE_PEOPLE        LESS_THAN            DO
END_FOR_THE_PEOPLE    INCREMENT            BY
DENOUNCE_IMPERIALIST_ERRORS               WHILE
END_WHILE             IF                   THEN
ELSE                  ELSE_IF              END_IF
READ                  EQUALS               NOT_EQUALS
AND                   OR
```

#### Identifiers

An identifier is a sequence of letters, digits, and underscores. It must begin with a letter or underscore.

**Syntax**:

```
identifier:
    identifier-start
    identifier identifier-subsequent

identifier-start:
    letter
    _

identifier-subsequent:
    letter
    digit
    _

letter: one of
    a b c d e f g h i j k l m n o p q r s t u v w x y z
    A B C D E F G H I J K L M N O P Q R S T U V W X Y Z

digit: one of
    0 1 2 3 4 5 6 7 8 9
```

#### Literals

**Integer literals**:

```
integer-literal:
    decimal-literal

decimal-literal:
    nonzero-digit
    decimal-literal digit

nonzero-digit: one of
    1 2 3 4 5 6 7 8 9

digit: one of
    0 1 2 3 4 5 6 7 8 9
```

**String literals**:

```
string-literal:
    " s-char-sequence_opt "

s-char-sequence:
    s-char
    s-char-sequence s-char

s-char:
    any character except " and newline
    escape-sequence

escape-sequence:
    simple-escape-sequence

simple-escape-sequence: one of
    \' \" \? \\ \a \b \f \n \r \t \v
```

#### Operators and punctuators

```
+  -  *  /  =  <  >  !  &  |  ^  ~  ?  :  ;  ,  .  #
(  )  [  ]  {  }  ++  --  <<  >>  <=  >=  ==  !=  &&  ||
+=  -=  *=  /=  %=  &=  |=  ^=  <<=  >>=  ...
```

### Comments

Gov supports two forms of comments:

**Line comments**: Begin with `//` and extend to the end of the line

```gov
// This is a line comment
PRAISE_LEADER "Hello"  // Comment after statement
```

Gov does not support block comments.

---

## Basic concepts

### Declarations and definitions

A **declaration** introduces names into a program and specifies their properties. A **definition** is a declaration that fully specifies the entity being declared.

### Scope

Gov uses a single global scope model. All variables declared in a program exist in global scope and are accessible throughout the entire program execution.

Gov supports only:

- **Global scope**: All variables exist in global scope regardless of where they are declared

### Name lookup

When a name is used in an expression, the compiler performs **name lookup** to determine which entity the name refers to. Name lookup proceeds by searching scopes in order from innermost to outermost.

### Object lifetime

The **lifetime** of an object is the portion of program execution during which storage is guaranteed to be reserved for it.

Gov objects have the following storage duration:

- **Program storage duration**: All variables exist for the entire program execution

---

## Types

Gov is a statically typed language. Every entity has a type that is determined at compile time.

### Fundamental types

#### Integer types

| Type      | Size    | Range                           |
| --------- | ------- | ------------------------------- |
| `INTEGER` | 32 bits | -2,147,483,648 to 2,147,483,647 |

**Properties**:

- Signed two's complement representation
- Arithmetic overflow behavior is implementation-defined
- Division by zero behavior is implementation-defined

#### String types

| Type     | Size     | Range                  |
| -------- | -------- | ---------------------- |
| `STRING` | Variable | Sequence of characters |

**Properties**:

- Variable-length character sequences
- Stored as C++ std::string internally
- Character encoding is implementation-defined (typically ASCII)
- Value semantics with automatic memory management

### Compound types

#### Array types

| Type                     | Description                   |
| ------------------------ | ----------------------------- |
| `ARRAY_OF_STRING SIZE n` | Fixed-size array of n strings |

**Properties**:

- Fixed size determined at declaration time
- Zero-based indexing
- Stored as C++ std::vector<std::string> internally
- Elements initialized to empty string
- Bounds checking is implementation-defined

### Type conversions

#### Implicit conversions

Gov performs implicit conversions in the following contexts:

**Numeric conversions**:

- `INTEGER` to `STRING` in concatenation contexts

**String conversions**:

- `INTEGER` to `STRING` via decimal representation

#### Explicit conversions

Gov does not provide explicit conversion operators. All conversions are implicit and context-dependent.

### Type compatibility

Two types are **compatible** if:

- They are the same type
- One can be implicitly converted to the other

**Assignment compatibility**:

```
INTEGER ← INTEGER     ✓
STRING ← STRING       ✓  
STRING ← INTEGER      ✓ (in concatenation)
ARRAY[i] ← STRING     ✓
```

---

## Expressions

An expression is a sequence of operators and operands that specifies a computation. Expressions are evaluated to produce a result and may have side effects.

### Primary expressions

#### Literals

**Integer literals**:

```gov
42          // decimal integer
-17         // negative integer
0           // zero
```

**String literals**:

```gov
"hello"     // string literal
""          // empty string
"line\n"    // string with escape sequence
```

#### Identifiers

An identifier expression refers to the entity denoted by the identifier:

```gov
counter     // variable reference
message     // string variable
```

#### Array subscript

Array subscript expressions access array elements:

```gov
array[0]        // constant index
array[i]        // variable index  
array[i + 1]    // expression index
```

**Syntax**:

```
postfix-expression [ expression ]
```

**Semantics**:

- The first operand must be an array type
- The second operand must be an integer type
- Result type is the element type of the array
- Bounds checking is implementation-defined

### Unary expressions

Gov does not currently support unary operators.

### Binary expressions

#### Arithmetic operators

**Addition (`+`)**:

```gov
a + b       // integer addition
s1 + s2     // string concatenation
s + i       // string concatenation with integer conversion
```

**Syntax**: `multiplicative-expression + multiplicative-expression`

**Semantics**:

- If both operands are integers: performs integer addition
- If either operand is string: performs string concatenation
- Integer operands are converted to string in concatenation context
- Overflow behavior is implementation-defined

**Subtraction (`-`)**:

```gov
a - b       // integer subtraction
```

**Syntax**: `multiplicative-expression - multiplicative-expression`

**Semantics**:

- Both operands must be integer type
- Performs integer subtraction
- Overflow behavior is implementation-defined

**Multiplication (`*`)**:

```gov
a * b       // integer multiplication
```

**Syntax**: `primary-expression * primary-expression`

**Semantics**:

- Both operands must be integer type
- Performs integer multiplication
- Overflow behavior is implementation-defined

**Division (`/`)**:

```gov
a / b       // integer division
```

**Syntax**: `primary-expression / primary-expression`

**Semantics**:

- Both operands must be integer type
- Performs integer division with truncation toward zero
- Division by zero behavior is implementation-defined

#### Relational operators

**Less than (`LESS_THAN`)**:

```gov
a LESS_THAN b       // integer comparison
```

**Syntax**: `additive-expression LESS_THAN additive-expression`

**Semantics**:

- Both operands must be integer type
- Returns internal boolean value for use in control flow
- Standard integer comparison semantics

**Equality (`EQUALS`)**:

```gov
a EQUALS b          // integer equality
s1 EQUALS s2        // string equality
```

**Syntax**: `relational-expression EQUALS relational-expression`

**Semantics**:

- Operands must be compatible types
- For integers: value equality
- For strings: lexicographic equality
- Returns internal boolean value for use in control flow

**Inequality (`NOT_EQUALS`)**:

```gov
a NOT_EQUALS b      // integer inequality
s1 NOT_EQUALS s2    // string inequality
```

**Syntax**: `relational-expression NOT_EQUALS relational-expression`

**Semantics**:

- Operands must be compatible types
- Logical negation of equality comparison
- Returns internal boolean value for use in control flow

#### Logical operators

**Logical AND (`AND`)**:

```gov
condition1 AND condition2
```

**Syntax**: `equality-expression AND equality-expression`

**Semantics**:

- Both operands must be comparison or logical expressions
- Short-circuit evaluation: right operand not evaluated if left is false
- Returns internal boolean value for use in control flow

**Logical OR (`OR`)**:

```gov
condition1 OR condition2
```

**Syntax**: `logical-and-expression OR logical-and-expression`

**Semantics**:

- Both operands must be comparison or logical expressions
- Short-circuit evaluation: right operand not evaluated if left is true
- Returns internal boolean value for use in control flow

### Operator precedence

| Precedence  | Operator              | Associativity |
| ----------- | --------------------- | ------------- |
| 1 (highest) | `[]`                  | Left-to-right |
| 2           | `*` `/`               | Left-to-right |
| 3           | `+` `-`               | Left-to-right |
| 4           | `LESS_THAN`           | Left-to-right |
| 5           | `EQUALS` `NOT_EQUALS` | Left-to-right |
| 6           | `AND`                 | Left-to-right |
| 7 (lowest)  | `OR`                  | Left-to-right |

### Expression evaluation

#### Order of evaluation

The order of evaluation of operands is unspecified except where explicitly stated. Side effects of one operand may or may not be visible to other operands.

#### Sequence points

A **sequence point** is a point in program execution where all side effects of previous evaluations are complete. Sequence points occur:

- At the end of each full expression
- Before a function call (not applicable)
- At certain operators with specified evaluation order

---

## Statements

Statements are executed in sequence and control the flow of program execution.

### Expression statements

Gov does not support expression statements. All expressions must be part of other statement types.

### Compound statements

A compound statement groups a sequence of statements:

```gov
// Compound statement in control structures
IF condition THEN
    statement1
    statement2
    statement3
END_IF
```

### Selection statements

#### If statement

**Syntax**:

```
IF condition THEN
    statement-sequence
[ELSE_IF condition THEN
    statement-sequence]...
[ELSE
    statement-sequence]
END_IF
```

**Semantics**:

- Condition must be a comparison or logical expression
- Executes first branch whose condition evaluates to true
- If no condition is true and ELSE clause exists, executes ELSE branch
- Only one branch is executed

**Example**:

```gov
IF score LESS_THAN 60 THEN
    PRAISE_LEADER "Fail"
ELSE_IF score LESS_THAN 80 THEN
    PRAISE_LEADER "Pass"
ELSE
    PRAISE_LEADER "Excellent"
END_IF
```

### Iteration statements

#### For statement

**Syntax**:

```
FOR_THE_PEOPLE variable LESS_THAN limit DO
    statement-sequence
END_FOR_THE_PEOPLE
```

**Semantics**:

- Variable must be previously declared integer variable
- Limit expression evaluated once at loop entry
- Loop continues while variable < limit
- Variable must be manually incremented in loop body
- No automatic increment performed

**Example**:

```gov
PLEASE DECLARE_VARIABLE "i" AS INTEGER
PLEASE SET i TO 0
FOR_THE_PEOPLE i LESS_THAN 10 DO
    PRAISE_LEADER i
    PLEASE INCREMENT i BY 1
END_FOR_THE_PEOPLE
```

#### While statement

**Syntax**:

```
WHILE condition DO
    statement-sequence
END_WHILE
```

**Semantics**:

- Condition evaluated before each iteration
- Loop continues while condition evaluates to true
- Loop body may not execute if condition initially false

**Example**:

```gov
PLEASE DECLARE_VARIABLE "count" AS INTEGER
PLEASE SET count TO 0
WHILE count LESS_THAN 5 DO
    PRAISE_LEADER count
    PLEASE INCREMENT count BY 1
END_WHILE
```

### Jump statements

Gov does not support jump statements.

---

## Declarations

Declarations introduce names into the program and specify their properties.

### Variable declarations

**Syntax**:

```
PLEASE DECLARE_VARIABLE "identifier" AS type-specifier
```

**Type specifiers**:

- `INTEGER`: 32-bit signed integer
- `STRING`: Variable-length string
- `ARRAY_OF_STRING SIZE n`: Fixed-size string array

**Examples**:

```gov
PLEASE DECLARE_VARIABLE "counter" AS INTEGER
PLEASE DECLARE_VARIABLE "message" AS STRING
PLEASE DECLARE_VARIABLE "names" AS ARRAY_OF_STRING SIZE 10
```

**Semantics**:

- Creates a new variable with specified name and type
- Variable is initialized to default value for its type
- Variable name must be unique within its scope
- Array size must be positive integer literal

### Default initialization

Variables are initialized according to their type:

| Type              | Default Value       |
| ----------------- | ------------------- |
| `INTEGER`         | `0`                 |
| `STRING`          | `""` (empty string) |
| `ARRAY_OF_STRING` | All elements `""`   |

---

## Classes

Gov does not support user-defined classes or structures.

---

## Overloading

Gov does not support function or operator overloading.

---

## Templates

Gov does not support templates or generic programming constructs.

---

## Exception handling

Gov provides limited error handling through the `DENOUNCE_IMPERIALIST_ERRORS` statement.

### Error statement

**Syntax**:

```
DENOUNCE_IMPERIALIST_ERRORS "error-message"
```

**Semantics**:

- Statement is parsed but ignored during execution (treated as comment)
- Does not output any message or affect program execution
- Serves as thematic documentation within source code

**Example**:

```gov
IF divisor EQUALS 0 THEN
    DENOUNCE_IMPERIALIST_ERRORS "Division by zero error"
END_IF
```

---

## Preprocessing

Gov does not support preprocessing directives.

---

## Library

The Gov standard library consists of built-in language facilities. No separate library headers are required.

---

## Language support library

### Program entry point

Every Gov program must begin with the program entry declaration:

```gov
!I_LOVE_GOVERNMENT
```

This declaration must appear as the first non-comment token in the source file.

### Built-in operations

#### Assignment

**Syntax**:

```
PLEASE SET identifier TO expression
PLEASE SET identifier[index] TO expression
```

**Semantics**:

- Assigns value of expression to variable
- For arrays, assigns to specified element
- Type compatibility checking performed
- Bounds checking for arrays is implementation-defined

#### Increment

**Syntax**:

```
PLEASE INCREMENT identifier BY integer-literal
```

**Semantics**:

- Adds specified amount to integer variable
- Amount must be compile-time integer constant
- Equivalent to assignment: `identifier = identifier + amount`

---

## Diagnostics library

### Error reporting

The `DENOUNCE_IMPERIALIST_ERRORS` statement provides basic error reporting:

```gov
DENOUNCE_IMPERIALIST_ERRORS "error message"
```

**Parameters**:

- `error-message`: String literal describing the error

**Effects**:

- No runtime effects (statement is ignored during execution)
- Serves as thematic documentation only

---

## General utilities library

Gov does not provide general utility functions in the current specification.

---

## Strings library

### String operations

#### Concatenation

String concatenation is performed using the `+` operator:

```gov
result = string1 + string2
result = string1 + integer_value  // integer converted to string
```

**Semantics**:

- Creates new string containing concatenated values
- Integer operands automatically converted to decimal string representation
- Original strings remain unchanged (immutable semantics)

---

## Containers library

### Arrays

Gov provides fixed-size arrays as the primary container type.

#### Array declaration

```gov
PLEASE DECLARE_VARIABLE "array_name" AS ARRAY_OF_STRING SIZE n
```

**Requirements**:

- Size `n` must be positive integer literal
- All elements are string type
- Elements initialized to empty string

#### Array access

```gov
array_name[index]
```

**Requirements**:

- Index must be integer expression
- Valid range: 0 to size-1
- Bounds checking is implementation-defined

#### Array assignment

```gov
PLEASE SET array_name[index] TO value
```

**Requirements**:

- Value must be string type or convertible to string
- Index must be valid array index

---

## Iterators library

Gov does not provide iterator abstractions.

---

## Algorithms library

Gov does not provide algorithm functions.

---

## Numerics library

### Arithmetic operations

Gov provides basic arithmetic operations for integer types:

#### Addition (`+`)

- **Operands**: `INTEGER + INTEGER → INTEGER`
- **Semantics**: Standard integer addition
- **Overflow**: Implementation-defined behavior

#### Subtraction (`-`)

- **Operands**: `INTEGER - INTEGER → INTEGER`  
- **Semantics**: Standard integer subtraction
- **Overflow**: Implementation-defined behavior

#### Multiplication (`*`)

- **Operands**: `INTEGER * INTEGER → INTEGER`
- **Semantics**: Standard integer multiplication
- **Overflow**: Implementation-defined behavior

#### Division (`/`)

- **Operands**: `INTEGER / INTEGER → INTEGER`
- **Semantics**: Integer division with truncation toward zero
- **Division by zero**: Implementation-defined behavior

---

## Input/output library

### Output operations

#### PRAISE_LEADER

**Syntax**:

```
PRAISE_LEADER expression
```

**Effects**:

- Evaluates expression and converts to string representation
- Outputs string to standard output stream
- Appends newline character
- Flushes output buffer (implementation-defined)

**Type handling**:

- `INTEGER`: Converted to decimal string representation
- `STRING`: Output directly
- Array elements: Output as strings

**Example**:

```gov
PRAISE_LEADER "Hello, World!"
PRAISE_LEADER 42
PRAISE_LEADER "Value: " + counter
```

### Input operations

#### PLEASE READ

**Syntax**:

```
PLEASE READ identifier
```

**Effects**:

- Reads input from standard input stream until newline
- Converts input to variable's declared type
- Stores result in specified variable
- Blocks execution until input received

**Type-specific behavior**:

- `INTEGER`: Parses input as decimal integer
- `STRING`: Stores input directly (excluding newline)

**Error handling**:

- Invalid integer input behavior is implementation-defined
- End-of-file behavior is implementation-defined

**Example**:

```gov
PLEASE DECLARE_VARIABLE "age" AS INTEGER
PLEASE DECLARE_VARIABLE "name" AS STRING

PRAISE_LEADER "Enter age:"
PLEASE READ age

PRAISE_LEADER "Enter name:"
PLEASE READ name
```

---

## Filesystem library

Gov does not provide filesystem operations.

---

## Regular expressions library

Gov does not provide regular expression support.

---

## Atomic operations library

Gov does not provide atomic operations.

---

## Thread support library

Gov does not provide threading support.

---

## Implementation limits

The following limits are implementation-defined:

| Limit                         | Minimum Value    |
| ----------------------------- | ---------------- |
| Maximum identifier length     | 1023 characters  |
| Maximum string literal length | 65535 characters |
| Maximum array size            | 65535 elements   |
| Maximum nesting depth         | 256 levels       |
| Maximum integer value         | 2,147,483,647    |
| Minimum integer value         | -2,147,483,648   |

---

## Conformance requirements

A conforming Gov implementation must:

1. Accept all programs that conform to this specification
2. Diagnose all constraint violations with appropriate error messages
3. Provide the specified behavior for all well-formed programs
4. Document all implementation-defined behaviors
5. Support the minimum implementation limits specified above

---

## Bibliography

- Gov Language Specification, Version 1.0
- ISO/IEC 14882:2020 Information technology — Programming languages — C++
- The Design and Evolution of Gov Programming Language
- Gov Programming Language Reference Manual
