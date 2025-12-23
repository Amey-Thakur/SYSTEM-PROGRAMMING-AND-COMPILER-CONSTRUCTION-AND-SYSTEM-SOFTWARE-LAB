/*
 * Experiment 7: Assembler PASS-I Implementation
 * Course: System Programming and Compiler Construction (SPCC)
 * 
 * Author: Amey Thakur
 * GitHub: https://github.com/Amey-Thakur
 * Repository: https://github.com/Amey-Thakur/SYSTEM-PROGRAMMING-AND-COMPILER-CONSTRUCTION-AND-SYSTEM-SOFTWARE-LAB
 * 
 * Description:
 * This program implements the first pass of a two-pass assembler.
 * Key responsibilities:
 * 1. Read assembly source from 'INPUT.txt'.
 * 2. Maintain a Location Counter (LC).
 * 3. Generate a Symbol Table (SYMTAB) from identified labels.
 * 4. Validate opcodes against 'OPTAB.txt'.
 * 5. Calculate the total program length.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
    FILE *f_input, *f_optab, *f_symtab;
    int lc, start_address, op_value, program_length;
    char label[20], opcode[20], operand[20], optab_opcode[20];

    f_input = fopen("INPUT.txt", "r");
    f_symtab = fopen("SYMTAB.txt", "w");

    if (!f_input) {
        printf("Error: Could not open INPUT.txt\n");
        return 1;
    }

    printf("\n==============================================\n");
    printf("           ASSEMBLER PASS-I LOG              \n");
    printf("==============================================\n");
    printf("%-10s %-10s %-10s %-10s\n", "LC", "Label", "Opcode", "Operand");
    printf("----------------------------------------------\n");

    /* Initial processing: Check for START directive */
    if (fscanf(f_input, "%s %s %d", label, opcode, &start_address) == 3) {
        if (strcmp(opcode, "START") == 0) {
            lc = start_address;
            printf("\t   %-10s %-10s %d\n", label, opcode, start_address);
        } else {
            lc = 0;
            // Handle case where START is missing (rewind or assume 0)
            rewind(f_input);
        }
    }

    /* Process lines until END */
    while (fscanf(f_input, "%s %s", label, opcode) != EOF) {
        fscanf(f_input, "%s", operand);
        printf("%04d\t   %-10s %-10s %-10s\n", lc, label, opcode, operand);

        // If label exists, enter into Symbol Table
        if (strcmp(label, "-") != 0) {
            fprintf(f_symtab, "%s\t%d\n", label, lc);
        }

        // Search in Opcode Table
        f_optab = fopen("OPTAB.txt", "r");
        int found = 0;
        if (f_optab) {
            while (fscanf(f_optab, "%s %d", optab_opcode, &op_value) != EOF) {
                if (strcmp(opcode, optab_opcode) == 0) {
                    lc += 3; // SIC instruction size is 3 bytes
                    found = 1;
                    break;
                }
            }
            fclose(f_optab);
        }

        // Handle Assembler Directives
        if (!found) {
            if (strcmp(opcode, "WORD") == 0) {
                lc += 3;
            } else if (strcmp(opcode, "RESW") == 0) {
                lc += (3 * atoi(operand));
            } else if (strcmp(opcode, "RESB") == 0) {
                lc += atoi(operand);
            } else if (strcmp(opcode, "BYTE") == 0) {
                if (operand[0] == 'X') {
                    lc += 1;
                } else {
                    lc += (strlen(operand) - 3); // C'EOF' -> EOF = 3 bytes
                }
            } else if (strcmp(opcode, "END") == 0) {
                break;
            }
        }
    }

    program_length = lc - start_address;
    printf("----------------------------------------------\n");
    printf("Total Program Length: %d bytes\n", program_length);
    printf("==============================================\n");

    fclose(f_input);
    fclose(f_symtab);

    return 0;
}
