//Program to implement NFA from Regular Expression
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STATES 10
#define MAX_SYMBOLS 27  // 26 letters + 1 for epsilon
#define EPSILON 26      // Use 26th index for epsilon

int fa[MAX_STATES][MAX_SYMBOLS][MAX_STATES]; // NFA transitions
int states[2][MAX_STATES];                   // Accepting states
int row = 0, col = 0, th = 0;

// Recursive function to check NFA acceptance
int nfa(char *string, int state) {
    int i, curr;

    // Explore epsilon transitions first
    for (i = 0; i < MAX_STATES; i++) {
        curr = fa[state][EPSILON][i];
        if (curr != -1) {
            if (nfa(string, curr)) return 1;
        }
    }

    if (*string == '\0') {
        // Check if current state is accepting
        for (i = 0; i < MAX_STATES && states[1][i] != -1; i++) {
            if (state == states[1][i]) return 1;
        }
        return 0;
    }

    // Explore transitions for current symbol
    int sym_index = *string - 'a';
    for (i = 0; i < MAX_STATES; i++) {
        curr = fa[state][sym_index][i];
        if (curr != -1) {
            if (nfa(string + 1, curr)) return 1;
        }
    }

    return 0;
}

// Build a simple NFA for regex "a*"
void build_nfa_from_regex() {
    // Initialize arrays
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < MAX_STATES; j++)
            states[i][j] = -1;

    for (int i = 0; i < MAX_STATES; i++)
        for (int j = 0; j < MAX_SYMBOLS; j++)
            for (int k = 0; k < MAX_STATES; k++)
                fa[i][j][k] = -1;

    // NFA for a*:
    // State 0 epsilon -> 1
    fa[0][EPSILON][0] = 1;
    // State 1 'a' -> 1 (loop)
    fa[1]['a' - 'a'][0] = 1;
    // State 1 epsilon -> 2 (accepting)
    fa[1][EPSILON][0] = 2;

    // Accepting state
    states[1][0] = 2;
    row = 2;
}

int main() {
    char str[50];

    printf("Building NFA for regex a*\n");
    build_nfa_from_regex();

    printf("\nEnter the string to test: ");
    scanf("%s", str);

    if (nfa(str, 0))
        printf("\nString Is Accepted\n");
    else
        printf("\nString Not Accepted\n");

    return 0;
}
