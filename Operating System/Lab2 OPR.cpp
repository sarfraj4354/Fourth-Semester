#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <sstream>

using namespace std;

// Convert int to string for older compilers
string intToString(int num) {
    stringstream ss;
    ss << num;
    return ss.str();
}

// Function to find the index of the page to replace using Optimal algorithm
int findOptimalIndex(const vector<int>& frameVec, const vector<int>& referenceString, int currentIndex) {
    int farthest = currentIndex;
    int indexToReplace = -1;

    for (size_t i = 0; i < frameVec.size(); ++i) {
        int j;
        // Look ahead in the reference string to find when this page will be used next
        for (j = currentIndex; j < (int)referenceString.size(); ++j) {
            if (frameVec[i] == referenceString[j]) {
                if (j > farthest) {
                    farthest = j;
                    indexToReplace = (int)i;
                }
                break;
            }
        }
        // If page not found in future, replace this one immediately
        if (j == (int)referenceString.size()) {
            return i;
        }
    }

    // If all pages are found in future, replace the one with farthest use
    if (indexToReplace == -1) {
        // No page found farthest (means all pages used immediately), replace first frame by default
        return 0;
    } else {
        return indexToReplace;
    }
}

int main() {
    int n, frameSize;
    vector<int> referenceString;
    vector<int> frameVec;
    int pageFaults = 0;

    // Input
    cout << "Enter the number of pages in the reference string: ";
    cin >> n;

    cout << "Enter the reference string (space-separated): ";
    for (int i = 0; i < n; ++i) {
        int page;
        cin >> page;
        referenceString.push_back(page);
    }

    cout << "Enter the number of frames: ";
    cin >> frameSize;

    // Header
    cout << "\n---------------------------------------------------\n";
    cout << left << setw(15) << "Reference"
         << setw(20) << "Frame"
         << setw(15) << "Result" << endl;
    cout << "---------------------------------------------------\n";

    for (int i = 0; i < n; ++i) {
        int currentPage = referenceString[i];
        string result;

        // Check if page is already in frames (Page Hit)
        vector<int>::iterator it = find(frameVec.begin(), frameVec.end(), currentPage);

        if (it != frameVec.end()) {
            result = "Page Hit";
        } else {
            // Page Fault
            result = "Page Fault";
            pageFaults++;

            if ((int)frameVec.size() < frameSize) {
                // Still have room in frames, just add page
                frameVec.push_back(currentPage);
            } else {
                // Need to replace a page optimally
                int indexToReplace = findOptimalIndex(frameVec, referenceString, i + 1);
                frameVec[indexToReplace] = currentPage;
            }
        }

        // Display output for this step
        cout << left << setw(15) << currentPage;

        // Frame contents string
        string frameContent;
        for (size_t j = 0; j < frameVec.size(); ++j) {
            frameContent += intToString(frameVec[j]);
            if (j != frameVec.size() - 1) frameContent += ", ";
        }

        cout << setw(20) << frameContent
             << setw(15) << result << endl;
    }

    // Final Summary
    cout << "---------------------------------------------------\n";
    cout << "Total Page Faults: " << pageFaults << endl;
    cout << "Total Page Hits  : " << n - pageFaults << endl;

    return 0;
}

