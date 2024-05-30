#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>


void createProcesses(int count);

void createChildProcess(int count) {
    if (count > 0) {
        pid_t pid = fork();

        if (pid < 0) {
            perror("fork failed");
            exit(1);
        } else if (pid == 0) {
            printf("Child process %d created\n", getpid());
            createProcesses(count - 1);
            exit(0);
        } else {
            wait(NULL);
            printf("Child process %d finished\n", pid);
        }
    }
}

void createProcesses(int count) {
    createChildProcess(count);
}

int main() {
    createProcesses(100);
    return 0;
}