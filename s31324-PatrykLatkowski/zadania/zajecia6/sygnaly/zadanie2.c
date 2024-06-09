#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <stdbool.h>
#include <fcntl.h>
#include <sys/file.h>
#include <string.h>

#define LOCK_FILE "/tmp/lock"

void handle_usr1(int sig) {
    printf("Wykryto próbę uruchomienia drugiej instancji programu.\n");
}

void handle_sigint(int sig) {
    printf("\nOtrzymano sygnał CTRL+C. Zamykanie programu.\n");
    unlink(LOCK_FILE);
    exit(0);
}

int main() {
    int fd = open(LOCK_FILE, O_CREAT | O_RDWR, 0644);
    if (fd == -1) {
        perror("Nie można otworzyć pliku blokady");
        exit(1);
    }

    if (flock(fd, LOCK_EX | LOCK_NB) == -1) {
        printf("Program jest już uruchomiony.\n");
        exit(0);
    }

    char pid_str[10];
    sprintf(pid_str, "%d", getpid());
    write(fd, pid_str, strlen(pid_str));

    signal(SIGUSR1, handle_usr1);
    signal(SIGINT, handle_sigint);

    printf("Uruchomiono program. PID: %d\n", getpid());

    while (true) {
        sleep(1);
    }

    close(fd);
    return 0;
}
