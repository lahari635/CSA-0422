#include <stdio.h>

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    int bt[n], pr[n], p[n], wt[n], tat[n];

    for (int i = 0; i < n; i++) {
        p[i] = i+1;
        printf("Burst time and Priority of P%d: ", i+1);
        scanf("%d %d", &bt[i], &pr[i]);
    }

    // Sort by priority
    for (int i = 0; i < n-1; i++)
        for (int j = i+1; j < n; j++)
            if (pr[i] > pr[j]) {
                int t = pr[i]; pr[i] = pr[j]; pr[j] = t;
                int x = bt[i]; bt[i] = bt[j]; bt[j] = x;
                int y = p[i];  p[i] = p[j];   p[j] = y;
            }

    wt[0] = 0;
    for (int i = 1; i < n; i++)
        wt[i] = wt[i-1] + bt[i-1];

    for (int i = 0; i < n; i++)
        tat[i] = wt[i] + bt[i];

    printf("\nProcess\tPr\tBT\tWT\tTAT\n");
    for (int i = 0; i < n; i++)
        printf("P%d\t%d\t%d\t%d\t%d\n", p[i], pr[i], bt[i], wt[i], tat[i]);

    return 0;
}
