#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void handle_sigusr1(int sig) {
    printf("Received SIGUSR1\n");
}

int main() {
    printf("Program PID: %d\n", getpid());

    signal(SIGUSR1, handle_sigusr1);

    printf("Waiting for signal...\n");
    pause();
    
    return 0;
}