# C Lexical Analyzer

**C Lexical Analyzer** is a C-based application that reads source code character by character and identifies different lexical tokens such as keywords, identifiers, constants, operators, special symbols, and comments.

The project implements a **state machine-based lexical analysis approach** to scan C source code and classify individual tokens.

It also identifies preprocessor directives, string literals, character literals, and invalid characters, reporting lexical errors when unsupported characters are encountered.

The application follows a modular programming approach, where the main program, lexical analysis logic, and token definitions are maintained in separate files.

## Features

- Reads C source code character by character.
- Identifies C keywords.
- Recognizes identifiers.
- Identifies integer and floating-point constants.
- Recognizes arithmetic operators.
- Identifies relational and logical operators.
- Detects special symbols and brackets.
- Identifies string literals.
- Identifies character literals.
- Recognizes single-line comments.
- Recognizes multi-line comments.
- Identifies preprocessor directives.
- Handles header file inclusion.
- Tracks line numbers for tokens.
- Detects invalid characters.
- Reports lexical errors.
- Uses modular C source files for better code organization.

## How It Works

The lexical analyzer reads the input C source file character by character and classifies the characters based on the current state of the analyzer.

The main processing flow is:

```text
           C Source File
                 |
                 |
          Open Input File
                 |
                 |
        Initialize Lexer State
                 |
                 |
       Read Character by Character
                 |
                 |
          Identify Token Type
                 |
        +--------+---------+
        |        |         |
      Word     Number    Symbol
        |        |         |
        |        |         |
     Keyword  Integer   Operator
        |      Constant  Special Symbol
     Identifier |
                 |
        +--------+---------+
                 |
        +--------+---------+
        |        |         |
      String  Character  Comment
        |        |         |
        +--------+---------+
                 |
        Preprocessor Directive
                 |
                 |
         Classify Token
                 |
                 |
          Print Token Table
                 |
                 |
         Report Lexical Errors
                 |
                 |
             End Program
```

The analyzer maintains different states to determine how each character should be processed.

## Types of Tokens

The lexical analyzer identifies the following token categories:

### 1. Keywords

Keywords are reserved words in the C programming language that have predefined meanings.

Examples:

```c
int
char
float
double
if
else
while
for
return
switch
case
break
```

### 2. Identifiers

Identifiers are user-defined names used for variables, functions, and other program elements.

Examples:

```c
main
count
total
result
student_name
```

### 3. Constants

The analyzer recognizes numeric constants such as integer and floating-point values.

Examples:

```c
10
25
100
3.14
10.5
```

### 4. Operators

Operators perform arithmetic, logical, relational, and other operations.

Examples:

```c
+
-
*
/
%
=
==
!=
<
>
&&
||
++
--
```

### 5. Special Symbols

Special symbols are used to define the structure and syntax of C programs.

Examples:

```c
(
)
{
}
[
]
;
,
#
```

### 6. String Literals

String literals represent sequences of characters enclosed within double quotation marks.

Example:

```c
printf("Hello World");
```

### 7. Character Literals

Character literals represent individual characters enclosed within single quotation marks.

Example:

```c
char ch = 'A';
```

### 8. Comments

The analyzer recognizes both single-line and multi-line comments.

Single-line comment:

```c
// This is a single-line comment
```

Multi-line comment:

```c
/*
   This is a multi-line comment
*/
```

### 9. Preprocessor Directives

Preprocessor directives are instructions processed before the actual compilation of a C program.

Examples:

```c
#include <stdio.h>
#define MAX 100
```

## State Machine Approach

One of the important concepts implemented in this project is a **finite state machine**.

The analyzer maintains a current state and changes its state depending on the character being processed.

For example, the analyzer can transition between states such as:

- STATE_IDLE
- STATE_WORD
- STATE_NUMBER
- STATE_STRING
- STATE_CHARACTER
- STATE_SINGLE_COMMENT
- STATE_MULTI_COMMENT
- STATE_PREPROCESSOR
- STATE_HEADER

A simplified state transition flow is:

```text
             STATE_IDLE
                 |
       +---------+---------+
       |         |         |
    Alphabet   Digit     Symbol
       |         |         |
       v         v         v
   STATE_WORD STATE_NUMBER
       |
       |
   Check Keyword
       |
       +------> Keyword
       |
       +------> Identifier
```

The state machine approach makes it easier to identify different token types while scanning the source code.

## Keyword Handling

The analyzer maintains keyword information to distinguish reserved C keywords from user-defined identifiers.

When a word is identified, it is compared against the available keyword list.

If the word matches a reserved keyword, it is classified as a keyword. Otherwise, it is classified as an identifier.

## Project Structure

```text
C-Lexical-Analyzer/
│
├── 001_main.c
│
├── 002_lexer.c
│
├── lexer.h
│
├── input.c
│
└── README.md
```

### File Description

| File | Purpose |
|---|---|
| `001_main.c` | Main function and overall program execution |
| `002_lexer.c` | Implements lexical analysis and token identification |
| `lexer.h` | Contains token definitions, structures, and function declarations |
| `input.c` | Sample C source file used as input for lexical analysis |

The repository follows a modular design where the main program, token definitions, and lexical analysis implementation are maintained separately.

## Requirements

- GCC Compiler
- Linux / Unix-like environment
- Basic C development environment

## Compilation

Clone the repository:

```bash
git clone https://github.com/sharfu18/C-Lexical-Analyzer.git
```

Move into the project directory:

```bash
cd C-Lexical-Analyzer
```

Compile the project using GCC:

```bash
gcc *.c -o lexer
```

The GCC compiler compiles all C source files and links them to generate the `lexer` executable.

## Usage

The application reads the C source code from the `input.c` file located in the current working directory.

Run the application:

```bash
./lexer
```

After successful execution, the analyzer scans the input source file and displays the identified tokens along with their corresponding line numbers and token categories.

## Example

### Input: `input.c`

```c
#include <stdio.h>

int main()
{
    int number = 10;
    float value = 3.14;

    // Display message
    printf("Hello World");

    return 0;
}
```

### Command

```bash
./lexer
```

### Output

The analyzer displays a token table containing:

- Line number
- Identified lexeme
- Corresponding token category

Example:

```text
============================================================
                    LEXICAL ANALYZER
============================================================

LINE   LEXEME               TOKEN
------------------------------------------------------------
1      #include <stdio.h>   PREPROCESSOR DIRECTIVE
3      int                  KEYWORD
3      main                 IDENTIFIER
3      (                    SPECIAL SYMBOL
3      )                    SPECIAL SYMBOL
4      {                    SPECIAL SYMBOL
5      int                  KEYWORD
5      number               IDENTIFIER
5      =                    OPERATOR
5      10                   INTEGER CONSTANT
5      ;                    SPECIAL SYMBOL
```

The output continues with the remaining tokens identified in the input file.

## Lexical Error Detection

The analyzer also identifies unsupported or invalid characters in the source code.

For example:

```c
int main()
{
    int a = 10;
    ?
    @
    return 0;
}
```

The analyzer reports invalid characters as lexical errors along with their corresponding line numbers.

This helps identify invalid lexical elements during source code analysis.

## Concepts Learned

This project helped in understanding and applying:

- C Programming
- Compiler Design Fundamentals
- Lexical Analysis
- Finite State Machines
- State Transitions
- Token Recognition
- Keyword Identification
- String and Character Processing
- File Handling
- Character-by-Character Processing
- Structures and Enumerations
- Pointers
- Conditional Statements
- Modular Programming
- Error Detection and Handling
- Multi-file C Projects

## Future Improvements

Possible enhancements include:

- Supporting additional C operators.
- Improving recognition of numeric constants.
- Handling escaped characters in string and character literals.
- Improving preprocessor directive recognition.
- Supporting more complex header file declarations.
- Improving line number tracking.
- Detecting unterminated strings and comments.
- Supporting additional C language constructs.
- Improving lexical error reporting.
- Extending the analyzer to support more programming languages.

## Author

**Shaik Sharfuddin**

---

⭐ If you find this project useful, feel free to explore the repository and provide feedback.