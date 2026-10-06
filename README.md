# Mini Compiler in C

A simple modular Mini Compiler developed in C to demonstrate the major phases of compiler design.

## 📌 Project Overview

This project is a beginner-friendly implementation of a compiler that accepts simple C-like statements and processes them through different compiler phases.

The compiler demonstrates how source code is converted into tokens, checked for syntax and semantic errors, converted into intermediate code, optimized, and finally converted into target-like code.

## 🚀 Compiler Phases

The project includes the following phases:

1. **Lexical Analysis**
   - Converts source code into tokens.
   - Identifies keywords, identifiers, numbers, operators, and symbols.

2. **Syntax Analysis**
   - Checks whether the input follows the correct grammar.
   - Detects errors such as missing `=`, missing `;`, and invalid expressions.

3. **Semantic Analysis**
   - Checks the meaning of the statement.
   - Checks variable declaration, duplicate variables, data types, and division by zero.

4. **Symbol Table**
   - Stores information about variables.
   - Stores variable name, data type, and expression/value.

5. **Intermediate Code Generation**
   - Generates Three Address Code (TAC).
   - Uses temporary variables such as `t1`, `t2`, etc.

6. **Code Optimization**
   - Performs simple optimization such as constant folding.
   - Example:
     `10 + 20 → 30`

7. **Target Code Generation**
   - Generates simple assembly-like instructions such as:
   `MOV`, `ADD`, `SUB`, `MUL`, and `DIV`.

8. **Error Handling**
   - Displays clear syntax and semantic error messages.

## 🛠️ Technologies Used

- C Programming Language
- GCC Compiler
- Visual Studio Code
- Git Bash
- GitHub

## 📂 Project Structure

```text
MiniCompiler/
│
├── main.c
├── lexer.c
├── lexer.h
├── syntax.c
├── syntax.h
├── semantic.c
├── semantic.h
├── symbol_table.c
├── symbol_table.h
├── intermediate.c
├── intermediate.h
├── optimizer.c
├── optimizer.h
├── codegen.c
├── codegen.h
├── error.c
└── error.h
