#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid;

    pid = fork();

    if (pid < 0) {
        fprintf(stderr, "Błąd podczas wywoływania fork()\n");
        return 1;
    } else if (pid == 0) {
        printf("Proces potomny: PID = %d, PPID = %d\n", getpid(), getppid());
        sleep(3);
        printf("Proces potomny kończy działanie\n");
        return 0;
    } else {
        printf("Proces rodzica: PID = %d, PPID = %d\n", getpid(), getppid());
        int status;
        waitpid(pid, &status, 0);
        if (WIFEXITED(status)) {
            printf("Proces potomny zakończył się z kodem powrotu: %d\n", WEXITSTATUS(status));
        } else {
            printf("Proces potomny zakończył się niepoprawnie\n");
        }
        return 0;
    }
}
