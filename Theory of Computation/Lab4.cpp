// Design a DFA that accepts the string ending with "bb" over the alphabet {a,b}

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

    // Check if the string ends with "bb"
    bool endsWithBB = validString && userString.length() >= 2 && userString.substr(userString.length() - 2) == "bb";

    if (endsWithBB) {
        cout << "String is accepted." << endl;
    } else {
        cout << "String is not accepted." << endl;
    }

    return 0;
}