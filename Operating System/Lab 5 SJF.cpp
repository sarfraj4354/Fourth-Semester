#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;

struct Process {
    int pid;   // Process ID
    int at;    // Arrival Time
    int bt;    // Burst Time
    int ct;    // Completion Time
    int tat;   // Turnaround Time
    int wt;    // Waiting Time
    bool done; // Flag to mark completion
};

int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    vector<Process> p(n);
    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        cout << "Enter Arrival Time of P" << i + 1 << ": ";
        cin >> p[i].at;
        cout << "Enter Burst Time of P" << i + 1 << ": ";
        cin >> p[i].bt;
        p[i].ct = p[i].tat = p[i].wt = 0;
        p[i].done = false;
    }

    int completed = 0, time = 0;
    while (completed < n) {
        int idx = -1;
        int minBT = 1e9;

        // Select process with shortest burst time among arrived & not done
        for (int i = 0; i < n; i++) {
            if (!p[i].done && p[i].at <= time) {
                if (p[i].bt < minBT) {
                    minBT = p[i].bt;
                    idx = i;
                } else if (p[i].bt == minBT) {
                    // Tie-breaking by arrival time
                    if (p[i].at < p[idx].at) idx = i;
                }
            }
        }

        if (idx == -1) {
            time++; // CPU idle
        } else {
            time += p[idx].bt;
            p[idx].ct = time;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;
            p[idx].done = true;
            completed++;
        }
    }

    double avg_tat = 0.0, avg_wt = 0.0;

    cout << "\nProcess\tAT\tBT\tTAT\tWT\n";
    for (int i = 0; i < n; i++) {
        cout << "P" << p[i].pid << "\t"
             << p[i].at << "\t"
             << p[i].bt << "\t"
             << p[i].tat << "\t"
             << p[i].wt << "\n";
        avg_tat += p[i].tat;
        avg_wt += p[i].wt;
    }

    cout << fixed << setprecision(2);
    cout << "\nAverage Turnaround Time = " << (avg_tat / n);
    cout << "\nAverage Waiting Time    = " << (avg_wt / n) << endl;

    return 0;
}

