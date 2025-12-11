//Program to construct a DFA which accepts the language L = {aN | N ≥ 1}
#include <iostream>
using namespace std;

// Function to check whether the string is accepted by DFA
void isAcceptedDFA(string s)
{
    int N = s.size();

    // String must not be empty
    if (N == 0) {
        cout << "Not Accepted";
        return;
    }

    // Check if every character is 'a'
    for (int i = 0; i < N; i++) {
        if (s[i] != 'a') {
            cout << "Not Accepted";
            return;
        }
    }

    // All conditions matched
    cout << "Accepted";
}

// Driver Code
int main()
{
    string S = "aaaaa";   // Test string

    isAcceptedDFA(S);

    return 0;
}
