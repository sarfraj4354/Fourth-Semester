#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, head, totalCylinders;
    int seekTime = 0;

    printf("FCFS Disk Scheduling Algorithm by Sarfraj ALam\n");

    // Input total cylinders
    printf("Enter total number of cylinders: ");
    scanf("%d", &totalCylinders);

    // Input head position
    printf("Enter current position of R/W head: ");
    scanf("%d", &head);

    // Input request queue size
    printf("Enter number of pending requests: ");
    scanf("%d", &n);

    int requests[n];
    printf("Enter the request queue (cylinder numbers):\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &requests[i]);
        if (requests[i] < 0 || requests[i] >= totalCylinders) {
            printf("Invalid request: %d (out of range)\n", requests[i]);
            return 1;
        }
    }

    // FCFS scheduling
    int current = head;
    printf("\nHead Movement Order:\n");
    printf("%d", current);
    for (int i = 0; i < n; i++) {
        seekTime += abs(current - requests[i]);
        current = requests[i];
        printf(" -> %d", current);
    }

    // Gantt-style diagram
    printf("\n\nDiagrammatic Representation:\n");
    printf("----------------------------------------------------\n");
    current = head;
    printf("| %d ", current);
    for (int i = 0; i < n; i++) {
        printf("| %d ", requests[i]);
    }
    printf("|\n");
    printf("----------------------------------------------------\n");

    // Distances (seek)
    printf("  ");
    current = head;
    for (int i = 0; i < n; i++) {
        int dist = abs(current - requests[i]);
        printf("  %d   ", dist);
        current = requests[i];
    }
    printf("\n");

    // Results
    printf("\nTotal Seek Time = %d no of cylinders\n", seekTime);
    printf("Average Seek Time = %.2f no of cylinders\n", (float)seekTime / n);

    return 0;
}
