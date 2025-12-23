/*
 * Experiment 6: Target Code Generation
 * Course: System Programming and Compiler Construction (SPCC)
 * 
 * Author: Amey Thakur
 * GitHub: https://github.com/Amey-Thakur
 * Repository: https://github.com/Amey-Thakur/SYSTEM-PROGRAMMING-AND-COMPILER-CONSTRUCTION-AND-SYSTEM-SOFTWARE-LAB
 * 
 * Description:
 * This program demonstrates the generation of target assembly code (pseudo-code)
 * for simple arithmetic expressions. It converts high-level operations into
 * MOV and arithmetic instructions.
 */

#include <stdio.h>
#include <string.h>

/**
 * Generates assembly code for a given set of operands and an operator.
 * @param op1 First operand
 * @param op2 Second operand
 * @param op_type Operator selection (1:+, 2:-, 3:*, 4:/)
 * @param result Target variable
 */
void generate_target_code(char op1, char op2, int op_type, char result) {
    printf("\n--- Generated Target Code ---\n");
    printf("MOV R1, %c\n", op1);
    printf("MOV R2, %c\n", op2);

    switch (op_type) {
        case 1:
            printf("ADD R1, R2\n");
            break;
        case 2:
            printf("SUB R1, R2\n");
            break;
        case 3:
            printf("MUL R1, R2\n");
            break;
        case 4:
            printf("DIV R1, R2\n");
            break;
        default:
            printf("Error: Invalid Operator\n");
            return;
    }
    printf("MOV %c, R1\n", result);
}

int main() {
    int choice = 0;
    char target = 'X', var1 = 'A', var2 = 'B';

    printf("\n==============================================\n");
    printf("           TARGET CODE GENERATOR             \n");
    printf("==============================================\n");
    printf("Expression: %c = %c OP %c\n", target, var1, var2);
    printf("----------------------------------------------\n");
    printf("Select Operator:\n");
    printf("  1. Addition (+)\n");
    printf("  2. Subtraction (-)\n");
    printf("  3. Multiplication (*)\n");
    printf("  4. Division (/)\n");
    printf("----------------------------------------------\n");
    printf("Enter Choice (1-4): ");
    
    if (scanf("%d", &choice) != 1) {
        printf("Invalid input.\n");
        return 1;
    }

    if (choice < 1 || choice > 4) {
        printf("Invalid choice selection.\n");
    } else {
        generate_target_code(var1, var2, choice, target);
    }

    printf("==============================================\n");
    
    return 0;
}
