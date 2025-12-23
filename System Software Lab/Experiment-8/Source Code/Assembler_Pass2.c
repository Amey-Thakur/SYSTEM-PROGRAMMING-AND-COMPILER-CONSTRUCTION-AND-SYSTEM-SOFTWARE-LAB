/*
 * =========================================================================================
 * Experiment 8: Assembler PASS-II Implementation
 * Course: System Programming and Compiler Construction (SPCC)
 * 
 * Author: Amey Thakur
 * GitHub: https://github.com/Amey-Thakur
 * Repository: https://github.com/Amey-Thakur/SYSTEM-PROGRAMMING-AND-COMPILER-CONSTRUCTION-AND-SYSTEM-SOFTWARE-LAB
 * =========================================================================================
 * 
 * TECHNICAL LOGIC EXPLANATION:
 * Pass-II is the final stage of the assembly process. It uses the address information 
 * gathered in Pass-I to generate the actual machine-readable Object Code.
 * 
 * Core Logic:
 * 1. Reference Resolution: The program looks up operand labels in the Symbol Table 
 *    (SYMTAB) to find their numeric memory addresses.
 * 2. Instruction Synthesis: It combines the Operation Code (OpCode) from the 
 *    Machine Table with the resolved Operand Address to form the full instruction.
 * 3. Constant Conversion: 
 *    - 'WORD' values are converted directly to hex.
 *    - 'BYTE' values (like C'EOF') are converted into their ASCII hexadecimal equivalents.
 * 4. Record Formatting: The program formats the output into standard SIC object records:
 *    - H Record: Header (Name, Start Address, Total Length).
 *    - T Record: Text (Machine code for instructions).
 *    - E Record: End (Signal to end loading and start execution).
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/**
 * MACHINE TABLE (Partial)
 * Mapping mnemonics to their hexadecimal machine codes.
 */
char mnemonic[4][10] = {"LDA", "STA", "LDCH", "STCH"};
char opcode_hex[4][10] = {"00", "0C", "50", "54"};

int main() {
    FILE *f_inter, *f_symtab, *f_list, *f_obj;
    char label[10], opcode[10], operand[10], symbol[10];
    int start_addr, current_addr, final_addr, sym_addr;
    char object_code[20];

    // Resource Initialization
    f_inter = fopen("INTERMED.DAT", "r");
    f_symtab = fopen("SYMTAB.DAT", "r");
    f_list = fopen("ASSMLIST.DAT", "w");
    f_obj = fopen("OBJCODE.DAT", "w");

    // Integrity Check
    if (!f_inter || !f_symtab) {
        printf("Fatal Error: Required data files (INTERMED/SYMTAB) are inaccessible.\n");
        return 1;
    }

    /* LOGICAL STEP: Pre-scan to calculate total program length for the Header. */
    fscanf(f_inter, "%s %s %s", label, opcode, operand);
    while (strcmp(opcode, "END") != 0) {
        fscanf(f_inter, "%d %s %s %s", &current_addr, label, opcode, operand);
    }
    final_addr = current_addr;
    rewind(f_inter);

    /* LOGICAL STEP: Processing the START Directive. */
    fscanf(f_inter, "%s %s %d", label, opcode, &start_addr);
    if (strcmp(opcode, "START") == 0) {
        // Output documentation in the Assembly Listing
        fprintf(f_list, "\t%s\t%s\t%d\n", label, opcode, start_addr);
        // Writing the 'H' Record to the Object File
        fprintf(f_obj, "H^%-6s^%06d^%06X\n", label, start_addr, final_addr - start_addr);
        
        fscanf(f_inter, "%d %s %s %s", &current_addr, label, opcode, operand);
        // Initiating the first 'T' Record
        fprintf(f_obj, "T^%06X^%02X", current_addr, 0); 
    }

    /* LOGICAL STEP: Main Machine Code Generation Loop. */
    while (strcmp(opcode, "END") != 0) {
        int found_op = 0;
        sprintf(object_code, "");

        // 1. Resolve Machine Instructions
        for (int i = 0; i < 4; i++) {
            if (strcmp(opcode, mnemonic[i]) == 0) {
                rewind(f_symtab);
                while (fscanf(f_symtab, "%s %d", symbol, &sym_addr) != EOF) {
                    if (strcmp(operand, symbol) == 0) {
                        // Instruction = OpCode + Address
                        sprintf(object_code, "%s%04d", opcode_hex[i], sym_addr);
                        found_op = 1;
                        break;
                    }
                }
                break;
            }
        }

        // 2. Resolve Data Directives (BYTE/WORD)
        if (!found_op) {
            if (strcmp(opcode, "BYTE") == 0) {
                if (operand[0] == 'X') {
                    // Extract hex value from literal X'value'
                    strncpy(object_code, operand + 2, strlen(operand) - 3);
                    object_code[strlen(operand) - 3] = '\0';
                } else if (operand[0] == 'C') {
                    // Convert ASCII characters to Hex values
                    for (int i = 2; i < strlen(operand) - 1; i++) {
                        char temp[5];
                        sprintf(temp, "%02X", operand[i]);
                        strcat(object_code, temp);
                    }
                }
            } else if (strcmp(opcode, "WORD") == 0) {
                // Convert integer value to 6-digit Hex format
                sprintf(object_code, "%06X", atoi(operand));
            }
        }

        /* LOGICAL STEP: Writing outputs to listing and object artifacts. */
        if (strlen(object_code) > 0) {
            fprintf(f_list, "%04d\t%s\t%s\t%s\t%s\n", current_addr, label, opcode, operand, object_code);
            fprintf(f_obj, "^%s", object_code);
        } else {
            fprintf(f_list, "%04d\t%s\t%s\t%s\n", current_addr, label, opcode, operand);
        }

        // Read the next instruction block
        fscanf(f_inter, "%d %s %s %s", &current_addr, label, opcode, operand);
    }

    /* LOGICAL STEP: Finalization. */
    fprintf(f_list, "\t%s\t%s\t%s\n", label, opcode, operand); // Writing END to listing
    fprintf(f_obj, "\nE^%06d\n", start_addr);                  // Writing 'E' record

    printf("\n==============================================\n");
    printf("           ASSEMBLER PASS-II LOG             \n");
    printf("==============================================\n");
    printf("Status: Object Code successfully synthesized.\n");
    printf("Artifacts Generated:\n");
    printf("  - ASSMLIST.DAT: Detailed assembly breakdown.\n");
    printf("  - OBJCODE.DAT: Machine-ready SIC object code.\n");
    printf("==============================================\n");

    // Releasing File Resources
    fclose(f_inter);
    fclose(f_symtab);
    fclose(f_list);
    fclose(f_obj);

    return 0;
}
