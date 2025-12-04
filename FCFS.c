// Program 6: Round Robin Scheduling
#include <stdio.h>

int main() {
    int n, quantum, i, time = 0, flag = 1;
    int bt[20], rt[20], wt[20], tat[20];

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter Burst Times:\n");
    for(i = 0; i < n; i++) {
        printf("BT of P%d: ", i+1);
        scanf("%d", &bt[i]);
        rt[i] = bt[i];
        wt[i] = 0;
    }

    printf("Enter Time Quantum: ");
    scanf("%d", &quantum);

    while(flag) {
        flag = 0;
        for(i = 0; i < n; i++) {
            if(rt[i] > 0) {
                flag = 1;
                if(rt[i] > quantum) {
                    time += quantum;
                    rt[i] -= quantum;
                } else {
                    time += rt[i];
                    wt[i] = time - bt[i];
                    rt[i] = 0;
                }
            }
        }
    }

    for(i = 0; i < n; i++)
        tat[i] = wt[i] + bt[i];

    printf("\nP\tBT\tWT\tTAT\n");
    for(i = 0; i < n; i++)
        printf("P%d\t%d\t%d\t%d\n", i+1, bt[i], wt[i], tat[i]);

    return 0;
}