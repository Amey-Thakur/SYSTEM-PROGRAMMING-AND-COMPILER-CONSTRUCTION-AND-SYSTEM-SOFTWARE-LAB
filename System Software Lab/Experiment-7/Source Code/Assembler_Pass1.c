/*
 * =========================================================================================
 * Experiment 7: Assembler PASS-I Implementation
 * Course: System Programming and Compiler Construction (SPCC)
 * 
 * Author: Amey Thakur
 * GitHub: https://github.com/Amey-Thakur
 * Repository: https://github.com/Amey-Thakur/SYSTEM-PROGRAMMING-AND-COMPILER-CONSTRUCTION-AND-SYSTEM-SOFTWARE-LAB
 * =========================================================================================
 * 
 * TECHNICAL LOGIC EXPLANATION:
 * Pass-I of a two-pass assembler is primarily responsible for establishing the 
 * memory layout of the program and defining all symbols used in the source code.
 * 
 * Operational Logic:
 * 1. Location Counter (LC) Management: The LC tracks the relative address of 
 *    every instruction and data item. It is initialized via the 'START' directive.
 * 2. Symbol Extraction: Whenever a label is encountered, its name and current 
 *    LC value are recorded in the Symbol Table (SYMTAB). This "defines" the symbol.
 * 3. Opcode Validation: The program verifies instruction names against a 
 *    predefined Machine Operation Table (OPTAB) to ensure they are valid.
 * 4. Size Allocation: 
 *    - Standard Instructions increase LC by 3 bytes.
 *    - Directives like RESW (Reserve Word) and RESB (Reserve Byte) increase LC 
 *      based on user-specified memory requirements.
 * 5. Length Calculation: Upon reaching 'END', the program computes the total 
 *    memory footprint (Last LC - Starting Address).
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
    FILE *f_input, *f_optab, *f_symtab;
    int lc, start_address, op_value, program_length;
    char label[20], opcode[20], operand[20], optab_opcode[20];

    // File Resource Management
    f_input = fopen("INPUT.txt", "r");
    f_symtab = fopen("SYMTAB.txt", "w");

    // Pre-execution integrity check
    if (!f_input) {
        printf("System Error: Unable to access source file 'INPUT.txt'.\n");
        return 1;
    }

    printf("\n==============================================\n");
    printf("           ASSEMBLER PASS-I LOG              \n");
    printf("==============================================\n");
    printf("%-10s %-10s %-10s %-10s\n", "ADDR", "LABEL", "OPCODE", "OPERAND");
    printf("----------------------------------------------\n");

    /* PHASE 1: Initialization Logic */
    if (fscanf(f_input, "%s %s %d", label, opcode, &start_address) == 3) {
        if (strcmp(opcode, "START") == 0) {
            lc = start_address; // Synchronizing Location Counter with Start Address
            printf("\t   %-10s %-10s %d\n", label, opcode, start_address);
        } else {
            lc = 0; // Defaulting to zero if Start directive is absent
            rewind(f_input);
        }
    }

    /* PHASE 2: Main Processing Loop (Symbol Definition & LC Tracking) */
    while (fscanf(f_input, "%s %s", label, opcode) != EOF) {
        fscanf(f_input, "%s", operand);
        printf("%04d\t   %-10s %-10s %-10s\n", lc, label, opcode, operand);

        // Logical Step: Enter identified labels into the Symbol Table
        if (strcmp(label, "-") != 0) {
            fprintf(f_symtab, "%s\t%d\n", label, lc);
        }

        // Logical Step: Check for Machine Instructions in OPTAB
        f_optab = fopen("OPTAB.txt", "r");
        int found = 0;
        if (f_optab) {
            while (fscanf(f_optab, "%s %d", optab_opcode, &op_value) != EOF) {
                if (strcmp(opcode, optab_opcode) == 0) {
                    lc += 3; // SIC instruction increment constant
                    found = 1;
                    break;
                }
            }
            fclose(f_optab);
        }

        // Logical Step: Process Assembler Directives
        if (!found) {
            if (strcmp(opcode, "WORD") == 0) {
                lc += 3; // Word size allocation
            } else if (strcmp(opcode, "RESW") == 0) {
                lc += (3 * atoi(operand)); // Reserve Word block
            } else if (strcmp(opcode, "RESB") == 0) {
                lc += atoi(operand);       // Reserve Byte block
            } else if (strcmp(opcode, "BYTE") == 0) {
                // Byte allocation based on literal length
                if (operand[0] == 'X') {
                    lc += 1;
                } else {
                    lc += (strlen(operand) - 3); 
                }
            } else if (strcmp(opcode, "END") == 0) {
                break; // Logic termination on END directive
            }
        }
    }

    /* PHASE 3: Wrap-up Logic */
    program_length = lc - start_address;
    printf("----------------------------------------------\n");
    printf("Analysis Complete: Program Length = %d bytes\n", program_length);
    printf("==============================================\n");

    // Closing active file streams
    fclose(f_input);
    fclose(f_symtab);

    return 0;
}
