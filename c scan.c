#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int main() {
    int n, head, disk_size;
    printf("Enter number of requests: ");
    scanf("%d", &n);

    int req[n];
    printf("Enter the request queue:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &req[i]);

    printf("Enter initial head position: ");
    scanf("%d", &head);

    printf("Enter disk size: ");
    scanf("%d", &disk_size);   // example: 200, last cylinder = 199

    // Sort the request queue
    qsort(req, n, sizeof(int), compare);

    int total = 0;
    int index = 0;

    // Find the first request greater than head
    for (int i = 0; i < n; i++) {
        if (req[i] >= head) {
            index = i;
            break;
        }
    }

    printf("\nC-SCAN Order of servicing:\n");
    int current = head;

    // Move right from head to end
    for (int i = index; i < n; i++) {
        total += abs(req[i] - current);
        current = req[i];
        printf("%d ", current);
    }

    // Move to the end of disk
    total += abs((disk_size - 1) - current);
    current = 0; // jump to 0 (circular)

    // Add jump cost
    total += (disk_size - 1);

    // Service from beginning up to index-1
    for (int i = 0; i < index; i++) {
        total += abs(req[i] - current);
        current = req[i];
        printf("%d ", current);
    }

    printf("\n\nTotal Head Movement = %d\n", total);

    return 0;
}

