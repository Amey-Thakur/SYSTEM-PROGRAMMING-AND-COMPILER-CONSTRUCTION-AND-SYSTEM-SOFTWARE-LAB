/*
 * =========================================================================================
 * Experiment 2: Lexical Analysis - Sample Input Source
 * Course: System Programming and Compiler Construction (SPCC)
 * 
 * Author: Amey Thakur
 * GitHub: https://github.com/Amey-Thakur
 * Repository: https://github.com/Amey-Thakur/SYSTEM-PROGRAMMING-AND-COMPILER-CONSTRUCTION-AND-SYSTEM-SOFTWARE-LAB
 * =========================================================================================
 * 
 * TECHNICAL LOGIC EXPLANATION:
 * This code serves as a standardized test bench for validating the performance and accuracy 
 * of lexical analyzers. It contains a representative sample of C-language syntax, 
 * including diverse token categories.
 * 
 * Target Lexical Categories:
 * 1. Keywords: 'int', 'return', 'if', 'void'.
 * 2. Identifiers: 'first_number', 'second_number', 'sum', 'main'.
 * 3. Constants: Numeric literals such as '10', '20', and '25'.
 * 4. Operators: Arithmetic (+) and Assignment (=) symbols.
 * 5. Punctuators: Semicolons (;), Braces ({}), and Parentheses (()).
 * 6. String Literals: Text data enclosed in double quotes.
 */

#include <stdio.h>

/**
 * ENTRY POINT: MAIN FUNCTION
 * Implements a basic arithmetic operation to provide a valid token stream 
 * for the scanning engine.
 */
int main() {
    int first_number = 10;
    int second_number = 20;
    int sum;

    /* LOGICAL STEP: Arithmetic summation of integer variables. */
    sum = first_number + second_number;

    printf("Calculation: %d + %d = %d\n", first_number, second_number, sum);

    // Conditional evaluation logic
    if (sum > 25) {
        printf("Verification: Sum exceeds threshold of 25.\n");
    }

    return 0;
}
