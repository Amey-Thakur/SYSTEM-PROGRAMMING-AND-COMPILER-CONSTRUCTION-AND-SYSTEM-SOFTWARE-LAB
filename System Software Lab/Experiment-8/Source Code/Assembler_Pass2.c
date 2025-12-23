/*
 * Experiment 8: Assembler PASS-II Implementation
 * Course: System Programming and Compiler Construction (SPCC)
 * 
 * Author: Amey Thakur
 * GitHub: https://github.com/Amey-Thakur
 * Repository: https://github.com/Amey-Thakur/SYSTEM-PROGRAMMING-AND-COMPILER-CONSTRUCTION-AND-SYSTEM-SOFTWARE-LAB
 * 
 * Description:
 * This program implements the second pass of a two-pass assembler.
 * Key responsibilities:
 * 1. Read intermediate code from 'INTERMED.DAT'.
 * 2. Read symbol definitions from 'SYMTAB.DAT'.
 * 3. Generate Object Code (H, T, E records) in 'OBJCODE.DAT'.
 * 4. Create an assembly listing in 'ASSMLIST.DAT'.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/**
 * Standard SIC Mnemonics and Opcode Table
 */
char mnemonic[4][10] = {"LDA", "STA", "LDCH", "STCH"};
char opcode_hex[4][10] = {"00", "0C", "50", "54"};

int main() {
    FILE *f_inter, *f_symtab, *f_list, *f_obj;
    char label[10], opcode[10], operand[10], symbol[10];
    int start_addr, current_addr, final_addr, sym_addr, text_len;
    char object_code[20];

    f_inter = fopen("INTERMED.DAT", "r");
    f_symtab = fopen("SYMTAB.DAT", "r");
    f_list = fopen("ASSMLIST.DAT", "w");
    f_obj = fopen("OBJCODE.DAT", "w");

    if (!f_inter || !f_symtab) {
        printf("Error: Missing input files (INTERMED.DAT or SYMTAB.DAT)\n");
        return 1;
    }

    /* Initialize: Find final address for Header Record length calculation */
    fscanf(f_inter, "%s %s %s", label, opcode, operand);
    while (strcmp(opcode, "END") != 0) {
        fscanf(f_inter, "%d %s %s %s", &current_addr, label, opcode, operand);
    }
    final_addr = current_addr;
    rewind(f_inter);

    /* Process START Record */
    fscanf(f_inter, "%s %s %d", label, opcode, &start_addr);
    if (strcmp(opcode, "START") == 0) {
        fprintf(f_list, "\t%s\t%s\t%d\n", label, opcode, start_addr);
        fprintf(f_obj, "H^%-6s^%06d^%06X\n", label, start_addr, final_addr - start_addr);
        fscanf(f_inter, "%d %s %s %s", &current_addr, label, opcode, operand);
        
        // Start Text Record
        fprintf(f_obj, "T^%06X^%02X", current_addr, 0); // Length updated manually or via buffer later
    }

    /* Main Processing Loop */
    while (strcmp(opcode, "END") != 0) {
        int found_op = 0;
        sprintf(object_code, "");

        // Search Opcode Table
        for (int i = 0; i < 4; i++) {
            if (strcmp(opcode, mnemonic[i]) == 0) {
                rewind(f_symtab);
                while (fscanf(f_symtab, "%s %d", symbol, &sym_addr) != EOF) {
                    if (strcmp(operand, symbol) == 0) {
                        sprintf(object_code, "%s%04d", opcode_hex[i], sym_addr);
                        found_op = 1;
                        break;
                    }
                }
                break;
            }
        }

        // Handle Directives
        if (!found_op) {
            if (strcmp(opcode, "BYTE") == 0) {
                if (operand[0] == 'X') {
                    // X'05' -> 05
                    strncpy(object_code, operand + 2, strlen(operand) - 3);
                    object_code[strlen(operand) - 3] = '\0';
                } else if (operand[0] == 'C') {
                    // C'EOF' -> 454F46
                    for (int i = 2; i < strlen(operand) - 1; i++) {
                        char temp[5];
                        sprintf(temp, "%02X", operand[i]);
                        strcat(object_code, temp);
                    }
                }
            } else if (strcmp(opcode, "WORD") == 0) {
                sprintf(object_code, "%06X", atoi(operand));
            }
        }

        /* Write to Listing and Object File */
        if (strlen(object_code) > 0) {
            fprintf(f_list, "%04d\t%s\t%s\t%s\t%s\n", current_addr, label, opcode, operand, object_code);
            fprintf(f_obj, "^%s", object_code);
        } else {
            fprintf(f_list, "%04d\t%s\t%s\t%s\n", current_addr, label, opcode, operand);
        }

        fscanf(f_inter, "%d %s %s %s", &current_addr, label, opcode, operand);
    }

    /* Finalize */
    fprintf(f_list, "\t%s\t%s\t%s\n", label, opcode, operand);
    fprintf(f_obj, "\nE^%06d\n", start_addr);

    printf("\n==============================================\n");
    printf("           ASSEMBLER PASS-II LOG             \n");
    printf("==============================================\n");
    printf("Object code generated successfully.\n");
    printf("Files updated:\n  - ASSMLIST.DAT (Listing)\n  - OBJCODE.DAT (Object Code)\n");
    printf("==============================================\n");

    fclose(f_inter);
    fclose(f_symtab);
    fclose(f_list);
    fclose(f_obj);

    return 0;
}
