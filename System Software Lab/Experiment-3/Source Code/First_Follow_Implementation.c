/*
 * Experiment 3: Calculation of FIRST and FOLLOW Sets
 * Course: System Programming and Compiler Construction (SPCC)
 * 
 * Author: Amey Thakur
 * GitHub: https://github.com/Amey-Thakur
 * Repository: https://github.com/Amey-Thakur/SYSTEM-PROGRAMMING-AND-COMPILER-CONSTRUCTION-AND-SYSTEM-SOFTWARE-LAB
 * 
 * Description:
 * This program calculates the FIRST and FOLLOW sets for a given context-free grammar.
 * It reads the grammar from 'grammar.txt' and outputs the calculated sets.
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_PROD 20
#define MAX_LEN 10

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
 * Adds a terminal to a set if it's not already present.
 * @param set The set to add to.
 * @param c The character to add.
 */
void add_to_set(char *set, char c) {
    if (strchr(set, c) == NULL) {
        int len = strlen(set);
        set[len] = c;
        set[len + 1] = '\0';
    }
}

/**
 * Finds FIRST of a non-terminal recursively.
 * @param nt The non-terminal character.
 * @param prod_idx Index of the production in grammar.
 */
void find_first(char nt, int prod_idx) {
    for (int k = 0; k < num_productions; k++) {
        if (grammar[k].lhs[0] == nt) {
            for (int t = 0; t < grammar[k].num_rhs; t++) {
                char first_char = grammar[k].rhs[t][0];
                if (!isupper(first_char)) {
                    add_to_set(grammar[prod_idx].first, first_char);
                } else {
                    find_first(first_char, prod_idx);
                }
            }
        }
    }
}

/**
 * Finds FOLLOW of a non-terminal recursively.
 * @param nt The non-terminal character.
 * @param prod_idx Index of the production in grammar.
 */
void find_follow(char nt, int prod_idx) {
    for (int k = 0; k < num_productions; k++) {
        for (int t = 0; t < grammar[k].num_rhs; t++) {
            char *occurrence = strchr(grammar[k].rhs[t], nt);
            if (occurrence) {
                int pos = occurrence - grammar[k].rhs[t];
                char next_char = grammar[k].rhs[t][pos + 1];

                if (next_char != '\0') {
                    if (isupper(next_char)) {
                        for (int o = 0; o < num_productions; o++) {
                            if (grammar[o].lhs[0] == next_char) {
                                for (int f = 0; f < strlen(grammar[o].first); f++) {
                                    if (grammar[o].first[f] != '0') { // 0 for epsilon
                                        add_to_set(grammar[prod_idx].follow, grammar[o].first[f]);
                                    }
                                }
                            }
                        }
                    } else {
                        add_to_set(grammar[prod_idx].follow, next_char);
                    }
                } else if (grammar[k].lhs[0] != nt) {
                    // Rule: If A -> alpha B, then FOLLOW(B) includes FOLLOW(A)
                    int parent_idx = -1;
                    for (int o = 0; o < num_productions; o++) {
                        if (grammar[o].lhs[0] == grammar[k].lhs[0]) {
                            parent_idx = o;
                            break;
                        }
                    }
                    if (parent_idx != -1) {
                        // This part typically needs a bit more care for circularity
                        // For this lab, we'll follow the original logic
                        find_follow(grammar[k].lhs[0], prod_idx);
                    }
                }
            }
        }
    }
}

int main() {
    FILE *file = fopen("grammar.txt", "r");
    if (!file) {
        printf("Error: Could not open grammar.txt\n");
        return 1;
    }

    for (int i = 0; i < MAX_PROD; i++) {
        grammar[i].num_rhs = 0;
        grammar[i].first[0] = '\0';
        grammar[i].follow[0] = '\0';
    }

    /* Read Grammar from File */
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
    printf("Grammar detected:\n");
    for (int i = 0; i < num_productions; i++) {
        printf("%s -> ", grammar[i].lhs);
        for (int j = 0; j < grammar[i].num_rhs; j++) {
            printf("%s%s", grammar[i].rhs[j], (j < grammar[i].num_rhs - 1) ? " | " : "");
        }
        printf("\n");
    }

    /* Calculate FIRST */
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

    /* Calculate FOLLOW */
    grammar[0].follow[0] = '$';
    grammar[0].follow[1] = '\0';
    for (int i = 0; i < num_productions; i++) {
        find_follow(grammar[i].lhs[0], i);
    }

    /* Output Results */
    printf("\n%-15s %-20s %-20s\n", "Non-Terminal", "FIRST", "FOLLOW");
    printf("----------------------------------------------\n");
    for (int i = 0; i < num_productions; i++) {
        printf("%-15s { %-17s } { %-17s }\n", grammar[i].lhs, grammar[i].first, grammar[i].follow);
    }
    printf("==============================================\n");

    return 0;
}
