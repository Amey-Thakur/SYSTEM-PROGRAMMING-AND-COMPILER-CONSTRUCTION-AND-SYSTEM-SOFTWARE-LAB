/*
 * Experiment 1: Deterministic Finite Automaton (DFA) Implementation
 * Course: System Programming and Compiler Construction (SPCC)
 * 
 * Author: Amey Thakur
 * GitHub: https://github.com/Amey-Thakur
 * Repository: https://github.com/Amey-Thakur/SYSTEM-PROGRAMMING-AND-COMPILER-CONSTRUCTION-AND-SYSTEM-SOFTWARE-LAB
 * 
 * Description:
 * This program implements a DFA that accepts strings over the alphabet {a, b}.
 * The automaton transitions through various states based on the input character
 * and determines if the final state is an accepting state.
 */

#include <stdio.h>
#include <string.h>

/* DFA State Enumeration */
typedef enum {
    STATE_START = 0,
    STATE_1,
    STATE_2,
    STATE_3,
    STATE_4,
    STATE_INVALID = -1
} DFAState;

DFAState current_state = STATE_START;

/**
 * Transition function for the start state.
 * @param c Input character.
 */
void transition_start(char c) {
    if (c == 'a') current_state = STATE_1;
    else if (c == 'b') current_state = STATE_3;
    else current_state = STATE_INVALID;
}

/**
 * Transition function for state 1.
 * @param c Input character.
 */
void transition_state1(char c) {
    if (c == 'a') current_state = STATE_2;
    else if (c == 'b') current_state = STATE_4;
    else current_state = STATE_INVALID;
}

/**
 * Transition function for state 2.
 * @param c Input character.
 */
void transition_state2(char c) {
    if (c == 'b') current_state = STATE_3;
    else if (c == 'a') current_state = STATE_1;
    else current_state = STATE_INVALID;
}

/**
 * Transition function for state 3.
 * @param c Input character.
 */
void transition_state3(char c) {
    if (c == 'b') current_state = STATE_3;
    else if (c == 'a') current_state = STATE_4;
    else current_state = STATE_INVALID;
}

/**
 * Transition function for state 4 (Dead State).
 */
void transition_state4() {
    current_state = STATE_INVALID;
}

/**
 * Checks if the given string is accepted by the DFA.
 * @param str Input string.
 * @return 1 if accepted, 0 otherwise.
 */
int is_accepted(const char str[]) {
    current_state = STATE_START;
    int len = strlen(str);

    for (int i = 0; i < len; i++) {
        switch (current_state) {
            case STATE_START:
                transition_start(str[i]);
                break;
            case STATE_1:
                transition_state1(str[i]);
                break;
            case STATE_2:
                transition_state2(str[i]);
                break;
            case STATE_3:
                transition_state3(str[i]);
                break;
            case STATE_4:
                transition_state4();
                break;
            default:
                return 0; // Rejected early on invalid state
        }
    }

    /* Accepting state is STATE_3 */
    return (current_state == STATE_3);
}

int main() {
    char input_string[100];

    printf("\n==============================================\n");
    printf("       DFA String Acceptance Implementation    \n");
    printf("==============================================\n");
    printf("Alphabet: {a, b}\n");
    printf("Enter a string to test: ");
    
    if (scanf("%99s", input_string) == 1) {
        if (is_accepted(input_string)) {
            printf("\nRESULT: String \"%s\" is [ACCEPTED]\n", input_string);
        } else {
            printf("\nRESULT: String \"%s\" is [NOT ACCEPTED]\n", input_string);
        }
    }

    printf("==============================================\n");
    return 0;
}
