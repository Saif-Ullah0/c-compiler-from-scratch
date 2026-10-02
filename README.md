# C Compiler — Lexical Analyzer

A lexical analyzer (lexer/scanner) for the C programming language, written in C++17-compatible C++14.

## What It Does

Reads a C source file and produces a stream of tokens, one per line, in `TYPE LEXEME` format.

## Token Categories

| Category | Example |
|----------|---------|
| KEYWORD | `int`, `if`, `while`, `return` |
| IDENTIFIER | `main`, `count`, `myVar` |
| INT_CONST | `42`, `0xFF`, `0755` |
| FLOAT_CONST | `3.14`, `.5`, `5.`, `1.5e10`, `2.5E-3` |
| CHAR_CONST | `'A'`, `'\n'`, `'\''`, `'\\'` |
| STRING_LITERAL | `"hello"`, `"escaped \" quote"` |
| OPERATOR | `+`, `+=`, `<<=`, `==`, `&&`, `->` |
| SEPARATOR | `(`, `)`, `{`, `}`, `;`, `,`, `.` |
| PREPROCESSOR | `#include <stdio.h>` |
| COMMENT | `// single-line`, `/* multi-line */` |
| UNKNOWN | any illegal character |
| END_OF_FILE | sentinel token at end |

## Build

Requires `g++` with C++14 support (tested with MinGW GCC 6.3.0).

**Windows (Git Bash):**
cmd.exe //c build.bat

text

**Manual (any platform):**
g++ -std=c++14 -Wall -Wextra -Iinclude
src/main.cpp src/lexer/lexer.cpp src/lexer/keyword_table.cpp
src/utils/file_io.cpp -o build/compiler.exe

text

## Run
./build/compiler.exe lex <input.c> <output.txt>

text

Example:
./build/compiler.exe lex tests/lexer/sample1.c output/tokens.txt

text

## Project Structure
include/
├── common/ Token, TokenType, source location
├── lexer/ Lexer class, keyword table, char utilities
└── utils/ File I/O helpers
src/
├── lexer/ Lexer implementation
├── utils/ File I/O implementation
└── main.cpp CLI driver
tests/lexer/ Test inputs (sample1–6.c)
output/ Generated token files
docs/ Design notes, grammar

text

## Design Decisions

- **Longest-match rule:** multi-char operators (`<<=`, `+=`, `->`) are matched before shorter ones (`<`, `+`, `-`).
- **Comments recognized before operators:** `/` starts both comments and the division operator — comment check runs first in the dispatcher.
- **Keywords detected after scanning:** an identifier is scanned, then looked up in a keyword table. If found → KEYWORD; else → IDENTIFIER.
- **Position tracking in `advance()`:** line/column updates happen on every character consumption, so tokens record exact start positions.

## Test Files

| File | Tests |
|------|-------|
| sample1.c | keywords, identifiers |
| sample2.c | int, hex, octal, float constants |
| sample3.c | string and char literals with escapes |
| sample4.c | operators, separators, longest-match |
| sample5.c | comments and preprocessor |
| sample6.c | error handling for unknown characters |

## Author

Saif Ullah
GitHub: https://github.com/Saif-Ullah0/c-compiler-from-scratch