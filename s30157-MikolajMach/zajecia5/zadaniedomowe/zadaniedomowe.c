#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pidB, pidC, pidD, pidE, pidF, pidG;

    printf("Proces A, PID: %d\n", getpid());
    sleep(1);

    pidB = fork();
    if (pidB < 0) {
        fprintf(stderr, "Błąd podczas tworzenia procesu B\n");
        exit(EXIT_FAILURE);
    } else if (pidB == 0) {
        printf("Proces B, PID: %d, PPID: %d\n", getpid(), getppid());
        sleep(1);

        pidD = fork();
        if (pidD < 0) {
            fprintf(stderr, "Błąd podczas tworzenia procesu D\n");
            exit(EXIT_FAILURE);
        } else if (pidD == 0) {
            printf("Proces D, PID: %d, PPID: %d\n", getpid(), getppid());
            sleep(1);
            exit(EXIT_SUCCESS);
        } else {
            wait(NULL);
        }

        pidE = fork();
        if (pidE < 0) {
            fprintf(stderr, "Błąd podczas tworzenia procesu E\n");
            exit(EXIT_FAILURE);
        } else if (pidE == 0) {
            printf("Proces E, PID: %d, PPID: %d\n", getpid(), getppid());
            sleep(1);
            exit(EXIT_SUCCESS);
        } else {
            wait(NULL);
        }

        exit(EXIT_SUCCESS);
    }

    pidC = fork();
    if (pidC < 0) {
        fprintf(stderr, "Błąd podczas tworzenia procesu C\n");
        exit(EXIT_FAILURE);
    } else if (pidC == 0) {
        printf("Proces C, PID: %d, PPID: %d\n", getpid(), getppid());
        sleep(1);
        pidF = fork();
        if (pidF < 0) {
            fprintf(stderr, "Błąd podczas tworzenia procesu F\n");
            exit(EXIT_FAILURE);
        } else if (pidF == 0) {
            printf("Proces F, PID: %d, PPID: %d\n", getpid(), getppid());
            sleep(1);
            exit(EXIT_SUCCESS);
        } else {
            wait(NULL);
        }

        pidG = fork();
        if (pidG < 0) {
            fprintf(stderr, "Błąd podczas tworzenia procesu G\n");
            exit(EXIT_FAILURE);
        } else if (pidG == 0) {

            printf("Proces G, PID: %d, PPID: %d\n", getpid(), getppid());
            sleep(1);
            exit(EXIT_SUCCESS);
        } else {

            wait(NULL);
        }

        exit(EXIT_SUCCESS);
    }

    wait(NULL);
    wait(NULL);

    return 0;
}
