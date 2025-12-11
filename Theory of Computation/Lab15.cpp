//Construct deterministic finite automata (DFA) for the language L = { w : w has odd number of 0’s and w has odd number of 1’s},over the alphabet Σ = {0, 1}.
#include <stdio.h>

int main(void) {
    int EE = 0, OE = 1, OO = 2, EO = 3; // DFA states
    int state = EE; // initial state
    char input;

    printf("Enter a string of 0s and 1s: ");

    while (1) {
        scanf("%c", &input);

        if (input == '\n') // end-of-line
            break;

        if (input != '0' && input != '1') { // invalid input
            printf("Invalid input: program terminating\n");
            return 0;
        }

        // DFA transitions
        if (state == EE) {
            state = (input == '0') ? OE : EO;
        }
        else if (state == OE) {
            state = (input == '0') ? EE : OO;
        }
        else if (state == OO) {
            state = (input == '0') ? EO : OE;
        }
        else if (state == EO) {
            state = (input == '0') ? OO : EE;
        }
    }

    // Check if final state is accepting (OO)
    if (state == OO)
        printf("Input accepted\n");
    else
        printf("Input rejected\n");

    return 0;
}
