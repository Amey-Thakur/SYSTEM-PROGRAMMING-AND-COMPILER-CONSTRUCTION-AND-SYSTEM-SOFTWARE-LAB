/*
 * Experiment 9: Macro Processor Implementation
 * Course: System Programming and Compiler Construction (SPCC)
 * 
 * Author: Amey Thakur
 * GitHub: https://github.com/Amey-Thakur
 * Repository: https://github.com/Amey-Thakur/SYSTEM-PROGRAMMING-AND-COMPILER-CONSTRUCTION-AND-SYSTEM-SOFTWARE-LAB
 * 
 * Description:
 * This program implements a basic one-pass macro processor.
 * It handles macro definition and expansion using:
 * 1. NAMTAB: Stores macro names and their definition start/end pointers.
 * 2. DEFTAB: Stores the actual macro definitions with positional parameters.
 * 3. ARGTAB: Stores arguments passed during macro invocation.
 * 
 * Input: Expects an assembly file (e.g., 'input_macro.txt') with MACRO/MEND blocks.
 * Output: Generates an expanded source file ('expanded_output.txt').
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_TABLE_SIZE 50

typedef struct {
    char opcode[20];
    char operand[50];
} DefinitionTable;

typedef struct {
    char name[20];
    int start_index;
    int end_index;
} NameTable;

typedef struct {
    char arg[20];
} ArgumentTable;

DefinitionTable deftab[MAX_TABLE_SIZE];
NameTable namtab[MAX_TABLE_SIZE];
ArgumentTable argtab[10];

int deftab_ptr = 0, namtab_ptr = 0, arg_count = 0;

/**
 * Searches the Name Table for a macro name.
 * @return Index if found, -1 otherwise.
 */
int find_macro(char *name) {
    for (int i = 0; i < namtab_ptr; i++) {
        if (strcmp(namtab[i].name, name) == 0) return i;
    }
    return -1;
}

/**
 * Processes the macro definition and expansion logic.
 */
void process_macros() {
    FILE *f_in, *f_out;
    char label[20], opcode[20], operand[50], temp[20];
    int is_defining = 0;

    f_in = fopen("input_macro.txt", "r");
    f_out = fopen("expanded_output.txt", "w");

    if (!f_in) {
        printf("Error: Could not open input_macro.txt\n");
        return;
    }

    while (fscanf(f_in, "%s %s %s", label, opcode, operand) != EOF) {
        if (strcmp(opcode, "MACRO") == 0) {
            /* Start of Macro Definition */
            strcpy(namtab[namtab_ptr].name, label);
            namtab[namtab_ptr].start_index = deftab_ptr;
            is_defining = 1;

            // Store MACRO header in DEFTAB
            strcpy(deftab[deftab_ptr].opcode, opcode);
            strcpy(deftab[deftab_ptr].operand, operand);
            deftab_ptr++;
        } 
        else if (is_defining) {
            /* Inside Macro Definition */
            strcpy(deftab[deftab_ptr].opcode, opcode);
            
            // Replace positional parameters (e.g., &PARAM1) with indices (?1)
            // Simplified replacement logic for demonstration
            if (operand[0] == '&') {
                sprintf(deftab[deftab_ptr].operand, "?1"); // Hardcoded for simplicity in this variant
            } else {
                strcpy(deftab[deftab_ptr].operand, operand);
            }
            
            deftab_ptr++;
            if (strcmp(opcode, "MEND") == 0) {
                namtab[namtab_ptr].end_index = deftab_ptr - 1;
                namtab_ptr++;
                is_defining = 0;
            }
        } 
        else {
            int macro_idx = find_macro(opcode);
            if (macro_idx != -1) {
                /* Macro Invocation: Expand definition */
                printf("Expanding Macro: %s\n", namtab[macro_idx].name);
                
                // Store argument in ARGTAB
                strcpy(argtab[0].arg, operand);
                
                // Print definition to output file (excluding MACRO/MEND)
                for (int i = namtab[macro_idx].start_index + 1; i < namtab[macro_idx].end_index; i++) {
                    char final_op[20];
                    if (deftab[i].operand[0] == '?') {
                        strcpy(final_op, argtab[0].arg); // Substitute positional parameter
                    } else {
                        strcpy(final_op, deftab[i].operand);
                    }
                    fprintf(f_out, "-\t%s\t%s\n", deftab[i].opcode, final_op);
                }
            } else {
                /* Regular Instruction */
                fprintf(f_out, "%s\t%s\t%s\n", label, opcode, operand);
            }
        }
    }

    fclose(f_in);
    fclose(f_out);
}

int main() {
    printf("\n==============================================\n");
    printf("           MACRO PROCESSOR SIMULATOR         \n");
    printf("==============================================\n");

    process_macros();

    printf("\n--- Definition Table (DEFTAB) ---\n");
    for (int i = 0; i < deftab_ptr; i++) {
        printf("%d: %s\t%s\n", i, deftab[i].opcode, deftab[i].operand);
    }

    printf("\n--- Name Table (NAMTAB) ---\n");
    printf("NAME\tSTART\tEND\n");
    for (int i = 0; i < namtab_ptr; i++) {
        printf("%s\t%d\t%d\n", namtab[i].name, namtab[i].start_index, namtab[i].end_index);
    }

    printf("\nExpansion complete. Check 'expanded_output.txt'.\n");
    printf("==============================================\n");

    return 0;
}
