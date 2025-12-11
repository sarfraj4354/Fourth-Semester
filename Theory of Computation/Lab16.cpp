//Design a DFA machine accepting odd numbers of 0’s or even numbers of 1’s
#include <stdio.h>

int main() {
    // DFA states
    int S0=0, S1=1, S2=2, S3=3;
    int state = S0; // initial state
    char input;

    printf("Enter a string of 0s and 1s: ");

    while (1) {
        scanf("%c", &input);
        if (input == '\n') break; // end of input

        if (input != '0' && input != '1') {
            printf("Invalid input: program terminating\n");
            return 0;
        }

        // DFA transitions
        switch(state) {
            case 0: state = (input=='0')?S1:S2; break;
            case 1: state = (input=='0')?S0:S3; break;
            case 2: state = (input=='0')?S3:S0; break;
            case 3: state = (input=='0')?S2:S1; break;
        }
    }

    // Accepting states: S0, S1, S3
    if (state == S0 || state == S1 || state == S3)
        printf("Input accepted\n");
    else
        printf("Input rejected\n");

    return 0;
}
