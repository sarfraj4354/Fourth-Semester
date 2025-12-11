//A simple and basic program in C to convert NFA to DFA (does not handle null moves)
/* 
A program to convert NFA to DFA using conversion table

Author - Kipawa
Technique used - Bitmasking
NOTE -
1. If your states are q0, q1, q2 they will be represented as follows (in the
table)
q0 = 2^0 = 1
q1 = 2^1 = 2
q2 = 2^2 = 4
2. Similarly union of states will be represented as -
q0,q1 = 2^0 + 2^1 = 3
q1, q2 = 2^1 + 2^2 = 6
q0,q1,q2 = 2^0 + 2^1 + 2^2 = 7
3. Do not give any condition for "phi"...
That case is not handled... (Coz I m Lazy :P)
4. Follow zero based indexing everywhere
5. Program assumes that if "Number of states are = n", then they are numbered
as q0, q1, q2 ... q(n-1)
6. If you find any bug, msg me and forgive me for the errors
*/

#include <stdio.h>
#include <string.h>
#include <math.h>

int dfa[100][2][100] = {0};   // NFA transitions
int state[10000] = {0};       // Track existing DFA states
int go[10000][2] = {0};       // DFA transition table
int arr[10000] = {0};         // Queue for new DFA states

int main() {
    int st, fin, in;
    int f[10];
    int i, j, k, x = 0, curr1, l, flag;
    int p, q, r, rel;

    printf("\nFollow zero-based indexing for states.\n");
    printf("Enter the number of states: ");
    scanf("%d", &st);

    for (i = 0; i < st; i++) state[(int)pow(2, i)] = 1;

    printf("Enter number of final states: ");
    scanf("%d", &fin);

    printf("Enter final states: ");
    for (i = 0; i < fin; i++) scanf("%d", &f[i]);

    printf("Enter number of NFA transitions: ");
    scanf("%d", &rel);

    printf("Enter transitions as: initial_state input_symbol final_state\n");
    for (i = 0; i < rel; i++) {
        scanf("%d %d %d", &p, &q, &r);
        dfa[p][q][r] = 1;
    }

    printf("Enter initial state: ");
    scanf("%d", &in);
    in = (int)pow(2, in);  // bitmask of initial state

    printf("\nSolving according to DFA\n");

    // Compute DFA transitions for single NFA states
    for (i = 0; i < st; i++) {
        for (j = 0; j < 2; j++) {
            int stf = 0;
            for (k = 0; k < st; k++) {
                if (dfa[i][j][k] == 1) stf += (int)pow(2, k);
            }
            go[(int)pow(2, i)][j] = stf;
            if (state[stf] == 0 && stf != 0) arr[x++] = stf;
            state[stf] = 1;
        }
    }

    // Compute DFA transitions for combined states
    for (i = 0; i < x; i++) {
        for (j = 0; j < 2; j++) {
            int new_state = 0;
            for (k = 0; k < st; k++) {
                if (arr[i] & (1 << k)) new_state |= go[1 << k][j];
            }
            go[arr[i]][j] = new_state;
            if (state[new_state] == 0 && new_state != 0) arr[x++] = new_state;
            state[new_state] = 1;
        }
    }

    // Print DFA table
    printf("\nThe total number of distinct DFA states are:\n");
    printf("STATE  0  1\n");
    for (i = 0; i < 10000; i++) {
        if (state[i] == 1) {
            int y = 0;
            if (i == 0) {
                printf("q0 ");
            } else {
                printf("q");
                for (j = 0; j < st; j++) {
                    if (i & (1 << j)) printf("%d", j);
                    y |= (i & (1 << j));
                }
            }
            printf(" %d %d\n", go[y][0], go[y][1]);
        }
    }

    // Test strings
    int test_count = 3;
    while (test_count--) {
        char str[100];
        printf("\nEnter string to test (0 and 1 only): ");
        scanf("%s", str);

        l = strlen(str);
        curr1 = in;
        flag = 0;

        printf("String path: %d-", curr1);
        for (i = 0; i < l; i++) {
            curr1 = go[curr1][str[i] - '0'];
            printf("%d-", curr1);
        }
        printf("\nFinal state: %d\n", curr1);

        // Check if string is accepted
        for (i = 0; i < fin; i++) {
            if (curr1 & (1 << f[i])) {
                flag = 1;
                break;
            }
        }

        if (flag) printf("String Accepted\n");
        else printf("String Rejected\n");
    }

    return 0;
}
