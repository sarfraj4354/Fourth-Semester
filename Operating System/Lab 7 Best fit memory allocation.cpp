#include <stdio.h>
int main() {
    int nb, np;
    int blockSize[20], initialBlockSize[20], processSize[20], allocation[20], freeSpace[20];

    // Input number of blocks
    printf("Enter number of free blocks: ");
    scanf("%d", &nb);

    printf("Enter size of each block:\n");
    for (int i = 0; i < nb; i++) {
        printf("Block %d size: ", i + 1);
        scanf("%d", &blockSize[i]);
        initialBlockSize[i] = blockSize[i]; // Save original size for later
        freeSpace[i] = blockSize[i];        // Initially all space is free
    }

    // Input number of processes
    printf("\nEnter number of processes: ");
    scanf("%d", &np);

    printf("Enter size of each process:\n");
    for (int i = 0; i < np; i++) {
        printf("Process %d size: ", i + 1);
        scanf("%d", &processSize[i]);
        allocation[i] = -1; // Initially not allocated
    }

    // Best Fit Allocation
    for (int i = 0; i < np; i++) {
        int bestIndex = -1;
        for (int j = 0; j < nb; j++) {
            if (freeSpace[j] >= processSize[i]) {
                if (bestIndex == -1 || freeSpace[j] < freeSpace[bestIndex]) {
                    bestIndex = j;
                }
            }
        }

        if (bestIndex != -1) {
            allocation[i] = bestIndex;
            freeSpace[bestIndex] -= processSize[i];
        }
    }

    // Process Allocation Table
    printf("\nProcess No.\tProcess Size\tBlock No.\tFree Space Remaining\n");
    for (int i = 0; i < np; i++) {
        printf("%d\t\t%d\t\t", i + 1, processSize[i]);
        if (allocation[i] != -1) {
            printf("%d\t\t%d", allocation[i] + 1, freeSpace[allocation[i]]);
        } else {
            printf("Not Allocated\t-");
        }
        printf("\n");
    }

    // Final Block Status Table
    printf("\nFinal Block Status:\n");
    printf("Block No.\tInitial Size\tFinal Free Space\n");
    for (int i = 0; i < nb; i++) {
        printf("%d\t\t%d\t\t%d\n", i + 1, initialBlockSize[i], freeSpace[i]);
    }

    return 0;
}

