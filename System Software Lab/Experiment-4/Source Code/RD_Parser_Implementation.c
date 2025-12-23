/*
 * =========================================================================================
 * Experiment 4: Recursive Descent Parser Implementation
 * Course: System Programming and Compiler Construction (SPCC)
 * 
 * Author: Amey Thakur
 * GitHub: https://github.com/Amey-Thakur
 * Repository: https://github.com/Amey-Thakur/SYSTEM-PROGRAMMING-AND-COMPILER-CONSTRUCTION-AND-SYSTEM-SOFTWARE-LAB
 * =========================================================================================
 * 
 * TECHNICAL LOGIC EXPLANATION:
 * This program implements a Recursive Descent Parser, a top-down parsing technique 
 * where a set of recursive functions is used to check the syntax of an input expression.
 * 
 * Grammar Rules Implemented:
 * E  -> T E'         (Expression consists of a Term followed by optional additions)
 * E' -> + T E' | - T E' | epsilon
 * T  -> F T'         (Term consists of a Factor followed by optional multiplications)
 * T' -> * F T' | / F T' | epsilon
 * F  -> ( E ) | id | num (Factors can be parentheses, identifiers, or numbers)
 * 
 * Operational Logic:
 * 1. Lexing: The `lexer()` function breaks the input stream into tokens.
 * 2. Prediction: Each function (E, T, F) corresponds to a non-terminal in the grammar.
 * 3. Recursive Call: Functions call each other to handle nested sub-expressions 
 *    (e.g., handles parentheses by calling the start function 'E' again).
 * 4. Verification: If the lookahead token matches the grammar, the process continues; 
 *    otherwise, a syntax error is reported.
 */

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

/* Global Configuration Constants */
#define SIZE 128
#define NONE -1
#define EOS '\0'     // End of String
#define NUM 257     // Numeric Token Identifier
#define ID 259      // Identifier Token Indicator
#define DONE 260    // Processing Complete Flag
#define MAX_LEXEMES 999

/* Runtime State Tracking */
char lexemes[MAX_LEXEMES];
char buffer[SIZE];
int last_char = -1;
int last_entry = 0;
int token_value = DONE;
int line_no = 1;      // Tracking lines for error reporting
int lookahead;        // The token currently being analyzed

/**
 * SYMBOL TABLE ARCHITECTURE
 * Used to store and retrieve unique identifiers during the parsing process.
 */
typedef struct {
    char *lexptr;
    int token;
} SymbolEntry;

SymbolEntry symbol_table[100];

/**
 * ERROR HANDLING
 * Terminates execution and provides diagnostic information to the user.
 */
void report_error(const char *message) {
    fprintf(stderr, "\nFATAL ERROR (Line %d): %s\n", line_no, message);
    exit(1);
}

/**
 * SYMBOL TABLE MANAGEMENT
 * lookup: Checks if an identifier is already cataloged.
 * insert: Adds a new identifier to the internal record.
 */
int lookup(char s[]) {
    for (int k = last_entry; k > 0; k--) {
        if (strcmp(symbol_table[k].lexptr, s) == 0)
            return k;
    }
    return 0;
}

int insert(char s[], int tok) {
    int len = strlen(s);
    if (last_entry + 1 >= 100) report_error("Symbol Table Capacity Exceeded");
    if (last_char + len + 1 >= MAX_LEXEMES) report_error("Lexical Buffer Overflow");

    last_entry++;
    symbol_table[last_entry].token = tok;
    symbol_table[last_entry].lexptr = &lexemes[last_char + 1];
    last_char += len + 1;
    strcpy(symbol_table[last_entry].lexptr, s);
    return last_entry;
}

/**
 * LEXICAL ANALYSIS ENGINE
 * Character-level processing to identify tokens (Numbers, IDs, Operators).
 */
int lexer() {
    int t;
    int val, i = 0;
    while (1) {
        t = getchar();
        if (t == ' ' || t == '\t'); // Null action: Ignore standard spaces
        else if (t == '\n') line_no++;
        else if (isdigit(t)) {
            ungetc(t, stdin);
            if (scanf("%d", &token_value) != 1) report_error("Malformed numeric value detected");
            return NUM;
        } else if (isalpha(t)) {
            while (isalnum(t)) {
                buffer[i++] = t;
                t = getchar();
                if (i >= SIZE) report_error("Identifier length limit exceeded");
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
            return t; // Direct return for operators and delimiters
        }
    }
}

/**
 * PARSING UTILITIES
 * match: Compares the lookahead against expected grammar input and moves to the next token.
 */
void match(int t) {
    if (lookahead == t) {
        lookahead = lexer();
    } else {
        report_error("Syntax Violation: Unexpected token sequence");
    }
}

void display_token(int t, int tval) {
    if (strchr("+-*/", t)) printf("\n[TOKEN] Arithmetic Operator: %c", t);
    else if (t == NUM) printf("\n[TOKEN] Integer Constant: %d", tval);
    else if (t == ID) printf("\n[TOKEN] Literal Identifier: %s", symbol_table[tval].lexptr);
}

/**
 * RECURSIVE DESCENT FUNCTIONS
 * These represent the hierarchical levels of the grammar.
 */

void E(); // Forward declaration to allow recursive calls

/* F -> ( E ) | id | num */
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
            report_error("Syntax Violation: Invalid expression in Factor");
    }
}

/* T -> F { * F | / F } */
void T() {
    F();
    while (lookahead == '*' || lookahead == '/') {
        int op = lookahead;
        match(lookahead);
        F();
        display_token(op, NONE);
    }
}

/* E -> T { + T | - T } */
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
 * INITIALIZATION AND ORCHESTRATION
 */
void start_parser() {
    lookahead = lexer(); // Priming the scanner
    while (lookahead != DONE) {
        E();
        if (lookahead == ';') { // Every expression must conclude with a semicolon
            match(';');
            printf("\n--- Result: Expression Validation Successful ---\n");
        } else if (lookahead != DONE) {
            report_error("Terminator Missing: Expressions must end with ';'");
        }
    }
}

int main() {
    printf("\n==============================================\n");
    printf("        RECURSIVE DESCENT PARSER (SPCC)        \n");
    printf("==============================================\n");
    printf("Input: Arithmetic expressions concludes with ';'\n");
    printf("Example: price + taxes * rate;\n");
    printf("Terminate input using EOF symbol (Ctrl+Z or Ctrl+D)\n\n");
    
    start_parser();
    
    printf("\n==============================================\n");
    return 0;
}
