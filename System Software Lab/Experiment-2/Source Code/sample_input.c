/*
 * Experiment 2: Lexical Analysis - Sample Input Source
 * Course: System Programming and Compiler Construction (SPCC)
 * 
 * Author: Amey Thakur
 * GitHub: https://github.com/Amey-Thakur
 * Repository: https://github.com/Amey-Thakur/SYSTEM-PROGRAMMING-AND-COMPILER-CONSTRUCTION-AND-SYSTEM-SOFTWARE-LAB
 * 
 * Description:
 * This is a sample C program used to test the lexical analyzer implementations
 * (both LEX and Manual). It contains keywords, identifiers, constants, 
 * and various operators.
 */

#include <stdio.h>

/**
 * Main function to demonstrate simple addition.
 * This code serves as input for the lexical analyzers.
 */
int main() {
    int first_number = 10;
    int second_number = 20;
    int sum;

    /* Perform addition */
    sum = first_number + second_number;

    printf("Calculation: %d + %d = %d\n", first_number, second_number, sum);

    if (sum > 25) {
        printf("The sum is greater than 25.\n");
    }

    return 0;
}
