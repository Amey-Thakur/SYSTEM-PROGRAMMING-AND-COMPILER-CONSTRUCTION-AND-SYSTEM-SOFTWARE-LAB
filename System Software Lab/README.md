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

  **[️ Exp 1](#-experiment-1-symbol-table-implementation)** &nbsp;·&nbsp; **[🔍 Exp 2](#-experiment-2-lexical-analysis)** &nbsp;·&nbsp; **[🏗️ Exp 3](#-experiment-3-parsing-techniques)** &nbsp;·&nbsp; **[🚦 Exp 4](#-experiment-4-intermediate-code-generation)** &nbsp;·&nbsp; **[⚙️ Exp 5](#-experiment-5-code-optimization)** &nbsp;·&nbsp; **[📝 Exp 6](#-experiment-6-target-code-generation)** &nbsp;·&nbsp; **[🧩 Exp 7](#-experiment-7-assembler-pass-i)** &nbsp;·&nbsp; **[🔄 Exp 8](#-experiment-8-assembler-pass-ii)** &nbsp;·&nbsp; **[🔗 Exp 9](#-experiment-9-macro-processor)** &nbsp;·&nbsp; **[🛠️ Exp 10](#-experiment-10-yacc--lex-tools)**

</div>

---

> [!TIP]
> **LEX & YACC Workflow**: When working with LEX/YACC tools, always test your regular expressions and grammar rules incrementally. Start with the simplest patterns first, then gradually add complexity. For Assembler experiments, ensure your Symbol Table (`SYMTAB`) from Pass-I is correctly populated before attempting Pass-II, as all address resolution depends on it.

> [!WARNING]
> **Compilation Requirements**: When compiling LEX files, always ensure the `-lfl` library is linked or define `yywrap()` to avoid linker errors. For Assembler experiments (Pass-I/II), verify that `INPUT.txt` and `OPTAB.txt` are in the same directory as the executable.

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

| # | Program | Description | Source Code |
|:---|:---|:---|:-:|
| 1 | [DFA_Implementation.c](Experiment-1/Source%20Code/DFA_Implementation.c) | C implementation for DFA acceptance | [View](Experiment-1/Source%20Code/DFA_Implementation.c) |
| � | [Lab Report](Experiment-1/Amey_B-50_SPCC_Lab_Experiment-1.pdf) | Detailed experiment report | [View](Experiment-1/Amey_B-50_SPCC_Lab_Experiment-1.pdf) |

---

<!-- =========================================================================================
                                     EXPERIMENT 2
     ========================================================================================= -->
## 🔍 Experiment 2: Lexical Analysis

Scanner development using LEX tool to identify tokens in a source program.

| # | Program | Description | Source Code |
|:---|:---|:---|:-:|
| 1 | [Lex_Lexical_Analyzer.l](Experiment-2/Source%20Code/Lex_Lexical_Analyzer.l) | LEX implementation for scanner | [View](Experiment-2/Source%20Code/Lex_Lexical_Analyzer.l) |
| 2 | [Manual_Lexical_Analyzer.c](Experiment-2/Source%20Code/Manual_Lexical_Analyzer.c) | Manual C implementation for scanner | [View](Experiment-2/Source%20Code/Manual_Lexical_Analyzer.c) |
| 3 | [sample_input.c](Experiment-2/Source%20Code/sample_input.c) | Test C file for analysis | [View](Experiment-2/Source%20Code/sample_input.c) |
| � | [Lab Report](Experiment-2/Amey_B-50_SPCC_Lab_Experiment-2.pdf) | Detailed experiment report | [View](Experiment-2/Amey_B-50_SPCC_Lab_Experiment-2.pdf) |

---

<!-- =========================================================================================
                                     EXPERIMENT 3
     ========================================================================================= -->
## 🏗️ Experiment 3: Parsing Techniques

Implementation of FIRST and FOLLOW sets calculation for syntax analysis of grammars.

| # | Program | Description | Source Code |
|:---|:---|:---|:-:|
| 1 | [First_Follow_Implementation.c](Experiment-3/Source%20Code/First_Follow_Implementation.c) | C implementation for FIRST & FOLLOW | [View](Experiment-3/Source%20Code/First_Follow_Implementation.c) |
| 2 | [grammar.txt](Experiment-3/Source%20Code/grammar.txt) | Input grammar for calculation | [View](Experiment-3/Source%20Code/grammar.txt) |
| � | [Lab Report](Experiment-3/Amey_B-50_SPCC_Lab_Experiment-3.pdf) | Detailed experiment report | [View](Experiment-3/Amey_B-50_SPCC_Lab_Experiment-3.pdf) |

---

<!-- =========================================================================================
                                     EXPERIMENT 4
     ========================================================================================= -->
## 🚦 Experiment 4: Intermediate Code Generation

Implementation of Recursive Descent Parser for syntax analysis of grammars.

| # | Program | Description | Source Code |
|:---|:---|:---|:-:|
| 1 | [RD_Parser_Implementation.c](Experiment-4/Source%20Code/RD_Parser_Implementation.c) | C implementation for RD Parser | [View](Experiment-4/Source%20Code/RD_Parser_Implementation.c) |
| � | [Lab Report](Experiment-4/Amey_B-50_SPCC_Lab_Experiment-4.pdf) | Detailed experiment report | [View](Experiment-4/Amey_B-50_SPCC_Lab_Experiment-4.pdf) |

---

<!-- =========================================================================================
                                     EXPERIMENT 5
     ========================================================================================= -->
## ⚙️ Experiment 5: Code Optimization

Implementation of constant folding and common sub-expression elimination techniques.

| # | Program | Description | Source Code |
|:---|:---|:---|:-:|
| 1 | [Code_Optimization.c](Experiment-5/Source%20Code/Code_Optimization.c) | C implementation for optimizations | [View](Experiment-5/Source%20Code/Code_Optimization.c) |
| � | [Lab Report](Experiment-5/Amey_B-50_SPCC_Lab_Experiment-5.pdf) | Detailed experiment report | [View](Experiment-5/Amey_B-50_SPCC_Lab_Experiment-5.pdf) |

---

<!-- =========================================================================================
                                     EXPERIMENT 6
     ========================================================================================= -->
## 📝 Experiment 6: Target Code Generation

Implementation of Target Code Generation logic including MOV and arithmetic instructions.

| # | Program | Description | Source Code |
|:---|:---|:---|:-:|
| 1 | [Target_Code_Generator.c](Experiment-6/Source%20Code/Target_Code_Generator.c) | C implementation for Target Code Generation | [View](Experiment-6/Source%20Code/Target_Code_Generator.c) |
| � | [Lab Report](Experiment-6/Amey_B-50_SPCC_Lab_Experiment-6.pdf) | Detailed experiment report | [View](Experiment-6/Amey_B-50_SPCC_Lab_Experiment-6.pdf) |

---

<!-- =========================================================================================
                                     EXPERIMENT 7
     ========================================================================================= -->
## 🧩 Experiment 7: Assembler PASS-I

Design and implementation of Pass-I Assembler to generate Symbol Table and calculate program length.

| # | Program | Description | Source Code |
|:---|:---|:---|:-:|
| 1 | [Assembler_Pass1.c](Experiment-7/Source%20Code/Assembler_Pass1.c) | C implementation for Assembler PASS-I | [View](Experiment-7/Source%20Code/Assembler_Pass1.c) |
| 2 | [INPUT.txt](Experiment-7/Source%20Code/INPUT.txt) | Input assembly source code | [View](Experiment-7/Source%20Code/INPUT.txt) |
| 3 | [OPTAB.txt](Experiment-7/Source%20Code/OPTAB.txt) | Machine Operation Table | [View](Experiment-7/Source%20Code/OPTAB.txt) |
| 4 | [SYMTAB.txt](Experiment-7/Source%20Code/SYMTAB.txt) | Generated Symbol Table | [View](Experiment-7/Source%20Code/SYMTAB.txt) |
| 📄 | [Lab Report](Experiment-7/Amey_B-50_SPCC_Lab_Experiment-7.pdf) | Detailed experiment report | [View](Experiment-7/Amey_B-50_SPCC_Lab_Experiment-7.pdf) |

---

<!-- =========================================================================================
                                     EXPERIMENT 8
     ========================================================================================= -->
## 🔄 Experiment 8: Assembler PASS-II

Design and implementation of Pass-II Assembler to generate Object Code (H, T, E records).

| # | Program | Description | Source Code |
|:---|:---|:---|:-:|
| 1 | [Assembler_Pass2.c](Experiment-8/Source%20Code/Assembler_Pass2.c) | C implementation for Assembler PASS-II | [View](Experiment-8/Source%20Code/Assembler_Pass2.c) |
| � | [Lab Report](Experiment-8/Amey_B-50_SPCC_Lab_Experiment-8.pdf) | Detailed experiment report | [View](Experiment-8/Amey_B-50_SPCC_Lab_Experiment-8.pdf) |

---

<!-- =========================================================================================
                                     EXPERIMENT 9
     ========================================================================================= -->
## 🔗 Experiment 9: Macro Processor

Simulation of a one-pass Macro Processor handling definition and expansion.

| # | Program | Description | Source Code |
|:---|:---|:---|:-:|
| 1 | [Macro_Processor.c](Experiment-9/Source%20Code/Macro_Processor.c) | C implementation for Macro Processor | [View](Experiment-9/Source%20Code/Macro_Processor.c) |
| � | [Lab Report](Experiment-9/Amey_B-50_SPCC_Lab_Experiment-9.pdf) | Detailed experiment report | [View](Experiment-9/Amey_B-50_SPCC_Lab_Experiment-9.pdf) |

---

<!-- =========================================================================================
                                     EXPERIMENT 10
     ========================================================================================= -->
## 🛠️ Experiment 10: YACC & LEX Tools

Parser development using YACC tool for various grammatical structures.

| # | Program | Description | Source Code |
|:---|:---|:---|:-:|
| 1 | [Integer_Recognizer.l](Experiment-10/Source%20Code/Integer_Recognizer.l) | LEX script to recognize integers | [View](Experiment-10/Source%20Code/Integer_Recognizer.l) |
| 2 | [Arithmetic_Counter.l](Experiment-10/Source%20Code/Arithmetic_Counter.l) | LEX script to count numbers | [View](Experiment-10/Source%20Code/Arithmetic_Counter.l) |
| 📄 | [Lab Report](Experiment-10/Amey_B-50_SPCC_Lab_Experiment-10.docx) | Detailed experiment report | [View](Experiment-10/Amey_B-50_SPCC_Lab_Experiment-10.docx) |

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
