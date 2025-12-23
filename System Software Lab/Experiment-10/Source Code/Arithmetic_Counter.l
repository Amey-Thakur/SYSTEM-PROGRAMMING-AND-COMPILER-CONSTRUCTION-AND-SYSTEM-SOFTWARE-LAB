%{
/*
 * Experiment 10.2: Arithmetic Counter using LEX
 * Course: System Programming and Compiler Construction (SPCC)
 * 
 * Author: Amey Thakur
 * GitHub: https://github.com/Amey-Thakur
 * Repository: https://github.com/Amey-Thakur/SYSTEM-PROGRAMMING-AND-COMPILER-CONSTRUCTION-AND-SYSTEM-SOFTWARE-LAB
 * 
 * Description:
 * This LEX program counts the number of integers encountered and 
 * prints the count when a lowercase character is entered.
 */

#include <stdio.h>
int integer_count = 0;
%}

/* Rule Section */
%%
[0-9]+ {
    integer_count++;
    printf(" [Integer Detected: %s | Running Count: %d]\n", yytext, integer_count);
}

[a-z] {
    printf("\n--- Result Summary ---\n");
    printf("Total Integers Counted: %d\n", integer_count);
    printf("Trigger Character: '%s'\n", yytext);
    printf("----------------------\n");
}

.|\n {
    /* Ignore whitespace and other characters */
}
%%

/* User Code Section */
int yywrap() {
    return 1;
}

int main(void) {
    printf("==============================================\n");
    printf("           ARITHMETIC COUNTER (LEX)           \n");
    printf("==============================================\n");
    printf("1. Enter numbers to increment the count.\n");
    printf("2. Enter any lowercase letter (a-z) to view total.\n");
    printf("----------------------------------------------\n");
    
    yylex();
    
    return 0;
}
