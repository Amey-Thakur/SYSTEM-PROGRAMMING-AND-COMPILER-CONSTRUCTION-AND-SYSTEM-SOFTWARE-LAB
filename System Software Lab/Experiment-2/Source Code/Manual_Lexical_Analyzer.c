/*
 * =========================================================================================
 * Experiment 2: Lexical Analysis (Manual Implementation in C)
 * Course: System Programming and Compiler Construction (SPCC)
 * 
 * Author: Amey Thakur
 * GitHub: https://github.com/Amey-Thakur
 * Repository: https://github.com/Amey-Thakur/SYSTEM-PROGRAMMING-AND-COMPILER-CONSTRUCTION-AND-SYSTEM-SOFTWARE-LAB
 * =========================================================================================
 * 
 * TECHNICAL LOGIC EXPLANATION:
 * This program performs lexical analysis manually by reading the input source file 
 * character by character and categorizing sequences into valid language components.
 * 
 * Procedural Steps:
 * 1. Stream Reading: The program opens a file stream and examines each individual 
 *    character (ch).
 * 2. Character Aggregation: If characters are Alphanumeric, they are buffered to 
 *    form a "word" or "lexeme".
 * 3. Classification: When a word boundary (like a space or delimiter) is detected, 
 *    the program checks its "Keyword" dictionary. If it matches, it is classified 
 *    as a Keyword; otherwise, it is labeled an Identifier.
 * 4. Symbol Detection: Mathematical symbols (Operators) and Structural symbols 
 *    (Delimiters) are recognized instantly as they are encountered.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/**
 * KEYWORD DICTIONARY LOOKUP
 * Compares the identified lexeme against a predefined list of reserved language tokens.
 */
int is_keyword(char buffer[]) {
    char keywords[32][10] = {
        "auto", "break", "case", "char", "const", "continue", "default",
        "do", "double", "else", "enum", "extern", "float", "for", "goto",
        "if", "int", "long", "register", "return", "short", "signed",
        "sizeof", "static", "struct", "switch", "typedef", "union",
        "unsigned", "void", "volatile", "while"
    };
    
    // Linear search through the internal dictionary for a match.
    for (int i = 0; i < 32; ++i) {
        if (strcmp(keywords[i], buffer) == 0) {
            return 1; // True: The token is a reserved keyword.
        }
    }
    return 0; // False: The token is not a keyword (likely an identifier).
}

int main() {
    char ch, buffer[50], operators[] = "+-*/%=";
    FILE *fp;
    int i, j = 0;
    char *input_file = "sample_input.c";

    // Establishing a read-only stream from the target file.
    fp = fopen(input_file, "r");

    if (fp == NULL) {
        printf("\nError: Input file could not be accessed: %s\n", input_file);
        exit(1);
    }

    printf("\n==============================================\n");
    printf("      Manual Lexical Analyzer (C Version)      \n");
    printf("==============================================\n");
    printf("Source File: %s\n\n", input_file);

    // Iterating through the character stream until the End-of-File indicator is met.
    while ((ch = fgetc(fp)) != EOF) {
        
        // Logical Step: Immediate detection for Operator symbols.
        for (i = 0; i < 6; ++i) {
            if (ch == operators[i]) {
                printf("Token: Operator  | Value: %c\n", ch);
            }
        }

        // Logical Step: Aggregation of alphanumeric characters into a localized buffer.
        if (isalnum(ch) || ch == '_') {
            buffer[j++] = ch; 
        } 
        
        // Logical Step: Word boundary detection (Whitespace or special characters).
        else if ((isspace(ch) || strchr(",;()[]{}", ch)) && (j != 0)) {
            buffer[j] = '\0'; // Null-terminating the collected sequence.
            j = 0; // Resetting buffer index for the next sequence.

            // Classification of the identified sequence.
            if (is_keyword(buffer)) {
                printf("Token: Keyword   | Value: %s\n", buffer);
            } else {
                printf("Token: Identifier| Value: %s\n", buffer);
            }
        }
        
        // Logical Step: Standalone detection for structural Delimiters.
        if (strchr(",;()[]{}", ch)) {
            printf("Token: Delimiter | Value: %c\n", ch);
        }
    }

    fclose(fp); // Proper release of the file system resource.
    printf("\n==============================================\n");
    return 0;
}
