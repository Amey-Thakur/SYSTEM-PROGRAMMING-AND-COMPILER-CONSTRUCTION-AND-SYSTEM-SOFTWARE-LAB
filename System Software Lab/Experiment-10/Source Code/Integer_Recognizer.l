%{
/*
 * =========================================================================================
 * Experiment 10.1: Integer Recognizer using LEX
 * Course: System Programming and Compiler Construction (SPCC)
 * 
 * Author: Amey Thakur
 * GitHub: https://github.com/Amey-Thakur
 * Repository: https://github.com/Amey-Thakur/SYSTEM-PROGRAMMING-AND-COMPILER-CONSTRUCTION-AND-SYSTEM-SOFTWARE-LAB
 * =========================================================================================
 * 
 * TECHNICAL LOGIC EXPLANATION:
 * This program serves as a specialized pattern matcher designed to extract and identify 
 * whole numbers (integers) from a stream of text data.
 * 
 * Detection Logic:
 * 1. Rule Definition: The regular expression [0-9]+ specifies a pattern where one 
 *    or more numeric digits occur consecutively.
 * 2. Scan Phase: The LEX engine evaluates incoming text against this pattern.
 * 3. Identification: When a match is secured, the program identifies the segment 
 *    as a 'Lexeme' of type 'Integer' and logs its value.
 * 4. Filtering: Any characters that do not conform to the numeric pattern (like 
 *    letters or symbols) are filtered out and discarded.
 */

#include <stdio.h>
%}

/* 
 * PATTERN RULES SECTION 
 */
%%
[0-9]+ {
    /* Action: Print the successfully matched numeric sequence */
    printf("\n[REPORT] Lexeme identified: %s | Result: Valid Integer\n", yytext);
}

.|\n {
    /* Action: Silence (Ignore all non-numeric characters and whitespace) */
}
%%

/* 
 * USER EXECUTION LOGIC 
 */

/* Required function to handle single-input source completion */
int yywrap() {
    return 1;
}

int main(void) {
    printf("==============================================\n");
    printf("           INTEGER RECOGNIZER (LEX)          \n");
    printf("==============================================\n");
    printf("Operation: Extracting numeric patterns from input.\n");
    printf("Usage: Type input and observe extraction results.\n");
    printf("Input Stream (End with Ctrl+D / Ctrl+Z):\n");
    
    /* Initiating the scanner engine */
    yylex();
    
    printf("\n==============================================\n");
    return 0;
}
