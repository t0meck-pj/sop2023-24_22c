#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid_B, pid_C, pid_D, pid_E, pid_F, pid_G;
    pid_t parent_pid, child_pid;

    parent_pid = getpid();

    pid_B = fork();
    if (pid_B == 0) {
        child_pid = getpid();
        printf("Proces B (PID: %d), rodzic: Proces A (PID: %d)\n", getpid(), getppid());

        pid_D = fork();
        if (pid_D == 0) {
            printf("Proces D (PID: %d), rodzic: Proces B (PID: %d)\n", getpid(), getppid());
        } else {
            wait(NULL);
            pid_E = fork();
            if (pid_E == 0) {
                printf("Proces E (PID: %d), rodzic: Proces B (PID: %d)\n", getpid(), getppid());
            } else {
                wait(NULL);
                return 0;
            }
        }
    } else {
        wait(NULL);
        pid_C = fork();
        if (pid_C == 0) {
            child_pid = getpid();
            printf("Proces C (PID: %d), rodzic: Proces A (PID: %d)\n", getpid(), getppid());

            pid_F = fork();
            if (pid_F == 0) {
                printf("Proces F (PID: %d), rodzic: Proces C (PID: %d)\n", getpid(), getppid());
            } else {
                wait(NULL);
                pid_G = fork();
                if (pid_G == 0) {
                    printf("Proces G (PID: %d), rodzic: Proces C (PID: %d)\n", getpid(), getppid());
                } else {
                    wait(NULL);
                    return 0;
                }
            }
        } else {
            wait(NULL);
            return 0;
        }
    }

    return 0;
}
