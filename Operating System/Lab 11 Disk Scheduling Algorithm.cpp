#include <stdio.h>
#include <stdlib.h>

int main() {
    int totalCylinders, head, n, direction;
    int seekTime = 0;

    printf("SCAN Disk Scheduling Algorithm by Sarfraj Alam\n");

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

    // Input scan direction
    printf("Enter direction (0 = left, 1 = right): ");
    scanf("%d", &direction);

    // Add head into list for easier processing
    int allRequests[n + 1];
    for (int i = 0; i < n; i++) {
        allRequests[i] = requests[i];
    }
    allRequests[n] = head;

    // Sort all requests (including head)
    for (int i = 0; i < n + 1; i++) {
        for (int j = i + 1; j < n + 1; j++) {
            if (allRequests[i] > allRequests[j]) {
                int temp = allRequests[i];
                allRequests[i] = allRequests[j];
                allRequests[j] = temp;
            }
        }
    }

    // Find head index in sorted array
    int headIndex = 0;
    for (int i = 0; i < n + 1; i++) {
        if (allRequests[i] == head) {
            headIndex = i;
            break;
        }
    }

    printf("\nHead Movement Order:\n%d", head);

    // SCAN to the right
    if (direction == 1) {
        // Move from head to right end
        for (int i = headIndex + 1; i < n + 1; i++) {
            seekTime += abs(head - allRequests[i]);
            head = allRequests[i];
            printf(" -> %d", head);
        }

        // Go to last cylinder
        if (head != totalCylinders - 1) {
            seekTime += abs(head - (totalCylinders - 1));
            head = totalCylinders - 1;
            printf(" -> %d", head);
        }

        // Then move left servicing remaining requests
        for (int i = headIndex - 1; i >= 0; i--) {
            seekTime += abs(head - allRequests[i]);
            head = allRequests[i];
            printf(" -> %d", head);
        }
    }

    // SCAN to the left
    else {
        // Move from head left
        for (int i = headIndex - 1; i >= 0; i--) {
            seekTime += abs(head - allRequests[i]);
            head = allRequests[i];
            printf(" -> %d", head);
        }

        // Go to cylinder 0
        if (head != 0) {
            seekTime += abs(head - 0);
            head = 0;
            printf(" -> %d", head);
        }

        // Then move right servicing remaining requests
        for (int i = headIndex + 1; i < n + 1; i++) {
            seekTime += abs(head - allRequests[i]);
            head = allRequests[i];
            printf(" -> %d", head);
        }
    }

    printf("\n\nTotal Seek Time = %d cylinders\n", seekTime);
    printf("Average Seek Time = %.2f cylinders\n", (float)seekTime / n);

    return 0;
}

