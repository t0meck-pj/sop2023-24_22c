#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t child_pid;

    child_pid = fork();

    if (child_pid == -1) {
        perror("fork");
        return 1;
    } else if (child_pid == 0) {
        printf("Proces potomny:\n");
        printf("PID: %d\n", getpid());
        printf("PPID: %d\n", getppid());
    } else {
        printf("Proces rodzica:\n");
        printf("PID: %d\n", getpid());
        printf("PPID: %d\n", getppid());

        wait(NULL);
    }

    return 0;
}

