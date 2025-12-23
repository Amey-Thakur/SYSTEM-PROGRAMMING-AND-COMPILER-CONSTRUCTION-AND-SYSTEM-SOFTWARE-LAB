%{
/*
 * Experiment 10.1: Integer Recognizer using LEX
 * Course: System Programming and Compiler Construction (SPCC)
 * 
 * Author: Amey Thakur
 * GitHub: https://github.com/Amey-Thakur
 * Repository: https://github.com/Amey-Thakur/SYSTEM-PROGRAMMING-AND-COMPILER-CONSTRUCTION-AND-SYSTEM-SOFTWARE-LAB
 * 
 * Description:
 * This LEX program identifies and prints integer sequences from the input.
 */

#include <stdio.h>
%}

/* Rule Section */
%%
[0-9]+ {
    printf("\n[Lexeme: %s] -> Recognized as Integer\n", yytext);
}

.|\n {
    /* Ignore other characters */
}
%%

/* User Code Section */
int yywrap() {
    return 1;
}

int main(void) {
    printf("==============================================\n");
    printf("           INTEGER RECOGNIZER (LEX)          \n");
    printf("==============================================\n");
    printf("Enter input text (press Ctrl+D/Ctrl+Z to end):\n");
    
    yylex();
    
    printf("\n==============================================\n");
    return 0;
}
