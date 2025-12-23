/*
 * =========================================================================================
 * Experiment 5: Code Optimization Techniques
 * Course: System Programming and Compiler Construction (SPCC)
 * 
 * Author: Amey Thakur
 * GitHub: https://github.com/Amey-Thakur
 * Repository: https://github.com/Amey-Thakur/SYSTEM-PROGRAMMING-AND-COMPILER-CONSTRUCTION-AND-SYSTEM-SOFTWARE-LAB
 * =========================================================================================
 * 
 * TECHNICAL LOGIC EXPLANATION:
 * This program demonstrates fundamental compiler optimization passes used to improve 
 * execution efficiency and reduce program size.
 * 
 * Implemented Techniques:
 * 1. Dead Code Elimination (DCE): 
 *    Identifies expressions whose results are never utilized by subsequent operations. 
 *    Such "dead" instructions are safely removed without changing the program's output.
 * 2. Common Subexpression Elimination (CSE): 
 *    Detects redundant calculations where the same arithmetic operation is performed 
 *    multiple times. It replaces subsequent identical calculations with a reference 
 *    to the result of the first one.
 * 
 * Operational Logic:
 * - Data Storage: Expressions are stored in a structured format containing the Left-Hand 
 *   Side (LHS - variable being assigned) and Right-Hand Side (RHS - the formula).
 * - Liveness Analysis: For DCE, the program scans backwards to see if a variable's 
 *   assignment is actually read later.
 * - String Comparison: For CSE, it looks for identical RHS strings across the code block.
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_EXPR 10

/**
 * DATA STRUCTURE: EXPRESSION
 * Encapsulates a standard assignment operation (e.g., A = B + C).
 */
typedef struct {
    char lhs;
    char rhs[20];
} Expression;

Expression exprs[MAX_EXPR], optimized[MAX_EXPR];
int num_exprs = 0, opt_count = 0;

/**
 * OPTIMIZATION PASS: DEAD CODE ELIMINATION
 * Analyzes the 'liveness' of each expression's LHS.
 */
void dead_code_elimination() {
    int live_indices[MAX_EXPR] = {0};
    opt_count = 0;

    /* Logic: The final result of a code block is always considered "live" (output). */
    live_indices[num_exprs - 1] = 1;

    /* Scan expressions in reverse order to determine if their outputs are used. */
    for (int i = num_exprs - 2; i >= 0; i--) {
        char target = exprs[i].lhs;
        // Search all subsequent (future) expressions to see if they read 'target'.
        for (int j = i + 1; j < num_exprs; j++) {
            if (strchr(exprs[j].rhs, target)) {
                live_indices[i] = 1; // Mark as useful/live
                break;
            }
        }
    }

    /* Compile the list of non-dead expressions into the optimized buffer. */
    for (int i = 0; i < num_exprs; i++) {
        if (live_indices[i]) {
            optimized[opt_count++] = exprs[i];
        }
    }
}

/**
 * OPTIMIZATION PASS: COMMON SUBEXPRESSION ELIMINATION
 * Reduces computational redundancy by removing duplicate math operations.
 */
void common_subexpression_elimination() {
    for (int i = 0; i < opt_count; i++) {
        for (int j = i + 1; j < opt_count; j++) {
            /* If the math operation (RHS) is identical to a previous one. */
            if (strcmp(optimized[i].rhs, optimized[j].rhs) == 0) {
                char old_var = optimized[j].lhs;
                char new_var = optimized[i].lhs;
                
                /* Propagate optimization: Re-route future code to use the existing result. */
                for (int k = j + 1; k < opt_count; k++) {
                    char *pos;
                    while ((pos = strchr(optimized[k].rhs, old_var)) != NULL) {
                        *pos = new_var;
                    }
                }
                /* Flag the redundant expression for physical removal. */
                optimized[j].lhs = '\0';
            }
        }
    }

    /* Maintenance: Collapse the array to remove the empty slots left by flagged expressions. */
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

    /* INPUT PHASE: Capture the intermediate code segment. */
    printf("Enter the number of expressions: ");
    if (scanf("%d", &num_exprs) != 1) return 1;

    for (int i = 0; i < num_exprs; i++) {
        printf("Expression %d Configuration:\n", i + 1);
        printf("  Variable Name (LHS): "); scanf(" %c", &exprs[i].lhs);
        printf("  Math Operation (RHS): "); scanf(" %s", exprs[i].rhs);
    }

    /* STATUS: Original source visualization. */
    printf("\n--- INPUT: Original Code Stream ---\n");
    for (int i = 0; i < num_exprs; i++) {
        printf("%c = %s\n", exprs[i].lhs, exprs[i].rhs);
    }

    /* EXECUTION: Layer 1 Optimization. */
    dead_code_elimination();
    printf("\n--- LOG: Post Dead Code Elimination ---\n");
    for (int i = 0; i < opt_count; i++) {
        printf("%c = %s\n", optimized[i].lhs, optimized[i].rhs);
    }

    /* EXECUTION: Layer 2 Optimization. */
    common_subexpression_elimination();
    printf("\n--- LOG: Post Common Subexpression Elimination ---\n");
    for (int i = 0; i < opt_count; i++) {
        printf("%c = %s\n", optimized[i].lhs, optimized[i].rhs);
    }

    /* FINAL OUTPUT REVEAL */
    printf("\n==============================================\n");
    printf("           FINAL OPTIMIZED OUTPUT             \n");
    printf("==============================================\n");
    for (int i = 0; i < opt_count; i++) {
        printf("%c = %s\n", optimized[i].lhs, optimized[i].rhs);
    }
    printf("==============================================\n");

    return 0;
}
