#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <iomanip>
#include <sstream>  // include stringstream header

using namespace std;

// Function to convert int to string for older compilers
string intToString(int num) {
    stringstream ss;
    ss << num;
    return ss.str();
}

int main() {
    int n, frameSize;
    vector<int> referenceString;
    queue<int> fifoQueue;
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

    // FIFO Logic with Output
    for (int i = 0; i < n; ++i) {
        int currentPage = referenceString[i];
        string result;

        vector<int>::iterator it = find(frameVec.begin(), frameVec.end(), currentPage);

        if (it != frameVec.end()) {
            // Page Hit
            result = "Page Hit";
        } else {
            // Page Fault
            result = "Page Fault";
            pageFaults++;

            if ((int)frameVec.size() < frameSize) {
                fifoQueue.push(currentPage);
                frameVec.push_back(currentPage);
            } else {
                int toRemove = fifoQueue.front();
                fifoQueue.pop();

                vector<int>::iterator it = find(frameVec.begin(), frameVec.end(), toRemove);
                if (it != frameVec.end()) frameVec.erase(it);

                fifoQueue.push(currentPage);
                frameVec.push_back(currentPage);
            }
        }

        // Display output for this step
        cout << left << setw(15) << currentPage;

        // Frame contents string
        string frameContent;
        for (size_t j = 0; j < frameVec.size(); ++j) {
            frameContent += intToString(frameVec[j]);  // use intToString here
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

