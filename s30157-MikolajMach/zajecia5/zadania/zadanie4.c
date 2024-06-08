#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

#define NUM_PROCESSES 1
#define MAX_DEPTH 100

void create_processes(int depth) {
    if (depth >= MAX_DEPTH) {
        return;
    }

    pid_t child_pid;

    for (int i = 0; i < NUM_PROCESSES; ++i) {
        child_pid = fork();

        if (child_pid == -1) {
            perror("fork");
            exit(1);
        } else if (child_pid == 0) {
            printf("Proces potomny %d - PID: %d, PPID: %d\n", depth + 1, getpid(), getppid());
            create_processes(depth + 1);
            exit(0);
        } else {
            wait(NULL);
        }
    }
}

int main() {
    printf("Proces główny - PID: %d\n", getpid());
    create_processes(0);

    return 0;
}

