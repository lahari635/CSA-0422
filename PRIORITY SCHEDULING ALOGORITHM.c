#include <stdio.h>

struct Process {
    int pid;
    int arrival;
    int burst;
    int priority; // lower number = higher priority
    int completion;
    int waiting;
    int turnaround;
    int started;
};

int main() {
    int n;
    printf("Enter number of processes: ");
    if (scanf("%d",&n)!=1 || n<=0) return 0;

    struct Process p[n];
    for (int i=0;i<n;i++){
        p[i].pid = i+1;
        p[i].started = 0;
        printf("P%d Arrival: ", p[i].pid); scanf("%d",&p[i].arrival);
        printf("P%d Burst: ", p[i].pid);   scanf("%d",&p[i].burst);
        printf("P%d Priority (lower = higher): ", p[i].pid); scanf("%d",&p[i].priority);
    }

    int time = 0, completed = 0;
    while (completed < n) {
        int idx = -1;
        int bestPriority = 1<<30;
        for (int i=0;i<n;i++){
            if (!p[i].started && p[i].arrival <= time) {
                if (p[i].priority < bestPriority) {
                    bestPriority = p[i].priority;
                    idx = i;
                } else if (p[i].priority == bestPriority) {
                    if (p[i].arrival < p[idx].arrival) idx = i;
                }
            }
        }
        if (idx == -1) { time++; continue; }
        p[idx].started = 1;
        time += p[idx].burst;
        p[idx].completion = time;
        p[idx].turnaround = p[idx].completion - p[idx].arrival;
        p[idx].waiting = p[idx].turnaround - p[idx].burst;
        completed++;
    }

    double totW=0, totT=0;
    printf("\nPID\tArr\tBurst\tPrio\tComp\tTAT\tWT\n");
    for (int i=0;i<n;i++){
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
            p[i].pid,p[i].arrival,p[i].burst,p[i].priority,p[i].completion,p[i].turnaround,p[i].waiting);
        totW+=p[i].waiting; totT+=p[i].turnaround;
    }
    printf("\nAvg WT = %.2f, Avg TAT = %.2f\n", totW/n, totT/n);
    return 0;
}
