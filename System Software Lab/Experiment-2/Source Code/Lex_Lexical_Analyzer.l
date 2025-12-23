%{
/*
 * Experiment 2: Lexical Analysis (using LEX Tool)
 * Course: System Programming and Compiler Construction (SPCC)
 * 
 * Author: Amey Thakur
 * GitHub: https://github.com/Amey-Thakur
 * Repository: https://github.com/Amey-Thakur/SYSTEM-PROGRAMMING-AND-COMPILER-CONSTRUCTION-AND-SYSTEM-SOFTWARE-LAB
 * 
 * Description:
 * This LEX program performs lexical analysis on a C source file.
 * It identifies keywords, identifiers, constants, operators, and comments.
 */

#include <stdio.h>
#include <stdlib.h>

int comment_depth = 0;
%}

/* Regular Expressions */
ID          [a-zA-Z_][a-zA-Z0-9_]*
NUMBER      [0-9]+(\.[0-9]+)?
KEYWORDS    "int"|"float"|"char"|"double"|"while"|"for"|"struct"|"typedef"|"do"|"if"|"break"|"continue"|"void"|"switch"|"return"|"else"|"goto"
OPERATORS   "+"|"-"|"*"|"/"|"%"|"="|"=="|"!="|"<"|">"|"<="|">="

%%

"/*"        { comment_depth++; printf("\n[COMMENT START]"); }
"*/"        { if (comment_depth > 0) comment_depth--; printf("\n[COMMENT END]"); }

{KEYWORDS}  { if (!comment_depth) printf("\nKeyword: %s", yytext); }
{ID}        { if (!comment_depth) printf("\nIdentifier: %s", yytext); }
{NUMBER}    { if (!comment_depth) printf("\nNumber: %s", yytext); }
{OPERATORS} { if (!comment_depth) printf("\nOperator: %s", yytext); }

\"[^\"]*\"  { if (!comment_depth) printf("\nString constant: %s", yytext); }
"#"         { if (!comment_depth) printf("\nPreprocessor Directive: #"); }
[ \t\n]+    { /* Ignore whitespace */ }
"{"         { if (!comment_depth) printf("\nBlock Start: {"); }
"}"         { if (!comment_depth) printf("\nBlock End: }"); }
"("         { if (!comment_depth) printf("\nParenthesis Open: ("); }
")"         { if (!comment_depth) printf("\nParenthesis Close: )"); }
";"         { if (!comment_depth) printf("\nSemicolon: ;"); }
","         { if (!comment_depth) printf("\nComma: ,"); }

.           { if (!comment_depth) printf("\nUnknown Token: %s", yytext); }

%%

int main(int argc, char **argv) {
    char *input_file = "sample_input.c";
    
    if (argc > 1) {
        input_file = argv[1];
    }

    FILE *file = fopen(input_file, "r");
    if (!file) {
        printf("\nError: Could not open file %s\n", input_file);
        return 1;
    }

    printf("\n==============================================\n");
    printf("       LEX Lexical Analyzer for SPCC Lab       \n");
    printf("==============================================\n");
    printf("Reading from: %s\n", input_file);

    yyin = file;
    yylex();

    fclose(file);
    printf("\n\n==============================================\n");
    return 0;
}

int yywrap() {
    return 1;
}
