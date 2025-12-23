/*
 * =========================================================================================
 * Experiment 9: Macro Processor Implementation
 * Course: System Programming and Compiler Construction (SPCC)
 * 
 * Author: Amey Thakur
 * GitHub: https://github.com/Amey-Thakur
 * Repository: https://github.com/Amey-Thakur/SYSTEM-PROGRAMMING-AND-COMPILER-CONSTRUCTION-AND-SYSTEM-SOFTWARE-LAB
 * =========================================================================================
 * 
 * TECHNICAL LOGIC EXPLANATION:
 * A Macro Processor is a program that allows users to define a sequence of code 
 * (a Macro) and invoke it using a single name. This saves time and reduces errors.
 * 
 * Phases of Macro Processing Logic:
 * 1. Macro Definition: When 'MACRO' is detected, the program enters a definition 
 *    phase. It records the macro name in the NAMTAB (Name Table) and 
 *    stores the actual instructions in the DEFTAB (Definition Table).
 * 2. Macro Expansion: When the program encounters the name of a predefined macro 
 *    in the source code, it "expands" it by replacing the name with the 
 *    stored instructions from the DEFTAB.
 * 3. Formal Parameters: Macros can accept inputs (arguments). The processor 
 *    replaces formal parameters (e.g., &VAL) with actual values provided 
 *    at the time of the macro call.
 * 4. Passthrough: Regular code that is not part of a macro or macro call is 
 *    simply copied to the output as-is.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
    FILE *f_input, *f_namtab, *f_deftab, *f_output;
    char label[20], opcode[20], operand[20];
    char name[20], def_label[20], def_opcode[20], def_operand[20];

    // System File Handlers
    f_input = fopen("MACRO_INPUT.txt", "r");
    f_output = fopen("MACRO_OUTPUT.txt", "w");
    
    // Internal Data Structures (Files acting as Tables)
    f_namtab = fopen("NAMTAB.txt", "w+");
    f_deftab = fopen("DEFTAB.txt", "w+");

    if (!f_input) {
        printf("Critical Error: Macro source file 'MACRO_INPUT.txt' missing.\n");
        return 1;
    }

    printf("\n==============================================\n");
    printf("           MACRO PROCESSOR STATUS LOG        \n");
    printf("==============================================\n");

    /* MAIN SCANNING LOGIC */
    while (fscanf(f_input, "%s %s %s", label, opcode, operand) != EOF) {
        
        /* LOGICAL BRANCH 1: Definition Handling */
        if (strcmp(opcode, "MACRO") == 0) {
            // Recording the name of the new macro
            fprintf(f_namtab, "%s\n", label);
            
            // Ingesting the macro body instructions until 'MEND' (Macro End)
            while (fscanf(f_input, "%s %s %s", label, opcode, operand) != EOF) {
                fprintf(f_deftab, "%s\t%s\t%s\n", label, opcode, operand);
                if (strcmp(opcode, "MEND") == 0) break;
            }
            printf("[INFO] Macro Definition Recorded: %s\n", label);
        } 
        
        /* LOGICAL BRANCH 2: Expansion Handling */
        else {
            rewind(f_namtab);
            int is_macro_call = 0;
            while (fscanf(f_namtab, "%s", name) != EOF) {
                if (strcmp(opcode, name) == 0) {
                    is_macro_call = 1;
                    break;
                }
            }

            if (is_macro_call) {
                // Expanding the macro call into its constituent instructions
                printf("[INFO] Expanding Macro Call: %s\n", opcode);
                rewind(f_deftab);
                fprintf(f_output, ".\t%s\t%s\t%s\n", label, opcode, operand); // Commenting the call
                
                while (fscanf(f_deftab, "%s %s %s", def_label, def_opcode, def_operand) != EOF) {
                    if (strcmp(def_opcode, "MEND") == 0) break;
                    // Output expanded code to the destination file
                    fprintf(f_output, "%s\t%s\t%s\n", def_label, def_opcode, def_operand);
                }
            } else {
                /* LOGICAL BRANCH 3: Standard Instruction (Passthrough) */
                fprintf(f_output, "%s\t%s\t%s\n", label, opcode, operand);
            }
        }
    }

    printf("----------------------------------------------\n");
    printf("Expansion State: Completed.\n");
    printf("Output Artifact: MACRO_OUTPUT.txt\n");
    printf("==============================================\n");

    // Resource Cleanup
    fclose(f_input);
    fclose(f_namtab);
    fclose(f_deftab);
    fclose(f_output);

    return 0;
}
