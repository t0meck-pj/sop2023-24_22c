#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

#define CHILDREN_NUM 100

int main() {
    pid_t child_pid;
    int status;

    for (int i = 0; i < CHILDREN_NUM; ++i) {
        child_pid = fork();

        if (child_pid == -1) {
            perror("fork");
            return 1;
        } else if (child_pid == 0) {
            printf("Proces potomny %d - PID: %d, PPID: %d\n", i + 1, getpid(), getppid());
            return 0;
        }
    }

    printf("Proces rodzica - PID: %d\n", getpid());

    for (int i = 0; i < CHILDREN_NUM; ++i) {
        wait(&status);
    }

    return 0;
}

