#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

void handle_signal(int sig) {
    if (sig == SIGUSR1) {
        printf("Otrzymano sygnał SIGUSR1. \n");
        exit(0);
    }
}

int main() {
    signal(SIGUSR1, handle_signal);

    printf("PID programu: %d\n", getpid());

    while (1) {
        pause();
    }

    return 0;
}

