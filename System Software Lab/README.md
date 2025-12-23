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

  **[🛠️ Exp 1](#-experiment-1-symbol-table-implementation)** &nbsp;·&nbsp; **[🔍 Exp 2](#-experiment-2-lexical-analysis)** &nbsp;·&nbsp; **[🏗️ Exp 3](#-experiment-3-parsing-techniques)** &nbsp;·&nbsp; **[🚦 Exp 4](#-experiment-4-intermediate-code-generation)** &nbsp;·&nbsp; **[⚙️ Exp 5](#-experiment-5-code-optimization)** &nbsp;·&nbsp; **[📝 Exp 6](#-experiment-6-assembler-pass-i)** &nbsp;·&nbsp; **[🧩 Exp 7](#-experiment-7-assembler-pass-ii)** &nbsp;·&nbsp; **[🔄 Exp 8](#-experiment-8-macro-processor)** &nbsp;·&nbsp; **[🔗 Exp 9](#-experiment-9-linker-and-loader)** &nbsp;·&nbsp; **[🛠️ Exp 10](#-experiment-10-yacc-tools)**

</div>

---

> [!TIP]
> **Lab Manual**: This directory contains comprehensive reports and source code for all experiments conducted during the course. For theoretical concepts and reference books, please visit the [**Main Repository**](../README.md).

---

<!-- =========================================================================================
                                     EXPERIMENT 1
     ========================================================================================= -->
## 🛠️ Experiment 1: Symbol Table Implementation

Implementation of Symbol Table using C to manage identifiers and their properties.

| Format | Document | Description | Link |
|:---:|:---|:---|:-:|
| 📄 | [Lab Report](Experiment-1/Amey_B-50_SPCC_Lab_Experiment-1.pdf) | Detailed experiment report | [View](Experiment-1/Amey_B-50_SPCC_Lab_Experiment-1.pdf) |
| 💻 | [Source Code](Experiment-1/Source Code/SPCC-1.c) | C implementation for Symbol Table | [View](Experiment-1/Source Code/SPCC-1.c) |

---

<!-- =========================================================================================
                                     EXPERIMENT 2
     ========================================================================================= -->
## 🔍 Experiment 2: Lexical Analysis

Scanner development using LEX tool to identify tokens in a source program.

| Format | Document | Description | Link |
|:---:|:---|:---|:-:|
| 📄 | [Lab Report](Experiment-2/Amey_B-50_SPCC_Lab_Experiment-2.pdf) | Detailed experiment report | [View](Experiment-2/Amey_B-50_SPCC_Lab_Experiment-2.pdf) |
| 💻 | [Source Code](Experiment-2/Source Code/SPCC-2.l) | LEX implementation for scanner | [View](Experiment-2/Source Code/SPCC-2.l) |

---

<!-- =========================================================================================
                                     EXPERIMENT 3
     ========================================================================================= -->
## 🏗️ Experiment 3: Parsing Techniques

Implementation of Recursive Descent Parser for syntax analysis of grammars.

| Format | Document | Description | Link |
|:---:|:---|:---|:-:|
| 📄 | [Lab Report](Experiment-3/Amey_B-50_SPCC_Lab_Experiment-3.pdf) | Detailed experiment report | [View](Experiment-3/Amey_B-50_SPCC_Lab_Experiment-3.pdf) |
| 💻 | [Source Code](Experiment-3/Source Code/SPCC-3.c) | C implementation for RD Parser | [View](Experiment-3/Source Code/SPCC-3.c) |

---

<!-- =========================================================================================
                                     EXPERIMENT 4
     ========================================================================================= -->
## 🚦 Experiment 4: Intermediate Code Generation

Three-address code generation implementation for arithmetic expressions.

| Format | Document | Description | Link |
|:---:|:---|:---|:-:|
| 📄 | [Lab Report](Experiment-4/Amey_B-50_SPCC_Lab_Experiment-4.pdf) | Detailed experiment report | [View](Experiment-4/Amey_B-50_SPCC_Lab_Experiment-4.pdf) |
| 💻 | [Source Code](Experiment-4/Source Code/SPCC-4.c) | C implementation for TAC generation | [View](Experiment-4/Source Code/SPCC-4.c) |

---

<!-- =========================================================================================
                                     EXPERIMENT 5
     ========================================================================================= -->
## ⚙️ Experiment 5: Code Optimization

Implementation of constant folding and common sub-expression elimination techniques.

| Format | Document | Description | Link |
|:---:|:---|:---|:-:|
| 📄 | [Lab Report](Experiment-5/Amey_B-50_SPCC_Lab_Experiment-5.pdf) | Detailed experiment report | [View](Experiment-5/Amey_B-50_SPCC_Lab_Experiment-5.pdf) |
| 💻 | [Source Code](Experiment-5/Source Code/SPCC-5.c) | C implementation for optimizations | [View](Experiment-5/Source Code/SPCC-5.c) |

---

<!-- =========================================================================================
                                     EXPERIMENT 6
     ========================================================================================= -->
## 📝 Experiment 6: Assembler PASS-I

Implementation of One-pass Assembler logic including LC and Symbol Table.

| Format | Document | Description | Link |
|:---:|:---|:---|:-:|
| 📄 | [Lab Report](Experiment-6/Amey_B-50_SPCC_Lab_Experiment-6.pdf) | Detailed experiment report | [View](Experiment-6/Amey_B-50_SPCC_Lab_Experiment-6.pdf) |
| 💻 | [Source Code](Experiment-6/Source Code/SPCC-6.c) | C implementation for Assembler PASS-I | [View](Experiment-6/Source Code/SPCC-6.c) |

---

<!-- =========================================================================================
                                     EXPERIMENT 7
     ========================================================================================= -->
## 🧩 Experiment 7: Assembler PASS-II

Design and implementation of Multi-pass Assembler to generate object code.

| Format | Document | Description | Link |
|:---:|:---|:---|:-:|
| 📄 | [Lab Report](Experiment-7/Amey_B-50_SPCC_Lab_Experiment-7.pdf) | Detailed experiment report | [View](Experiment-7/Amey_B-50_SPCC_Lab_Experiment-7.pdf) |
| 💻 | [Source Code](Experiment-7/Source Code/SPCC-7.c) | C implementation for Assembler PASS-II | [View](Experiment-7/Source Code/SPCC-7.c) |

---

<!-- =========================================================================================
                                     EXPERIMENT 8
     ========================================================================================= -->
## 🔄 Experiment 8: Macro Processor

Design of two-pass Macro Processor with MNT and MDT management.

| Format | Document | Description | Link |
|:---:|:---|:---|:-:|
| 📄 | [Lab Report](Experiment-8/Amey_B-50_SPCC_Lab_Experiment-8.pdf) | Detailed experiment report | [View](Experiment-8/Amey_B-50_SPCC_Lab_Experiment-8.pdf) |
| 💻 | [Source Code](Experiment-8/Source Code/SPCC-8.c) | C implementation for Macro Processor | [View](Experiment-8/Source Code/SPCC-8.c) |

---

<!-- =========================================================================================
                                     EXPERIMENT 9
     ========================================================================================= -->
## 🔗 Experiment 9: Linker and Loader

Simulation of Direct-linking Loader for program relocation and linking.

| Format | Document | Description | Link |
|:---:|:---|:---|:-:|
| 📄 | [Lab Report](Experiment-9/Amey_B-50_SPCC_Lab_Experiment-9.pdf) | Detailed experiment report | [View](Experiment-9/Amey_B-50_SPCC_Lab_Experiment-9.pdf) |
| 💻 | [Source Code](Experiment-9/Source Code/SPCC-9.c) | C implementation for Loader simulation | [View](Experiment-9/Source Code/SPCC-9.c) |

---

<!-- =========================================================================================
                                     EXPERIMENT 10
     ========================================================================================= -->
## 🛠️ Experiment 10: YACC Tools

Parser development using YACC tool for various grammatical structures.

| Format | Document | Description | Link |
|:---:|:---|:---|:-:|
| 📂 | [Report Folder](Experiment-10/) | Detailed experiment documents | [View](Experiment-10/) |
| 💻 | [Source Code](Experiment-10/Source Code/) | YACC implementation for parser | [View](Experiment-10/Source Code/) |

---

<!-- =========================================================================================
                                     FOOTER SECTION
     ========================================================================================= -->
<div align="center">

  <!-- Footer Navigation -->
  **[⬆ Back to Top](#system-software-lab)**

  **[🛠️ Exp 1](#-experiment-1-symbol-table-implementation)** &nbsp;·&nbsp; **[🔍 Exp 2](#-experiment-2-lexical-analysis)** &nbsp;·&nbsp; **[🏗️ Exp 3](#-experiment-3-parsing-techniques)** &nbsp;·&nbsp; **[🚦 Exp 4](#-experiment-4-intermediate-code-generation)** &nbsp;·&nbsp; **[⚙️ Exp 5](#-experiment-5-code-optimization)** &nbsp;·&nbsp; **[📝 Exp 6](#-experiment-6-assembler-pass-i)** &nbsp;·&nbsp; **[🧩 Exp 7](#-experiment-7-assembler-pass-ii)** &nbsp;·&nbsp; **[🔄 Exp 8](#-experiment-8-macro-processor)** &nbsp;·&nbsp; **[🔗 Exp 9](#-experiment-9-linker-and-loader)** &nbsp;·&nbsp; **[🛠️ Exp 10](#-experiment-10-yacc-tools)**

  <br>

  **[🏠 Back to Main Repository](../)**

</div>

---

<div align="center">

  ### [System Software Lab](https://github.com/Amey-Thakur/SYSTEM-PROGRAMMING-AND-COMPILER-CONSTRUCTION-AND-SYSTEM-SOFTWARE-LAB/tree/main/System%20Software%20Lab)

  **CSL602 · Semester VI · Computer Engineering**

  *University of Mumbai · Curated by [Amey Thakur](https://github.com/Amey-Thakur)*

</div>
