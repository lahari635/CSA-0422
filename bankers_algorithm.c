// bankers_algorithm.c
#include <stdio.h>
#include <stdbool.h>

#define P 5 // processes
#define R 3 // resource types

bool is_safe(int available[], int max[][R], int alloc[][R], int need[][R]) {
    int work[R]; bool finish[P]={0};
    for (int i=0;i<R;i++) work[i]=available[i];
    int count=0;
    while (count<P) {
        bool found=false;
        for (int p=0;p<P;p++){
            if(!finish[p]){
                int j; for(j=0;j<R;j++) if(need[p][j] > work[j]) break;
                if (j==R) {
                    for (int k=0;k<R;k++) work[k]+=alloc[p][k];
                    finish[p]=true; found=true; count++;
                }
            }
        }
        if(!found) return false;
    }
    return true;
}

int main(){
    // Example from standard texts
    int alloc[P][R] = {{0,1,0},{2,0,0},{3,0,2},{2,1,1},{0,0,2}};
    int max[P][R]   = {{7,5,3},{3,2,2},{9,0,2},{2,2,2},{4,3,3}};
    int available[R] = {3,3,2};
    int need[P][R];
    for (int i=0;i<P;i++) for(int j=0;j<R;j++) need[i][j]=max[i][j]-alloc[i][j];

    if (is_safe(available, max, alloc, need)) printf("System is in a SAFE state\n");
    else printf("System is NOT safe\n");

    // Example: try to allocate request for process 1 (P0-based index 1)
    int req[R] = {1,0,2}; // example request
    int pid = 1;
    bool possible = true;
    for (int i=0;i<R;i++) if (req[i] > need[pid][i] || req[i] > available[i]) possible=false;
    if (possible) {
        for (int i=0;i<R;i++){ available[i]-=req[i]; alloc[pid][i]+=req[i]; need[pid][i]-=req[i]; }
        if (is_safe(available, max, alloc, need)) printf("Request can be granted safely.\n");
        else printf("Granting request would make system unsafe — deny it.\n");
    } else printf("Request cannot be granted (too large) immediately.\n");

    return 0;
}
