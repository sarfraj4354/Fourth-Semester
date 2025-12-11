#include <iostream>
#include <vector>
#include <queue>
#include <iomanip>
using namespace std;

struct Process {
    int pid;   // Process ID
    int at;    // Arrival Time
    int bt;    // Burst Time
    int rt;    // Remaining Time
    int ct;    // Completion Time
    int tat;   // Turnaround Time
    int wt;    // Waiting Time
};

int main() {
    int n, tq;
    cout << "Enter number of processes: ";
    cin >> n;

    vector<Process> p(n);
    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        cout << "Enter Arrival Time of P" << i + 1 << ": ";
        cin >> p[i].at;
        cout << "Enter Burst Time of P" << i + 1 << ": ";
        cin >> p[i].bt;
        p[i].rt = p[i].bt; // initially remaining time = burst time
        p[i].ct = p[i].tat = p[i].wt = 0;
    }

    cout << "Enter Time Quantum: ";
    cin >> tq;

    queue<int> q;  // stores process indices
    int time = 0, completed = 0;
    vector<bool> inQueue(n, false);

    // Initially push processes that arrive at time 0
    for (int i = 0; i < n; i++) {
        if (p[i].at == 0) {
            q.push(i);
            inQueue[i] = true;
        }
    }

    while (completed < n) {
        if (q.empty()) {
            time++; // CPU idle
            for (int i = 0; i < n; i++) {
                if (!inQueue[i] && p[i].at <= time) {
                    q.push(i);
                    inQueue[i] = true;
                }
            }
            continue;
        }

        int idx = q.front();
        q.pop();

        if (p[idx].rt > tq) {
            time += tq;
            p[idx].rt -= tq;
        } else {
            time += p[idx].rt;
            p[idx].rt = 0;
            p[idx].ct = time;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;
            completed++;
        }

        // Push newly arrived processes into queue
        for (int i = 0; i < n; i++) {
            if (!inQueue[i] && p[i].at <= time && p[i].rt > 0) {
                q.push(i);
                inQueue[i] = true;
            }
        }

        // If current process not finished, push it back
        if (p[idx].rt > 0) {
            q.push(idx);
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

