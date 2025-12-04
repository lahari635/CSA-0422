#include <stdio.h>

int main() {
    int pages[50], frames[10];
    int n, f, i, j, k, pageFaults = 0;

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

        // Check if page exists in frame
        for (j = 0; j < f; j++) {
            if (frames[j] == pages[i]) {
                found = 1;
                break;
            }
        }

        // If page not found ? Page Fault
        if (!found) {
            int lruIndex = -1, farthest = i;

            // Find LRU page among frames
            for (j = 0; j < f; j++) {
                int k_flag = 0;
                for (k = i - 1; k >= 0; k--) {
                    if (frames[j] == pages[k]) {
                        k_flag = 1;
                        if (k < farthest) {
                            farthest = k;
                            lruIndex = j;
                        }
                        break;
                    }
                }
                // If frame page was never used before ? Replace it immediately
                if (!k_flag) {
                    lruIndex = j;
                    break;
                }
            }

            // Replace LRU page
            frames[lruIndex] = pages[i];
            pageFaults++;
        }

        // Display frames
        printf("\nAfter page %d: ", pages[i]);
        for (j = 0; j < f; j++)
            printf("%d ", frames[j]);
    }

    printf("\n\nTotal Page Faults = %d\n", pageFaults);

    return 0;
}
