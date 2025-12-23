<!-- =========================================================================================
                                     HEADER SECTION
     ========================================================================================= -->
<div align="center">

  # System Software Lab

  ### CSL602 · Semester VI · Computer Engineering

  [![Curated by](https://img.shields.io/badge/Curated%20by-Amey%20Thakur-blue.svg)](https://github.com/Amey-Thakur)
  [![Documents](https://img.shields.io/badge/Documents-10-yellowgreen.svg)](#laboratory-experiments)
  [![Language](https://img.shields.io/badge/Language-C%20%7C%20LEX%20%7C%20YACC-blueviolet.svg)](./)

  **A comprehensive collection of laboratory experiments for System Programming and Compiler Construction, covering language processors, assemblers, macro processors, linkers, loaders, and compiler design tools.**

  ---

  **[🛠️ Exp 1](#-experiment-1-symbol-table-implementation)** &nbsp;·&nbsp; **[🔍 Exp 2](#-experiment-2-lexical-analysis)** &nbsp;·&nbsp; **[🏗️ Exp 3](#-experiment-3-parsing-techniques)** &nbsp;·&nbsp; **[🚦 Exp 4](#-experiment-4-intermediate-code-generation)** &nbsp;·&nbsp; **[⚙️ Exp 5](#-experiment-5-code-optimization)** &nbsp;·&nbsp; **[📝 Exp 6](#-experiment-6-target-code-generation)** &nbsp;·&nbsp; **[🧩 Exp 7](#-experiment-7-assembler-pass-i)** &nbsp;·&nbsp; **[🔄 Exp 8](#-experiment-8-assembler-pass-ii)** &nbsp;·&nbsp; **[🔗 Exp 9](#-experiment-9-macro-processor)** &nbsp;·&nbsp; **[🛠️ Exp 10](#-experiment-10-yacc--lex-tools)**

</div>

---

<!-- =========================================================================================
                                     OVERVIEW SECTION
     ========================================================================================= -->
## 📝 Laboratory Overview

The **System Software Laboratory (CSL602)** focuses on the design and implementation of fundamental language processors. This lab covers the entire spectrum of software translation, from lexical analysis to target code generation.

### 🎯 Key Learning Objectives
- **Scanner & Parser Design**: Building automated tools using **LEX** and **YACC**.
- **Assembler Design**: Understanding two-pass translation for SIC architecture.
- **Compiler Optimization**: Implementing techniques like constant folding and dead code elimination.
- **Code Generation**: Mapping high-level logic to low-level assembly instructions.

---

<!-- =========================================================================================
                                     HOW TO RUN SECTION
     ========================================================================================= -->
## 🚀 How to Run

### Prerequisites
Ensure you have the following tools installed on your system:
- **GCC**: C Compiler (`sudo apt install build-essential`)
- **Flex**: Fast Lexical Analyzer Generator (`sudo apt install flex`)
- **Bison**: Parser Generator for YACC (`sudo apt install bison`)

### Compilation Commands

#### Standard C Programs (Exp 1, 3-9)
```bash
# Navigate to source directory
cd "Experiment-X/Source Code"

# Compile
gcc Program_Name.c -o Program_Name

# Execute
./Program_Name
```

#### LEX Programs (Exp 2, 10)
```bash
# Generate C source from LEX
flex Lex_File.l

# Compile with LEX library link
gcc lex.yy.c -o Scanner -lfl

# Execute
./Scanner
```

---

<!-- =========================================================================================
                                     EXPERIMENT 1
     ========================================================================================= -->
## 🛠️ Experiment 1: Symbol Table Implementation

Implementation of Symbol Table using C to manage identifiers and their properties.

| Format | Document | Description | Link |
|:---:|:---|:---|:-:|
| 📄 | [Lab Report](Experiment-1/Amey_B-50_SPCC_Lab_Experiment-1.pdf) | Detailed experiment report | [View](Experiment-1/Amey_B-50_SPCC_Lab_Experiment-1.pdf) |
| 💻 | [Source Code](Experiment-1/Source Code/DFA_Implementation.c) | C implementation for DFA acceptance | [View](Experiment-1/Source Code/DFA_Implementation.c) |

<details>
<summary><b>🔍 Technical Logic Overview</b></summary>

The DFA (Deterministic Finite Automata) implementation simulates string recognition for a specific regular language.
- **Transition Mapping**: Uses an enumeration for states and a switch-case transition table.
- **State Selection**: Iterates through the input string, updating the `current_state` based on defined rules.
- **Acceptance Logic**: Returns true only if the final state matches the defined 'Accept State' after processing the entire input.
</details>

---

<!-- =========================================================================================
                                     EXPERIMENT 2
     ========================================================================================= -->
## 🔍 Experiment 2: Lexical Analysis

Scanner development using LEX tool to identify tokens in a source program.

| Format | Document | Description | Link |
|:---:|:---|:---|:-:|
| 📄 | [Lab Report](Experiment-2/Amey_B-50_SPCC_Lab_Experiment-2.pdf) | Detailed experiment report | [View](Experiment-2/Amey_B-50_SPCC_Lab_Experiment-2.pdf) |
| 💻 | [LEX Source](Experiment-2/Source Code/Lex_Lexical_Analyzer.l) | LEX implementation for scanner | [View](Experiment-2/Source Code/Lex_Lexical_Analyzer.l) |
| 💻 | [Manual Source](Experiment-2/Source Code/Manual_Lexical_Analyzer.c) | Manual C implementation for scanner | [View](Experiment-2/Source Code/Manual_Lexical_Analyzer.c) |
| 📄 | [Sample Input](Experiment-2/Source Code/sample_input.c) | Test C file for analysis | [View](Experiment-2/Source Code/sample_input.c) |

<details>
<summary><b>🔍 Technical Logic Overview</b></summary>

This experiment involves both automated (LEX) and manual (C) approaches to token identification.
- **LEX Approach**: Defines regular expressions for keywords, operators, and identifiers. The LEX engine performs character matching and executes associated C actions.
- **Manual Approach**: Reads the source file character-by-character, using buffers to group characters into lexemes and logic to classify them (Keywords vs. Identifiers).
- **Comment Handling**: Both implementations include robust logic to ignore multi-line C-style comments.
</details>

---

<!-- =========================================================================================
                                     EXPERIMENT 3
     ========================================================================================= -->
## 🏗️ Experiment 3: Parsing Techniques

Implementation of FIRST and FOLLOW sets calculation for syntax analysis of grammars.

| Format | Document | Description | Link |
|:---:|:---|:---|:-:|
| 📄 | [Lab Report](Experiment-3/Amey_B-50_SPCC_Lab_Experiment-3.pdf) | Detailed experiment report | [View](Experiment-3/Amey_B-50_SPCC_Lab_Experiment-3.pdf) |
| 💻 | [Source Code](Experiment-3/Source Code/First_Follow_Implementation.c) | C implementation for FIRST & FOLLOW | [View](Experiment-3/Source Code/First_Follow_Implementation.c) |
| 📄 | [Grammar File](Experiment-3/Source Code/grammar.txt) | Input grammar for calculation | [View](Experiment-3/Source Code/grammar.txt) |

<details>
<summary><b>🔍 Technical Logic Overview</b></summary>

Recursive computation of FIRST and FOLLOW sets for context-free grammars.
- **FIRST Logic**: For a non-terminal $A$, it recursively finds the first terminals produced by any of $A$'s productions.
- **FOLLOW Logic**: For a non-terminal $B$, it looks for $B$ in the RHS of all productions and applies rules to inherit terminals from either the subsequent symbol or the parent's FOLLOW set.
- **Set Management**: Uses string-based sets with duplicate prevention to ensure mathematical accuracy.
</details>

---

<!-- =========================================================================================
                                     EXPERIMENT 4
     ========================================================================================= -->
## 🚦 Experiment 4: Intermediate Code Generation

Implementation of Recursive Descent Parser for syntax analysis of grammars.

| Format | Document | Description | Link |
|:---:|:---|:---|:-:|
| 📄 | [Lab Report](Experiment-4/Amey_B-50_SPCC_Lab_Experiment-4.pdf) | Detailed experiment report | [View](Experiment-4/Amey_B-50_SPCC_Lab_Experiment-4.pdf) |
| 💻 | [Source Code](Experiment-4/Source Code/RD_Parser_Implementation.c) | C implementation for RD Parser | [View](Experiment-4/Source Code/RD_Parser_Implementation.c) |

<details>
<summary><b>🔍 Technical Logic Overview</b></summary>

A top-down parser that uses a set of recursive functions to validate arithmetic expressions.
- **Function Mapping**: Each non-terminal in the grammar is mapped to a C function (e.g., `E()`, `T()`, `F()`).
- **Lookahead Token**: Maintains a `lookahead` variable to decide which production rule to expand.
- **Predictive Matching**: The `match()` function verifies if the current token satisfies expectations before advancing the scanner.
</details>

---

<!-- =========================================================================================
                                     EXPERIMENT 5
     ========================================================================================= -->
## ⚙️ Experiment 5: Code Optimization

Implementation of constant folding and common sub-expression elimination techniques.

| Format | Document | Description | Link |
|:---:|:---|:---|:-:|
| 📄 | [Lab Report](Experiment-5/Amey_B-50_SPCC_Lab_Experiment-5.pdf) | Detailed experiment report | [View](Experiment-5/Amey_B-50_SPCC_Lab_Experiment-5.pdf) |
| 💻 | [Source Code](Experiment-5/Source Code/Code_Optimization.c) | C implementation for optimizations | [View](Experiment-5/Source Code/Code_Optimization.c) |

<details>
<summary><b>🔍 Technical Logic Overview</b></summary>

Optimization logic focused on reducing redundant operations and eliminating unreachable code.
- **Dead Code Elimination**: Analyzes variable usage from the bottom up; code that computes a value never subsequently read is flagged and removed.
- **Common Subexpression Elimination**: Identifies repeated RHS expressions and replaces subsequent occurrences with the result of the first, reducing CPU cycles.
</details>

---

<!-- =========================================================================================
                                     EXPERIMENT 6
     ========================================================================================= -->
## 📝 Experiment 6: Target Code Generation

Implementation of Target Code Generation logic including MOV and arithmetic instructions.

| Format | Document | Description | Link |
|:---:|:---|:---|:-:|
| 📄 | [Lab Report](Experiment-6/Amey_B-50_SPCC_Lab_Experiment-6.pdf) | Detailed experiment report | [View](Experiment-6/Amey_B-50_SPCC_Lab_Experiment-6.pdf) |
| 💻 | [Source Code](Experiment-6/Source Code/Target_Code_Generator.c) | C implementation for Target Code Generation | [View](Experiment-6/Source Code/Target_Code_Generator.c) |

<details>
<summary><b>🔍 Technical Logic Overview</b></summary>

Translates intermediate operations into pseudo-assembly for a destination CPU.
- **Instruction Mapping**: Maps high-level operations (+, -, *) to machine commands (ADD, SUB, MUL).
- **Register Allocation**: Simulates loading identifiers into registers (R1, R2) via MOV before performing arithmetic.
- **Result Commitment**: Transfers the computed register value back into a memory location.
</details>

---

<!-- =========================================================================================
                                     EXPERIMENT 7
     ========================================================================================= -->
## 🧩 Experiment 7: Assembler PASS-I

Design and implementation of Pass-I Assembler to generate Symbol Table and calculate program length.

| Format | Document | Description | Link |
|:---:|:---|:---|:-:|
| 📄 | [Lab Report](Experiment-7/Amey_B-50_SPCC_Lab_Experiment-7.pdf) | Detailed experiment report | [View](Experiment-7/Amey_B-50_SPCC_Lab_Experiment-7.pdf) |
| 💻 | [Source Code](Experiment-7/Source Code/Assembler_Pass1.c) | C implementation for Assembler PASS-I | [View](Experiment-7/Source Code/Assembler_Pass1.c) |

<details>
<summary><b>🔍 Technical Logic Overview</b></summary>

First stage of a multi-pass assembler focused on memory allocation.
- **LC Management**: Tracks the Location Counter, incrementing by 3 for SIC instructions or by specific sizes for RESW/BYTE.
- **Symbol Definition**: Extracts labels and records their absolute addresses in a persistent Symbol Table (SYMTAB).
- **Opcode Check**: Validates mnemonics against the Machine Operation Table (OPTAB) to ensure syntax correctness.
</details>

---

<!-- =========================================================================================
                                     EXPERIMENT 8
     ========================================================================================= -->
## 🔄 Experiment 8: Assembler PASS-II

Design and implementation of Pass-II Assembler to generate Object Code (H, T, E records).

| Format | Document | Description | Link |
|:---:|:---|:---|:-:|
| 📄 | [Lab Report](Experiment-8/Amey_B-50_SPCC_Lab_Experiment-8.pdf) | Detailed experiment report | [View](Experiment-8/Amey_B-50_SPCC_Lab_Experiment-8.pdf) |
| 💻 | [Source Code](Experiment-8/Source Code/Assembler_Pass2.c) | C implementation for Assembler PASS-II | [View](Experiment-8/Source Code/Assembler_Pass2.c) |

<details>
<summary><b>🔍 Technical Logic Overview</b></summary>

Final stage of assembly that synthesizes the executable machine code.
- **Symbol Resolution**: Lookups operand labels in the SYMTAB (generated in Pass-I) to fetch their numeric addresses.
- **Code Synthesis**: Combines Opcodes with resolved addresses to create binary/hex instruction strings.
- **Record Generation**: Sequences the output into SIC Header (H), Text (T), and End (E) records for the loader.
</details>

---

<!-- =========================================================================================
                                     EXPERIMENT 9
     ========================================================================================= -->
## 🔗 Experiment 9: Macro Processor

Simulation of a one-pass Macro Processor handling definition and expansion.

| Format | Document | Description | Link |
|:---:|:---|:---|:-:|
| 📄 | [Lab Report](Experiment-9/Amey_B-50_SPCC_Lab_Experiment-9.pdf) | Detailed experiment report | [View](Experiment-9/Amey_B-50_SPCC_Lab_Experiment-9.pdf) |
| 💻 | [Source Code](Experiment-9/Source Code/Macro_Processor.c) | C implementation for Macro Processor | [View](Experiment-9/Source Code/Macro_Processor.c) |

<details>
<summary><b>🔍 Technical Logic Overview</b></summary>

A one-pass processor that handles macro definitions and subsequent calls.
- **NAMTAB/DEFTAB Management**: Stores macro names and their full body instructions in dedicated data structures.
- **Expansion Logic**: When a macro name is detected in the source, it is replaced by the stored instructions from DEFTAB.
- **Argument Handling**: Supports simple parameter substitution during the expansion phase.
</details>

---

<!-- =========================================================================================
                                     EXPERIMENT 10
     ========================================================================================= -->
## 🛠️ Experiment 10: YACC & LEX Tools

Parser development using YACC tool for various grammatical structures.

| Format | Document | Description | Link |
|:---:|:---|:---|:-:|
| 📄 | [Lab Report](Experiment-10/Amey_B-50_SPCC_Lab_Experiment-10.docx) | Detailed experiment report | [View](Experiment-10/Amey_B-50_SPCC_Lab_Experiment-10.docx) |
| 💻 | [Integer Recognizer](Experiment-10/Source Code/Integer_Recognizer.l) | LEX script to recognize integers | [View](Experiment-10/Source Code/Integer_Recognizer.l) |
| 💻 | [Arithmetic Counter](Experiment-10/Source Code/Arithmetic_Counter.l) | LEX script to count numbers | [View](Experiment-10/Source Code/Arithmetic_Counter.l) |

<details>
<summary><b>🔍 Technical Logic Overview</b></summary>

Specialized pattern matching tools using the FLEX generator.
- **Integer Recognizer**: Uses `[0-9]+` pattern to isolate numeric lexemes from text streams.
- **Arithmetic Counter**: Implements a global accumulator that increments on every numeric match, providing real-time state analysis.
- **Trigger Logic**: Modernized LEX scripts include custom report triggers (e.g., lowercase letters) to output cumulative data.
</details>

---

<!-- =========================================================================================
                                     FOOTER SECTION
     ========================================================================================= -->
<div align="center">

  <!-- Footer Navigation -->
  **[⬆ Back to Top](#system-software-lab)**

  **[🛠️ Exp 1](#-experiment-1-symbol-table-implementation)** &nbsp;·&nbsp; **[🔍 Exp 2](#-experiment-2-lexical-analysis)** &nbsp;·&nbsp; **[🏗️ Exp 3](#-experiment-3-parsing-techniques)** &nbsp;·&nbsp; **[🚦 Exp 4](#-experiment-4-intermediate-code-generation)** &nbsp;·&nbsp; **[⚙️ Exp 5](#-experiment-5-code-optimization)** &nbsp;·&nbsp; **[📝 Exp 6](#-experiment-6-target-code-generation)** &nbsp;·&nbsp; **[🧩 Exp 7](#-experiment-7-assembler-pass-i)** &nbsp;·&nbsp; **[🔄 Exp 8](#-experiment-8-assembler-pass-ii)** &nbsp;·&nbsp; **[🔗 Exp 9](#-experiment-9-macro-processor)** &nbsp;·&nbsp; **[🛠️ Exp 10](#-experiment-10-yacc--lex-tools)**

  <br>

  **[🏠 Back to Main Repository](../)**

</div>

---

<div align="center">

  ### [System Software Lab](https://github.com/Amey-Thakur/SYSTEM-PROGRAMMING-AND-COMPILER-CONSTRUCTION-AND-SYSTEM-SOFTWARE-LAB/tree/main/System%20Software%20Lab)

  **CSL602 · Semester VI · Computer Engineering**

  *University of Mumbai · Curated by [Amey Thakur](https://github.com/Amey-Thakur)*

</div>
