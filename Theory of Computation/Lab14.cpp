//Design deterministic finite automata (DFA) with ∑ = {0, 1} that accepts the languages ending with “01” over the characters {0, 1}.
#include <stdio.h>
#define MAX 100

int main() {
    char str[MAX], f = 'a';
    int i;

    printf("Enter the string to be checked: ");
    scanf("%s", str);

    for (i = 0; str[i] != '\0'; i++) {
        switch (f) {
            case 'a':
                if (str[i] == '0') f = 'b';
                else if (str[i] == '1') f = 'a';
                break;
            case 'b':
                if (str[i] == '0') f = 'b';
                else if (str[i] == '1') f = 'c';
                break;
            case 'c':
                if (str[i] == '0') f = 'b';
                else if (str[i] == '1') f = 'a';
                break;
        }
    }

    if (f == 'c')
        printf("\nString is accepted\n");
    else
        printf("\nString is not accepted\n");

    return 0;
}
