/*
 * Experiment 5: Code Optimization Techniques
 * Course: System Programming and Compiler Construction (SPCC)
 * 
 * Author: Amey Thakur
 * GitHub: https://github.com/Amey-Thakur
 * Repository: https://github.com/Amey-Thakur/SYSTEM-PROGRAMMING-AND-COMPILER-CONSTRUCTION-AND-SYSTEM-SOFTWARE-LAB
 * 
 * Description:
 * This program implements basic code optimization techniques:
 * 1. Dead Code Elimination: Removing expressions that are never used.
 * 2. Common Subexpression Elimination: Identifying and replacing redundant calculations.
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_EXPR 10

typedef struct {
    char lhs;
    char rhs[20];
} Expression;

Expression exprs[MAX_EXPR], optimized[MAX_EXPR];
int num_exprs = 0, opt_count = 0;

/**
 * Performs Dead Code Elimination.
 * An expression is considered "live" if its LHS appears in the RHS of a subsequent expression.
 */
void dead_code_elimination() {
    int live_indices[MAX_EXPR] = {0};
    opt_count = 0;

    // Mark the last expression as live by default (output)
    live_indices[num_exprs - 1] = 1;

    // Check for liveness upwards
    for (int i = num_exprs - 2; i >= 0; i--) {
        char target = exprs[i].lhs;
        for (int j = i + 1; j < num_exprs; j++) {
            if (strchr(exprs[j].rhs, target)) {
                live_indices[i] = 1;
                break;
            }
        }
    }

    // Collect live expressions
    for (int i = 0; i < num_exprs; i++) {
        if (live_indices[i]) {
            optimized[opt_count++] = exprs[i];
        }
    }
}

/**
 * Performs Common Subexpression Elimination.
 */
void common_subexpression_elimination() {
    for (int i = 0; i < opt_count; i++) {
        for (int j = i + 1; j < opt_count; j++) {
            if (strcmp(optimized[i].rhs, optimized[j].rhs) == 0) {
                char old_var = optimized[j].lhs;
                char new_var = optimized[i].lhs;
                
                // Replace all occurrences of old_var with new_var in subsequent expressions
                for (int k = j + 1; k < opt_count; k++) {
                    char *pos;
                    while ((pos = strchr(optimized[k].rhs, old_var)) != NULL) {
                        *pos = new_var;
                    }
                }
                // Mark the redundant expression for removal
                optimized[j].lhs = '\0';
            }
        }
    }

    // Shift expressions to remove gaps
    int shift = 0;
    for (int i = 0; i < opt_count; i++) {
        if (optimized[i].lhs == '\0') {
            shift++;
        } else if (shift > 0) {
            optimized[i - shift] = optimized[i];
        }
    }
    opt_count -= shift;
}

int main() {
    printf("\n==============================================\n");
    printf("         CODE OPTIMIZATION CALCULATOR        \n");
    printf("==============================================\n");

    printf("Enter the number of expressions: ");
    if (scanf("%d", &num_exprs) != 1) return 1;

    for (int i = 0; i < num_exprs; i++) {
        printf("Expression %d (LHS=RHS): ", i + 1);
        printf("\n  LHS: "); scanf(" %c", &exprs[i].lhs);
        printf("  RHS: "); scanf(" %s", exprs[i].rhs);
    }

    printf("\n--- Original Intermediate Code ---\n");
    for (int i = 0; i < num_exprs; i++) {
        printf("%c = %s\n", exprs[i].lhs, exprs[i].rhs);
    }

    /* Step 1: Dead Code Elimination */
    dead_code_elimination();
    printf("\n--- After Dead Code Elimination ---\n");
    for (int i = 0; i < opt_count; i++) {
        printf("%c = %s\n", optimized[i].lhs, optimized[i].rhs);
    }

    /* Step 2: Common Subexpression Elimination */
    common_subexpression_elimination();
    printf("\n--- After Common Subexpression Elimination ---\n");
    for (int i = 0; i < opt_count; i++) {
        printf("%c = %s\n", optimized[i].lhs, optimized[i].rhs);
    }

    printf("\n==============================================\n");
    printf("           FINAL OPTIMIZED CODE              \n");
    printf("==============================================\n");
    for (int i = 0; i < opt_count; i++) {
        printf("%c = %s\n", optimized[i].lhs, optimized[i].rhs);
    }
    printf("==============================================\n");

    return 0;
}
