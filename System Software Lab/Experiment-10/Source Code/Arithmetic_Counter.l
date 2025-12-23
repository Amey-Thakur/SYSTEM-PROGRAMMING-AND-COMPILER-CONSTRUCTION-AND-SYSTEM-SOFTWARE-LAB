%{
/*
 * =========================================================================================
 * Experiment 10.2: Arithmetic Counter using LEX
 * Course: System Programming and Compiler Construction (SPCC)
 * 
 * Author: Amey Thakur
 * GitHub: https://github.com/Amey-Thakur
 * Repository: https://github.com/Amey-Thakur/SYSTEM-PROGRAMMING-AND-COMPILER-CONSTRUCTION-AND-SYSTEM-SOFTWARE-LAB
 * =========================================================================================
 * 
 * TECHNICAL LOGIC EXPLANATION:
 * This program implements a state-ful pattern analyzer that maintains a real-time 
 * count of specific lexical tokens (integers) within the input stream.
 * 
 * Operational Logic:
 * 1. Accumulation: Whenever the numeric pattern [0-9]+ is matched, an internal 
 *    counter is incremented.
 * 2. Visual Feedback: Every match triggers a status update showing both the 
 *    detected value and the updated running total.
 * 3. Reporting Trigger: The program monitors for lowercase alphabetic characters 
 *    ([a-z]). Encountering such a character acts as a "Request Report" command, 
 *    prompting the system to display the final cumulative count.
 */

#include <stdio.h>
int integer_count = 0; // Global accumulator for numeric tokens
%}

/* 
 * RULE DEFINITIONS
 */
%%
[0-9]+ {
    /* Action: Update state and provide immediate detection feedback */
    integer_count++;
    printf(" [Status] Numeric Token Found: %s | Current Total: %d\n", yytext, integer_count);
}

[a-z] {
    /* Action: Trigger result summary and report generation */
    printf("\n--- CUMULATIVE RESULT SUMMARY ---\n");
    printf("Final Integer Count: %d\n", integer_count);
    printf("Reporting Triggered By: '%s'\n", yytext);
    printf("----------------------------------\n");
}

.|\n {
    /* Action: Ignore non-triggering characters */
}
%%

/* 
 * USER INTERFACE LOGIC 
 */

/* Required function to handle single-input source completion */
int yywrap() {
    return 1;
}

int main(void) {
    printf("==============================================\n");
    printf("           ARITHMETIC COUNTER (LEX)           \n");
    printf("==============================================\n");
    printf("Function: Continuous counting of numericlexemes.\n");
    printf("Control: Use lowercase letters [a-z] to fetch the current total.\n");
    printf("----------------------------------------------\n");
    
    /* Activating the LEX analysis engine */
    yylex();
    
    return 0;
}
