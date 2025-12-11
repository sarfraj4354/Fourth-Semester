#include <stdio.h>

int main() {
    int nb, np;
    
   // Step 1: Input number of free memory blocks
    printf("Enter number of free blocks: ");
    scanf("%d", &nb);

    // Arrays to store block information
    int blockSize[nb], blockFree[nb], initialBlockSize[nb];

    // Step 2: Input size of each memory block
    printf("Enter size of each block:\n");
    for (int i = 0; i < nb; i++) {
        printf("Block %d size: ", i + 1);
        scanf("%d", &blockSize[i]);

        blockFree[i] = blockSize[i];         // Initially, all space is free
        initialBlockSize[i] = blockSize[i];  // Keep original size for final report
    }

    // Step 3: Input number of processes
    printf("\nEnter number of processes: ");
    scanf("%d", &np);

    int processSize[np], allocation[np];

    // Step 4: Input process sizes
    for (int i = 0; i < np; i++) {
        printf("Process %d size: ", i + 1);
        scanf("%d", &processSize[i]);
        allocation[i] = -1; // Initially, no process is allocated
    }

    // Step 5: First Fit Allocation Algorithm
    for (int i = 0; i < np; i++) {       // For each process
        for (int j = 0; j < nb; j++) {   // Find first block that fits
            if (blockFree[j] >= processSize[i]) {
                allocation[i] = j;           // Allocate block j to process i
                blockFree[j] -= processSize[i]; // Reduce free space in the block
                break; // Stop searching once allocated (First Fit)
            }
        }
    }

    // Step 6: Display Process Allocation Table
    printf("\nProcess No.\tProcess Size\tBlock No.\tFree Space Remaining After Allocation\n");
    for (int i = 0; i < np; i++) {
        printf("%d\t\t%d\t\t", i + 1, processSize[i]);
        if (allocation[i] != -1)
            printf("%d\t\t%d", allocation[i] + 1, blockFree[allocation[i]]);
        else
            printf("Not Allocated\t-");
        printf("\n");
    }

    // Step 7: Display Final Block Status
    printf("\nFinal Block Status:\n");
    printf("Block No.\tInitial Size\tFinal Free Space\n");
    for (int i = 0; i < nb; i++) {
        printf("%d\t\t%d\t\t%d\n", i + 1, initialBlockSize[i], blockFree[i]);
    }

    return 0;
}

