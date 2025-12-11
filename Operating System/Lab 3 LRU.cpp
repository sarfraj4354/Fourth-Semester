#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <sstream>

using namespace std;

// Function to convert int to string for older compilers
string intToString(int num) {
    stringstream ss;
    ss << num;
    return ss.str();
}

// Function to update recently used pages
void updateLRU(vector<int>& usageOrder, int page) {
    vector<int>::iterator it = find(usageOrder.begin(), usageOrder.end(), page);
    if (it != usageOrder.end()) {
        usageOrder.erase(it);
    }
    usageOrder.push_back(page); // move to the back (most recently used)
}

int main() {
    int n, frameSize;
    vector<int> referenceString;
    vector<int> frameVec;
    vector<int> usageOrder; // keeps track of LRU
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

        // Check if page is in frame
        vector<int>::iterator it = find(frameVec.begin(), frameVec.end(), currentPage);

        if (it != frameVec.end()) {
            // Page Hit
            result = "Page Hit";
        } else {
            // Page Fault
            result = "Page Fault";
            pageFaults++;

            if ((int)frameVec.size() < frameSize) {
                frameVec.push_back(currentPage);
            } else {
                // Remove least recently used page
                int lruPage = usageOrder.front();
                usageOrder.erase(usageOrder.begin());

                vector<int>::iterator removeIt = find(frameVec.begin(), frameVec.end(), lruPage);
                if (removeIt != frameVec.end()) {
                    frameVec.erase(removeIt);
                }

                frameVec.push_back(currentPage);
            }
        }

        // Update usage history
        updateLRU(usageOrder, currentPage);

        // Print output for this step
        cout << left << setw(15) << currentPage;

        // Frame contents
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

