#include <stdio.h>

int main() {
    int pages[50], frames[10], temp[10];
    int n, f, i, j, k, pageFaults = 0, index = 0;

    printf("Enter number of pages: ");
    scanf("%d", &n);

    printf("Enter page reference string: ");
    for (i = 0; i < n; i++)
        scanf("%d", &pages[i]);

    printf("Enter number of frames: ");
    scanf("%d", &f);

    for (i = 0; i < f; i++)
        frames[i] = -1;

    for (i = 0; i < n; i++) {
        int found = 0;

        // Check if page already exists
        for (j = 0; j < f; j++) {
            if (frames[j] == pages[i]) {
                found = 1;
                break;
            }
        }

        // If page not found ? fault ? replace oldest
        if (!found) {
            frames[index] = pages[i];
            index = (index + 1) % f;
            pageFaults++;
        }

        // Display frames
        printf("\nAfter page %d: ", pages[i]);
        for (k = 0; k < f; k++)
            printf("%d ", frames[k]);
    }

    printf("\n\nTotal Page Faults = %d\n", pageFaults);

    return 0;
}
