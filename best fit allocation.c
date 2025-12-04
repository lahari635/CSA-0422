#include <stdio.h>

int main() {
    int blockSize[20], processSize[20];
    int blockCount, processCount;
    int allocation[20];

    printf("Enter number of blocks: ");
    scanf("%d", &blockCount);

    printf("Enter block sizes:\n");
    for (int i = 0; i < blockCount; i++)
        scanf("%d", &blockSize[i]);

    printf("Enter number of processes: ");
    scanf("%d", &processCount);

    printf("Enter process sizes:\n");
    for (int i = 0; i < processCount; i++)
        scanf("%d", &processSize[i]);

    for (int i = 0; i < processCount; i++)
        allocation[i] = -1;

    for (int i = 0; i < processCount; i++) {
        int bestIdx = -1;
        for (int j = 0; j < blockCount; j++) {
            if (blockSize[j] >= processSize[i]) {
                if (bestIdx == -1 || blockSize[j] < blockSize[bestIdx])
                    bestIdx = j;
            }
        }
        if (bestIdx != -1) {
            allocation[i] = bestIdx;
            blockSize[bestIdx] -= processSize[i];
        }
    }

    printf("\nProcess\tSize\tBlock\n");
    for (int i = 0; i < processCount; i++) {
        printf("%d\t%d\t", i + 1, processSize[i]);
        if (allocation[i] != -1)
            printf("%d\n", allocation[i] + 1);
        else
            printf("Not Allocated\n");
    }
    return 0;
}
