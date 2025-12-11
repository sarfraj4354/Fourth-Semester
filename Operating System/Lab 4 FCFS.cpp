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
};

// Comparator for stable_sort (keeps input order when AT ties)
bool cmpByAT(const Process& a, const Process& b) {
    return a.at < b.at;
}

int main() {
    int n;
    cout << "Enter number of processes: ";
    if (!(cin >> n) || n <= 0) {
        cout << "Invalid number of processes.\n";
        return 0;
    }

    vector<Process> p(n);
    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        cout << "Enter Arrival Time of P" << i + 1 << ": ";
        cin >> p[i].at;
        cout << "Enter Burst Time of P" << i + 1 << ": ";
        cin >> p[i].bt;
        p[i].ct = p[i].tat = p[i].wt = 0;
    }

    // Sort by arrival time; stable_sort preserves input order on ties
    stable_sort(p.begin(), p.end(), cmpByAT);

    int time = 0;
    for (int i = 0; i < n; i++) {
        if (time < p[i].at) {
            time = p[i].at; // CPU idle until next process arrives
        }
        time += p[i].bt;
        p[i].ct  = time;
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt  = p[i].tat - p[i].bt;
    }

    double avg_tat = 0.0, avg_wt = 0.0;

    cout << "\nProcess\tAT\tBT\tTAT\tWT\n";
    for (int i = 0; i < n; i++) {
        cout << "P" << p[i].pid << "\t"
             << p[i].at << "\t"
             << p[i].bt << "\t"
             << p[i].tat << "\t"
             << p[i].wt  << "\n";
        avg_tat += p[i].tat;
        avg_wt  += p[i].wt;
    }

    cout << fixed << setprecision(2);
    cout << "\nAverage Turnaround Time = " << (avg_tat / n);
    cout << "\nAverage Waiting Time    = " << (avg_wt  / n) << endl;

    return 0;
}

