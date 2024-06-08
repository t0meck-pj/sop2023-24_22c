#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void handle_sigusr1(int sig) {
    printf("Otrzymano sygnał SIGUSR1. Kończę działanie.\n");
    exit(0);
}

int main() {
    printf("PID programu: %d\n", getpid());
    signal(SIGUSR1, handle_sigusr1);
    pause();
    return 0;
}
