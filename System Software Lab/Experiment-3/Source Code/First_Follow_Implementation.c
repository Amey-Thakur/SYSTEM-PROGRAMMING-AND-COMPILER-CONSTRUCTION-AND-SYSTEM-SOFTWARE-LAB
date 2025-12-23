/*
 * =========================================================================================
 * Experiment 3: Calculation of FIRST and FOLLOW Sets
 * Course: System Programming and Compiler Construction (SPCC)
 * 
 * Author: Amey Thakur
 * GitHub: https://github.com/Amey-Thakur
 * Repository: https://github.com/Amey-Thakur/SYSTEM-PROGRAMMING-AND-COMPILER-CONSTRUCTION-AND-SYSTEM-SOFTWARE-LAB
 * =========================================================================================
 * 
 * TECHNICAL LOGIC EXPLANATION:
 * This program calculates the FIRST and FOLLOW sets for a given Context-Free Grammar (CFG). 
 * These sets are used during the construction of parsing tables in compilers.
 * 
 * Core Logic:
 * 1. FIRST Set: For a non-terminal (NT), it is the set of terminal symbols that appear 
 *    at the beginning of any string derived from that NT.
 * 2. FOLLOW Set: The set of terminal symbols that can appear immediately to the right 
 *    of a non-terminal in some sentential form.
 * 3. Recursive Discovery: The program uses recursive functions to navigate the 
 *    grammar rules, moving deeper into the rules until terminal symbols are found.
 * 4. Set Integration: Symbols found are aggregated into unique sets for each 
 *    individual non-terminal defined in the grammar.
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_PROD 20
#define MAX_LEN 10

/**
 * PRODUCTION STRUCTURE
 * Stores the Left-Hand Side (Non-Terminal) and multiple Right-Hand Side options.
 * Also keeps track of the calculated FIRST and FOLLOW sets for easy access.
 */
typedef struct {
    char lhs[MAX_LEN];
    char rhs[MAX_LEN][MAX_LEN];
    char first[MAX_PROD];
    char follow[MAX_PROD];
    int num_rhs;
} Production;

Production grammar[MAX_PROD];
int num_productions = 0;

/**
 * SET AGGREGATION LOGIC
 * Ensures that characters added to the sets are unique (no duplicates).
 */
void add_to_set(char *set, char c) {
    if (strchr(set, c) == NULL) {
        int len = strlen(set);
        set[len] = c;
        set[len + 1] = '\0';
    }
}

/**
 * RECURSIVE FIRST CALCULATION
 * Evaluates the grammar rules to find the leading terminals for a symbol.
 */
void find_first(char nt, int prod_idx) {
    for (int k = 0; k < num_productions; k++) {
        if (grammar[k].lhs[0] == nt) {
            for (int t = 0; t < grammar[k].num_rhs; t++) {
                char first_char = grammar[k].rhs[t][0];
                /* If the first character is a terminal (lowercase/symbol), add it. */
                if (!isupper(first_char)) {
                    add_to_set(grammar[prod_idx].first, first_char);
                } 
                /* If the first character is a non-terminal, recursively find its FIRST. */
                else {
                    find_first(first_char, prod_idx);
                }
            }
        }
    }
}

/**
 * RECURSIVE FOLLOW CALCULATION
 * Evaluates what symbols can follow a given Non-Terminal within the grammar production rules.
 */
void find_follow(char nt, int prod_idx) {
    for (int k = 0; k < num_productions; k++) {
        for (int t = 0; t < grammar[k].num_rhs; t++) {
            char *occurrence = strchr(grammar[k].rhs[t], nt);
            if (occurrence) {
                int pos = occurrence - grammar[k].rhs[t];
                char next_char = grammar[k].rhs[t][pos + 1];

                /* Rule: If there is a symbol after the current NT. */
                if (next_char != '\0') {
                    if (isupper(next_char)) {
                        // Inherit from the FIRST set of the next symbol.
                        for (int o = 0; o < num_productions; o++) {
                            if (grammar[o].lhs[0] == next_char) {
                                for (int f = 0; f < strlen(grammar[o].first); f++) {
                                    if (grammar[o].first[f] != '0') { // Skip epsilon
                                        add_to_set(grammar[prod_idx].follow, grammar[o].first[f]);
                                    }
                                }
                            }
                        }
                    } else {
                        add_to_set(grammar[prod_idx].follow, next_char);
                    }
                } 
                /* Rule: If the NT is at the end, inherit from the FOLLOW of the parent LHS. */
                else if (grammar[k].lhs[0] != nt) {
                    find_follow(grammar[k].lhs[0], prod_idx);
                }
            }
        }
    }
}

int main() {
    FILE *file = fopen("grammar.txt", "r");
    if (!file) {
        printf("Error: GRAMMAR.TXT not found. Please ensure input file is available.\n");
        return 1;
    }

    // Initializing structure fields to avoid junk data issues.
    for (int i = 0; i < MAX_PROD; i++) {
        grammar[i].num_rhs = 0;
        grammar[i].first[0] = '\0';
        grammar[i].follow[0] = '\0';
    }

    /* GRAMMAR INGESTION */
    while (!feof(file)) {
        char buffer[MAX_LEN];
        if (fscanf(file, "%s", buffer) != 1) break;

        if (num_productions > 0 && strcmp(buffer, grammar[num_productions - 1].lhs) == 0) {
            fscanf(file, "%s", grammar[num_productions - 1].rhs[grammar[num_productions - 1].num_rhs]);
            grammar[num_productions - 1].num_rhs++;
        } else {
            strcpy(grammar[num_productions].lhs, buffer);
            fscanf(file, "%s", grammar[num_productions].rhs[grammar[num_productions].num_rhs]);
            grammar[num_productions].num_rhs++;
            num_productions++;
        }
    }
    fclose(file);

    printf("\n==============================================\n");
    printf("         FIRST AND FOLLOW CALCULATOR         \n");
    printf("==============================================\n");
    printf("Grammar Structure detected:\n");
    for (int i = 0; i < num_productions; i++) {
        printf("%s -> ", grammar[i].lhs);
        for (int j = 0; j < grammar[i].num_rhs; j++) {
            printf("%s%s", grammar[i].rhs[j], (j < grammar[i].num_rhs - 1) ? " | " : "");
        }
        printf("\n");
    }

    /* EXECUTION: Calculate FIRST set for each non-terminal */
    for (int i = 0; i < num_productions; i++) {
        for (int j = 0; j < grammar[i].num_rhs; j++) {
            char first_sym = grammar[i].rhs[j][0];
            if (!isupper(first_sym)) {
                add_to_set(grammar[i].first, first_sym);
            } else {
                find_first(first_sym, i);
            }
        }
    }

    /* EXECUTION: Calculate FOLLOW set for each non-terminal */
    grammar[0].follow[0] = '$'; // The start symbol always contains $ (end of string)
    grammar[0].follow[1] = '\0';
    for (int i = 0; i < num_productions; i++) {
        find_follow(grammar[i].lhs[0], i);
    }

    /* REPORTING RESULTS */
    printf("\n%-15s %-20s %-20s\n", "Symbol", "FIRST Set", "FOLLOW Set");
    printf("----------------------------------------------\n");
    for (int i = 0; i < num_productions; i++) {
        printf("%-15s { %-17s } { %-17s }\n", grammar[i].lhs, grammar[i].first, grammar[i].follow);
    }
    printf("==============================================\n");

    return 0;
}
