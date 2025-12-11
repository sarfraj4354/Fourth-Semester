// C program to implement DFA that accepts
// all strings of the language
// L = { a^n b^m ; (n mod 2 = 0), m >= 1 }

#include <stdio.h>
#include <string.h>

// dfa stores the current state number
int dfa = 0;

// Starting state Q0
void start(char c)
{
    if (c == 'a') {
        dfa = 1;
    }
    else if (c == 'b') {
        dfa = 3;
    }
    else {
        dfa = -1;  // invalid character
    }
}

// State Q1
void state1(char c)
{
    if (c == 'a') {
        dfa = 2;   // even number of a's
    }
    else if (c == 'b') {
        dfa = 4;   // invalid: b after odd a count
    }
    else {
        dfa = -1;
    }
}

// State Q2
void state2(char c)
{
    if (c == 'b') {
        dfa = 3;   // move to b-state
    }
    else if (c == 'a') {
        dfa = 1;   // back to odd a-count
    }
    else {
        dfa = -1;
    }
}

// State Q3 (ACCEPTING state)
void state3(char c)
{
    if (c == 'b') {
        dfa = 3;   // stay in b*
    }
    else if (c == 'a') {
        dfa = 4;   // invalid: a after b
    }
    else {
        dfa = -1;
    }
}

// State Q4 (DEAD state)
void state4(char c)
{
    dfa = -1;
}

// Check if string is accepted
int isAccepted(char str[])
{
    int i, len = strlen(str);

    for (i = 0; i < len; i++) {
        if (dfa == 0)
            start(str[i]);
        else if (dfa == 1)
            state1(str[i]);
        else if (dfa == 2)
            state2(str[i]);
        else if (dfa == 3)
            state3(str[i]);
        else if (dfa == 4)
            state4(str[i]);
        else
            return 0;
    }

    if (dfa == 3)   // accepting state
        return 1;
    else
        return 0;
}

// Driver code
int main()
{
    char str[] = "aaaaaabbbb";

    if (isAccepted(str))
        printf("ACCEPTED");
    else
        printf("NOT ACCEPTED");

    return 0;
}
