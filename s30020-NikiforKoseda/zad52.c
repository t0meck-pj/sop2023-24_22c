#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t pid;
    int number;

    printf("PID: %d\n", getpid());
    printf("PPID: %d\n", getppid());

    pid = fork();

    if (pid < 0) {
        printf("Fork failed.\n");
    } else if (pid == 0) {
        printf("This is the child process. PID: %d, PPID: %d\n", getpid(), getppid());
    } else {
        printf("This is the parent process. PID: %d, Child's PID: %d\n", getpid(), pid);
    }

    scanf("%d", &number);

    return 0;
}