/*
 * =========================================================================================
 * Experiment 1: Deterministic Finite Automaton (DFA) Implementation
 * Course: System Programming and Compiler Construction (SPCC)
 * 
 * Author: Amey Thakur
 * GitHub: https://github.com/Amey-Thakur
 * Repository: https://github.com/Amey-Thakur/SYSTEM-PROGRAMMING-AND-COMPILER-CONSTRUCTION-AND-SYSTEM-SOFTWARE-LAB
 * =========================================================================================
 * 
 * TECHNICAL LOGIC EXPLANATION:
 * This program simulates a Deterministic Finite Automaton (DFA), a mathematical model 
 * used in computer science to represent a system that changes states based on 
 * external inputs. 
 * 
 * Operational Procedure:
 * 1. Initialization: The system begins in a fixed "Start State".
 * 2. Sequential Processing: The input string is read one character at a time.
 * 3. State Transition: For every character read, the program evaluates the current 
 *    state and determines the next state based on pre-defined logical rules.
 * 4. Final Validation: After the entire input is processed, the program checks if 
 *    the system has landed in an "Accepting State". If so, the input is considered valid.
 */

#include <stdio.h>
#include <string.h>

/**
 * DFA STATE ENUMERATIONS
 * An enumeration (enum) is used to define a set of named integer constants representing 
 * the various rooms or 'states' the machine can occupy.
 * STATE_INVALID (-1) acts as a sink state for unexpected or invalid characters.
 */
typedef enum {
    STATE_START = 0,
    STATE_1,
    STATE_2,
    STATE_3,
    STATE_4,
    STATE_INVALID = -1
} DFAState;

/* This variable tracks the runtime state of the automaton during execution. */
DFAState current_state = STATE_START;

/**
 * TRANSITION FUNCTIONS
 * Each function represents the logical rules governing state changes for a specific 
 * state given an input character ('a' or 'b').
 */

/* Rules for transitioning from the START state */
void transition_start(char c) {
    if (c == 'a') current_state = STATE_1;      // Transition to State 1 on input 'a'
    else if (c == 'b') current_state = STATE_3; // Transition to State 3 on input 'b'
    else current_state = STATE_INVALID;         // Error handling for out-of-alphabet characters
}

/* Rules for transitioning from State 1 */
void transition_state1(char c) {
    if (c == 'a') current_state = STATE_2;      // Move to State 2 on input 'a'
    else if (c == 'b') current_state = STATE_4; // Move to State 4 on input 'b'
    else current_state = STATE_INVALID;
}

/* Rules for transitioning from State 2 */
void transition_state2(char c) {
    if (c == 'b') current_state = STATE_3;      // Move to State 3 on input 'b'
    else if (c == 'a') current_state = STATE_1; // Loop back to State 1 on input 'a'
    else current_state = STATE_INVALID;
}

/* Rules for transitioning from State 3 (The designated Accepting State) */
void transition_state3(char c) {
    if (c == 'b') current_state = STATE_3;      // Self-loop on 'b' (stay in Accepting State)
    else if (c == 'a') current_state = STATE_4; // Transition to Rejection State 4 on input 'a'
    else current_state = STATE_INVALID;
}

/* Dead State / Error Handling Logic */
void transition_state4() {
    // Current state is moved to an invalid category to ensure the string is rejected.
    current_state = STATE_INVALID;
}

/**
 * AUTOMATON EXECUTION LOGIC
 * This function handles the high-level orchestration of the DFA simulation.
 */
int is_accepted(const char str[]) {
    current_state = STATE_START; // System reset for each processing cycle
    int len = strlen(str);

    // Iterative evaluation of input characters
    for (int i = 0; i < len; i++) {
        // Evaluate the current state context
        switch (current_state) {
            case STATE_START: transition_start(str[i]); break;
            case STATE_1:     transition_state1(str[i]); break;
            case STATE_2:     transition_state2(str[i]); break;
            case STATE_3:     transition_state3(str[i]); break;
            case STATE_4:     transition_state4(); break;
            // Early termination if an invalid state is encountered
            default:          return 0; 
        }
    }

    /* 
     * ACCEPTANCE CRITERION: 
     * The input is accepted only if the machine finishes in STATE_3.
     */
    return (current_state == STATE_3);
}

int main() {
    char input_string[100];

    // User Interface Header
    printf("\n==============================================\n");
    printf("       DFA String Acceptance Implementation    \n");
    printf("==============================================\n");
    printf("Logic: State transitions based on alphabet {a, b}.\n");
    printf("Enter a string to evaluate: ");
    
    // Capturing and processing user input
    if (scanf("%99s", input_string) == 1) {
        if (is_accepted(input_string)) {
            printf("\nRESULT: Success. String \"%s\" reaches an accepting state.\n", input_string);
        } else {
            printf("\nRESULT: Rejected. String \"%s\" ends in a non-accepting state.\n", input_string);
        }
    }

    printf("==============================================\n");
    return 0;
}
