/*
 * Experiment 4: Recursive Descent Parser Implementation
 * Course: System Programming and Compiler Construction (SPCC)
 * 
 * Author: Amey Thakur
 * GitHub: https://github.com/Amey-Thakur
 * Repository: https://github.com/Amey-Thakur/SYSTEM-PROGRAMMING-AND-COMPILER-CONSTRUCTION-AND-SYSTEM-SOFTWARE-LAB
 * 
 * Description:
 * This program implements a Recursive Descent Parser for basic arithmetic 
 * expressions including addition, subtraction, multiplication, and division.
 * It uses a top-down parsing approach to validate input strings.
 */

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define SIZE 128
#define NONE -1
#define EOS '\0'
#define NUM 257
#define ID 259
#define DONE 260
#define MAX_LEXEMES 999

/* Global Variables */
char lexemes[MAX_LEXEMES];
char buffer[SIZE];
int last_char = -1;
int last_entry = 0;
int token_value = DONE;
int line_no = 1;
int lookahead;

typedef struct {
    char *lexptr;
    int token;
} SymbolEntry;

SymbolEntry symbol_table[100];

/**
 * Reports an error and terminates the program.
 * @param message The error message to display.
 */
void report_error(const char *message) {
    fprintf(stderr, "\nError at line %d: %s\n", line_no, message);
    exit(1);
}

/**
 * Looks up a lexeme in the symbol table.
 * @param s Lexeme string.
 * @return Index in symbol table, or 0 if not found.
 */
int lookup(char s[]) {
    for (int k = last_entry; k > 0; k--) {
        if (strcmp(symbol_table[k].lexptr, s) == 0)
            return k;
    }
    return 0;
}

/**
 * Inserts a lexeme into the symbol table.
 * @param s Lexeme string.
 * @param tok Token type.
 * @return Index of the new entry.
 */
int insert(char s[], int tok) {
    int len = strlen(s);
    if (last_entry + 1 >= 100) report_error("Symbol table is full");
    if (last_char + len + 1 >= MAX_LEXEMES) report_error("Lexemes array is full");

    last_entry++;
    symbol_table[last_entry].token = tok;
    symbol_table[last_entry].lexptr = &lexemes[last_char + 1];
    last_char += len + 1;
    strcpy(symbol_table[last_entry].lexptr, s);
    return last_entry;
}

/**
 * Lexical analyzer to return tokens.
 * @return Token type.
 */
int lexer() {
    int t;
    int val, i = 0;
    while (1) {
        t = getchar();
        if (t == ' ' || t == '\t'); // Skip whitespace
        else if (t == '\n') line_no++;
        else if (isdigit(t)) {
            ungetc(t, stdin);
            if (scanf("%d", &token_value) != 1) report_error("Invalid number format");
            return NUM;
        } else if (isalpha(t)) {
            while (isalnum(t)) {
                buffer[i++] = t;
                t = getchar();
                if (i >= SIZE) report_error("Identifier too long");
            }
            buffer[i] = EOS;
            if (t != EOF) ungetc(t, stdin);

            val = lookup(buffer);
            if (val == 0) val = insert(buffer, ID);
            token_value = val;
            return symbol_table[val].token;
        } else if (t == EOF) {
            return DONE;
        } else {
            token_value = NONE;
            return t;
        }
    }
}

/**
 * Matches the current lookahead token with the expected token.
 * @param t Expected token.
 */
void match(int t) {
    if (lookahead == t) {
        lookahead = lexer();
    } else {
        report_error("Syntax error - Unmatched token");
    }
}

/**
 * Displays token information.
 */
void display_token(int t, int tval) {
    if (strchr("+-*/", t)) printf("\nArithmetic Operator: %c", t);
    else if (t == NUM) printf("\nNumber: %d", tval);
    else if (t == ID) printf("\nIdentifier: %s", symbol_table[tval].lexptr);
}

/* Grammar Rules: 
 * E -> T E'
 * T -> F T'
 * F -> ( E ) | id | num
 */

void E(); // Forward declaration

void F() {
    switch (lookahead) {
        case '(':
            match('(');
            E();
            match(')');
            break;
        case NUM:
            display_token(NUM, token_value);
            match(NUM);
            break;
        case ID:
            display_token(ID, token_value);
            match(ID);
            break;
        default:
            report_error("Syntax error in Factor");
    }
}

void T() {
    F();
    while (lookahead == '*' || lookahead == '/') {
        int op = lookahead;
        match(lookahead);
        F();
        display_token(op, NONE);
    }
}

void E() {
    T();
    while (lookahead == '+' || lookahead == '-') {
        int op = lookahead;
        match(lookahead);
        T();
        display_token(op, NONE);
    }
}

/**
 * Start the parser.
 */
void start_parser() {
    lookahead = lexer();
    while (lookahead != DONE) {
        E();
        if (lookahead == ';') {
            match(';');
            printf("\n--- Expression parsed successfully ---\n");
        } else if (lookahead != DONE) {
            report_error("Missing semicolon at end of expression");
        }
    }
}

int main() {
    printf("\n==============================================\n");
    printf("        RECURSIVE DESCENT PARSER (SPCC)        \n");
    printf("==============================================\n");
    printf("Enter arithmetic expressions (e.g., a + b * 2;)\n");
    printf("End each expression with a semicolon (;)\n");
    printf("Press Ctrl+Z (Windows) or Ctrl+D (Linux) to exit.\n\n");
    
    start_parser();
    
    printf("\n==============================================\n");
    return 0;
}
