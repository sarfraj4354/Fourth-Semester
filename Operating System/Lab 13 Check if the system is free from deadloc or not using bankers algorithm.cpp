#include <stdio.h>

int main() {
    int n, m; // n = number of processes, m = number of resources

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter number of resources: ");
    scanf("%d", &m);

    int allocation[n][m];
    int max[n][m];
    int available[m];
    int need[n][m];

    // Input Allocation Matrix
    printf("\nEnter Allocation Matrix:\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d: ", i);
        for (int j = 0; j < m; j++)
            scanf("%d", &allocation[i][j]);
    }

    // Input Max Matrix
    printf("\nEnter Maximum Matrix:\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d: ", i);
        for (int j = 0; j < m; j++)
            scanf("%d", &max[i][j]);
    }

    // Input Available Matrix
    printf("\nEnter Available Resources: ");
    for (int j = 0; j < m; j++)
        scanf("%d", &available[j]);

    // Calculate Need Matrix = Max - Allocation
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            need[i][j] = max[i][j] - allocation[i][j];

    int finish[n];
    for (int i = 0; i < n; i++)
        finish[i] = 0; // initialize all processes as unfinished

    int safeSeq[n];
    int count = 0;

    // Banker's Algorithm
    while (count < n) {
        int found = 0;

        for (int p = 0; p < n; p++) {
            if (!finish[p]) {
                int canAllocate = 1;
                for (int r = 0; r < m; r++) {
                    if (need[p][r] > available[r]) {
                        canAllocate = 0;
                        break;
                    }
                }

                if (canAllocate) {
                    // Allocate resources
                    for (int r = 0; r < m; r++)
                        available[r] += allocation[p][r];

                    safeSeq[count++] = p;
                    finish[p] = 1;
                    found = 1;
                }
            }
        }

        if (!found) {
            printf("\nSystem is NOT SAFE! Deadlock may occur.\n");
            return 0;
        }
    }

    // Print safe sequence
    printf("\nSystem is SAFE.\nSafe Sequence is: ");
    for (int i = 0; i < n; i++) {
        printf("P%d", safeSeq[i]);
        if (i != n - 1) printf(" -> ");
    }
    printf("\n");

    return 0;
}

