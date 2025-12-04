#include <stdio.h>

int main() {
    int n, indexBlock;

    printf("Enter index block number: ");
    scanf("%d", &indexBlock);

    printf("Enter number of blocks needed for file: ");
    scanf("%d", &n);

    int indexTable[n];

    printf("Enter block numbers allocated to this file:\n");
    for (int i = 0; i < n; i++) {
        printf("Block for entry %d: ", i);
        scanf("%d", &indexTable[i]);
    }

    printf("\n--- Indexed Allocation Table ---\n");
    printf("Index Block: %d\n", indexBlock);

    for (int i = 0; i < n; i++) {
        printf("Index[%d] -> Block %d\n", i, indexTable[i]);
    }

    printf("\nFile stored successfully using Indexed Allocation.\n");
    return 0;
}
