// Design a DFA that accepts the string starting with "aa" over the alphabet {a,b}

#include <iostream>
#include <string>

using namespace std;

int main() {
    string userString;

    cout << "Enter a string: ";
    cin >> userString;

    // Check if the user input string contains only 'a' and 'b' characters
    bool validString = true;
    for (char c : userString) {
        if (c != 'a' && c != 'b') {
            validString = false;
            break;
        }
    }

    // Check if the string starts with "aa"
    bool startsWithAA = validString && userString.substr(0, 2) == "aa";

    if (startsWithAA) {
        cout << "String is accepted." << endl;
    } else {
        cout << "String Rejected!" << endl;
    }

    return 0;
}