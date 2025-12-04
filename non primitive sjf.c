#include <stdio.h>
#include <limits.h>

struct Process {
    int pid, arrival, burst, completed;
    int completion, waiting, turnaround;
};

int main() {
    int n; printf("Enter number of processes: "); if (scanf("%d",&n)!=1 || n<=0) return 0;
    struct Process p[n];
    for (int i=0;i<n;i++){
        p[i].pid=i+1; p[i].completed=0;
        printf("P%d Arrival: ", p[i].pid); scanf("%d",&p[i].arrival);
        printf("P%d Burst: ", p[i].pid);   scanf("%d",&p[i].burst);
    }

    int completed=0, time=0;
    while (completed<n) {
        int idx=-1, minBurst=INT_MAX;
        for (int i=0;i<n;i++){
            if (!p[i].completed && p[i].arrival<=time){
                if (p[i].burst < minBurst) { minBurst=p[i].burst; idx=i; }
                else if (p[i].burst==minBurst && p[i].arrival < p[idx].arrival) idx=i;
            }
        }
        if (idx==-1) { time++; continue; }
        time += p[idx].burst;
        p[idx].completed = 1;
        p[idx].completion = time;
        p[idx].turnaround = p[idx].completion - p[idx].arrival;
        p[idx].waiting = p[idx].turnaround - p[idx].burst;
        completed++;
    }

    double totalWT=0, totalTAT=0;
    printf("\nPID\tArr\tBurst\tComp\tTAT\tWT\n");
    for (int i=0;i<n;i++){
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid,p[i].arrival,p[i].burst,p[i].completion,p[i].turnaround,p[i].waiting);
        totalWT+=p[i].waiting; totalTAT+=p[i].turnaround;
    }
    printf("\nAvg WT=%.2f, Avg TAT=%.2f\n", totalWT/n, totalTAT/n);
    return 0;
}
