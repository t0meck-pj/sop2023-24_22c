#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void createChildProcesses(int numProcesses) {
    for (int i = 1; i <= numProcesses; ++i) {
        pid_t pid = fork();

        if (pid < 0) {
            fprintf(stderr, "Błąd podczas wywoływania fork()\n");
            exit(1);
        } else if (pid == 0) {
            printf("Proces potomny %d: PID = %d, PPID = %d\n", i, getpid(), getppid());
            exit(0);
        } else {
            wait(NULL);
        }
    }
}

int main() {
    const int numProcesses = 10;
    printf("Proces główny: PID = %d\n", getpid());
    createChildProcesses(numProcesses);
    return 0;
}
