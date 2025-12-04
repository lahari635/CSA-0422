#include <stdio.h>

int main() {
    int n, quantum;
    printf("Enter number of processes: "); if (scanf("%d",&n)!=1 || n<=0) return 0;
    int arrival[n], burst[n], remaining[n], completion[n], waiting[n], turnaround[n];
    for (int i=0;i<n;i++){
        printf("P%d arrival: ", i+1); scanf("%d",&arrival[i]);
        printf("P%d burst: ", i+1);   scanf("%d",&burst[i]);
        remaining[i] = burst[i];
        completion[i] = waiting[i] = turnaround[i] = 0;
    }
    printf("Enter quantum: "); scanf("%d",&quantum);

    int time = 0, done = 0;
    while (done < n) {
        int progressed = 0;
        for (int i=0;i<n;i++){
            if (arrival[i] <= time && remaining[i] > 0) {
                progressed = 1;
                int exec = (remaining[i] > quantum) ? quantum : remaining[i];
                remaining[i] -= exec;
                time += exec;
                if (remaining[i] == 0) {
                    completion[i] = time;
                    turnaround[i] = completion[i] - arrival[i];
                    waiting[i] = turnaround[i] - burst[i];
                    done++;
                }
            }
        }
        if (!progressed) time++; // idle CPU until next arrival
    }

    double totW=0, totT=0;
    printf("\nPID\tArr\tBurst\tComp\tTAT\tWT\n");
    for (int i=0;i<n;i++){
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", i+1, arrival[i], burst[i], completion[i], turnaround[i], waiting[i]);
        totW += waiting[i]; totT += turnaround[i];
    }
    printf("\nAvg WT = %.2f, Avg TAT = %.2f\n", totW/n, totT/n);
    return 0;
}
