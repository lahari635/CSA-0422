#include <stdio.h>

int main() {
    int n;
    printf("Enter number of blocks in the file: ");
    scanf("%d", &n);

    int blocks[n];
    int next[n];

    printf("Enter block numbers in the order they appear:\n");
    for (int i = 0; i < n; i++) {
        printf("Block %d: ", i + 1);
        scanf("%d", &blocks[i]);
    }

    // Build linked list pointers
    for (int i = 0; i < n - 1; i++) {
        next[i] = blocks[i + 1];
    }
    next[n - 1] = -1; // Last block ? NULL

    printf("\n--- Linked Allocation Table ---\n");
    printf("Start Block = %d\n", blocks[0]);
    printf("End Block   = %d\n", blocks[n - 1]);

    for (int i = 0; i < n; i++) {
        printf("Block %d -> Next %d\n", blocks[i], next[i]);
    }

    printf("\nFile stored successfully using Linked Allocation.\n");
    return 0;
}
