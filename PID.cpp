#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        return 1;
    }
    else if (pid == 0) {
        // Child
        printf("Child: PID = %d, Parent PID = %d\n", getpid(), getppid());
        exit(0);
    }
    else {
        // Parent
        printf("Parent: PID = %d, My Child PID = %d\n", getpid(), pid);
        exit(0);
    }
}
