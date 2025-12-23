/*
 * Experiment 2: Lexical Analysis (Manual Implementation in C)
 * Course: System Programming and Compiler Construction (SPCC)
 * 
 * Author: Amey Thakur
 * GitHub: https://github.com/Amey-Thakur
 * Repository: https://github.com/Amey-Thakur/SYSTEM-PROGRAMMING-AND-COMPILER-CONSTRUCTION-AND-SYSTEM-SOFTWARE-LAB
 * 
 * Description:
 * This C program performs lexical analysis on a source file manually
 * without using LEX or other tools. It categorizes tokens into
 * keywords, identifiers, and operators.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/**
 * Checks if a given string is a C keyword.
 * @param buffer The string to check.
 * @return 1 if it's a keyword, 0 otherwise.
 */
int is_keyword(char buffer[]) {
    char keywords[32][10] = {
        "auto", "break", "case", "char", "const", "continue", "default",
        "do", "double", "else", "enum", "extern", "float", "for", "goto",
        "if", "int", "long", "register", "return", "short", "signed",
        "sizeof", "static", "struct", "switch", "typedef", "union",
        "unsigned", "void", "volatile", "while"
    };
    
    for (int i = 0; i < 32; ++i) {
        if (strcmp(keywords[i], buffer) == 0) {
            return 1;
        }
    }
    return 0;
}

int main() {
    char ch, buffer[50], operators[] = "+-*/%=";
    FILE *fp;
    int i, j = 0;
    char *input_file = "sample_input.c";

    fp = fopen(input_file, "r");

    if (fp == NULL) {
        printf("\nError: Could not open file %s\n", input_file);
        exit(1);
    }

    printf("\n==============================================\n");
    printf("      Manual Lexical Analyzer (C Version)      \n");
    printf("==============================================\n");
    printf("Reading from: %s\n\n", input_file);

    while ((ch = fgetc(fp)) != EOF) {
        // Check for operators
        for (i = 0; i < 6; ++i) {
            if (ch == operators[i]) {
                printf("Operator: %c\n", ch);
            }
        }

        // Build identifiers or numbers
        if (isalnum(ch) || ch == '_') {
            buffer[j++] = ch;
        } else if ((isspace(ch) || strchr(",;()[]{}", ch)) && (j != 0)) {
            buffer[j] = '\0';
            j = 0;

            if (is_keyword(buffer)) {
                printf("Keyword:  %s\n", buffer);
            } else {
                printf("Identifier: %s\n", buffer);
            }
        }
        
        // Handle standalone delimiters
        if (strchr(",;()[]{}", ch)) {
            printf("Delimiter: %c\n", ch);
        }
    }

    fclose(fp);
    printf("\n==============================================\n");
    return 0;
}
