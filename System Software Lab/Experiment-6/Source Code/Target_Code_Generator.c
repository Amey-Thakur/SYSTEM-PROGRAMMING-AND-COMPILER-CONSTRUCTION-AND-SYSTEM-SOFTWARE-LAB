/*
 * =========================================================================================
 * Experiment 6: Target Code Generation
 * Course: System Programming and Compiler Construction (SPCC)
 * 
 * Author: Amey Thakur
 * GitHub: https://github.com/Amey-Thakur
 * Repository: https://github.com/Amey-Thakur/SYSTEM-PROGRAMMING-AND-COMPILER-CONSTRUCTION-AND-SYSTEM-SOFTWARE-LAB
 * =========================================================================================
 * 
 * TECHNICAL LOGIC EXPLANATION:
 * This program simulates the final stage of a compiler: Target Code Generation. It 
 * translates intermediate arithmetic operations into low-level assembly language 
 * instructions targeting a hypothetical CPU architecture.
 * 
 * Generation Logic:
 * 1. Data Retrieval: The program uses 'MOV' (Move) instructions to load variable 
 *    values into processor registers (R1, R2).
 * 2. Execution: Based on the high-level operator (+, -, *, /), it selects the 
 *    corresponding machine-level instruction (ADD, SUB, MUL, DIV).
 * 3. Synchronization: The calculated result, currently residing in a register, is 
 *    transferred back to the permanent memory location (target variable).
 * 4. Pseudo-Assembly Mapping:
 *    - Addition -> ADD
 *    - Subtraction -> SUB
 *    - Multiplication -> MUL
 *    - Division -> DIV
 */

#include <stdio.h>
#include <string.h>

/**
 * INSTRUCTION GENERATION ENGINE
 * Outputs assembly commands based on high-level expression parameters.
 * 
 * Parameters:
 * op1, op2: Source variable names representing the numeric inputs.
 * op_type: Integer code mapped to the desired arithmetic operation.
 * result: The destination variable for the computed value.
 */
void generate_target_code(char op1, char op2, int op_type, char result) {
    printf("\n[LOG] Target Code Generation Sequence Initiated...\n");
    
    // Step 1: Loading operands into CPU registers
    printf("  MOV R1, %c\n", op1);
    printf("  MOV R2, %c\n", op2);
    
    // Step 2: Mapping operator to hardware instruction
    switch (op_type) {
        case 1:
            printf("  ADD R1, R2\n");
            break;
        case 2:
            printf("  SUB R1, R2\n");
            break;
        case 3:
            printf("  MUL R1, R2\n");
            break;
        case 4:
            printf("  DIV R1, R2\n");
            break;
        default:
            printf("  Error: Logic Failure - Unknown Instruction Code\n");
            return;
    }
    
    // Step 3: Storing result back to memory
    printf("  MOV %c, R1\n", result);
}

int main() {
    int choice = 0;
    char target = 'X', var1 = 'A', var2 = 'B';

    printf("\n==============================================\n");
    printf("           TARGET CODE GENERATOR             \n");
    printf("==============================================\n");
    printf("Current Operation Context: %c = %c (OP) %c\n", target, var1, var2);
    printf("----------------------------------------------\n");
    printf("System Instruction Menu:\n");
    printf("  1. Map to ADD (Addition)\n");
    printf("  2. Map to SUB (Subtraction)\n");
    printf("  3. Map to MUL (Multiplication)\n");
    printf("  4. Map to DIV (Division)\n");
    printf("----------------------------------------------\n");
    printf("Selection Input (1-4): ");
    
    // Handling user control flow
    if (scanf("%d", &choice) != 1) {
        printf("Termination Error: Non-numeric input detected.\n");
        return 1;
    }

    if (choice < 1 || choice > 4) {
        printf("Input Validation Error: Selection out of logical bounds.\n");
    } else {
        generate_target_code(var1, var2, choice, target);
    }

    printf("==============================================\n");
    
    return 0;
}
