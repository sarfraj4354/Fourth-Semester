#include <stdio.h>
#include <stdlib.h>

int main() {
    int totalCylinders, head, n, direction;
    int seekTime = 0;

    printf("LOOK Disk Scheduling Algorithm by Sarfraj Alam\n");

    // Input total cylinders
    printf("Enter total number of cylinders: ");
    scanf("%d", &totalCylinders);

    // Input head position
    printf("Enter current position of R/W head: ");
    scanf("%d", &head);

    // Input size of request queue
    printf("Enter number of pending requests: ");
    scanf("%d", &n);

    int requests[n];
    printf("Enter the request queue:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &requests[i]);
        if (requests[i] < 0 || requests[i] >= totalCylinders) {
            printf("Invalid request %d (out of range)\n", requests[i]);
            return 1;
        }
    }

    // Input LOOK direction
    printf("Enter direction (0 = left, 1 = right): ");
    scanf("%d", &direction);

    // Sort the request queue
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (requests[i] > requests[j]) {
                int temp = requests[i];
                requests[i] = requests[j];
                requests[j] = temp;
            }
        }
    }

    printf("\nHead Movement Order:\n%d", head);

    // LOOK to the right first
    if (direction == 1) {
        // Move from head to the farthest right request
        for (int i = 0; i < n; i++) {
            if (requests[i] >= head) {
                seekTime += abs(head - requests[i]);
                head = requests[i];
                printf(" -> %d", head);
            }
        }
        // Then move left to remaining requests
        for (int i = n - 1; i >= 0; i--) {
            if (requests[i] < head) {
                seekTime += abs(head - requests[i]);
                head = requests[i];
                printf(" -> %d", head);
            }
        }
    }

    // LOOK to the left first
    else {
        // Move from head to the farthest left request
        for (int i = n - 1; i >= 0; i--) {
            if (requests[i] <= head) {
                seekTime += abs(head - requests[i]);
                head = requests[i];
                printf(" -> %d", head);
            }
        }
        // Then move right to remaining requests
        for (int i = 0; i < n; i++) {
            if (requests[i] > head) {
                seekTime += abs(head - requests[i]);
                head = requests[i];
                printf(" -> %d", head);
            }
        }
    }

    printf("\n\nTotal Seek Time = %d cylinders\n", seekTime);
    printf("Average Seek Time = %.2f cylinders\n", (float)seekTime / n);

    return 0;
}

