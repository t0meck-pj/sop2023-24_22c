#define _POSIX_C_SOURCE 200112L

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/types.h>
#include <signal.h>

#define LOCK_FILE "/tmp/irmgrd.lock"

bool wait = true;

void usr1Handler(int sig) {
    printf("Wykryto probe uruchomienia drugiej instancji programu.\n");
}

void sigintHandler(int sig) {
    if (unlink(LOCK_FILE) != 0) {
        perror("Nie mozna usunac pliku lock");
    }
    exit(EXIT_SUCCESS);
}

int amIAlone(){
    pid_t PID;
    FILE *test = fopen("/tmp/irmgrd.lock", "r");
    if (fopen(LOCK_FILE, "r")){
        fscanf(test, "%d", &PID);
        fclose(test);
        printf("Wykryto dzialanie programu PID: %d\n", PID);
        kill(PID, SIGUSR1);
        exit(EXIT_FAILURE);
    }
    else{
        test = fopen(LOCK_FILE, "w");
        if (!test) {
            perror("Nie mozna utworzyc pliku lock");
            exit(EXIT_FAILURE);
        }
        fprintf(test, "%d", getpid());
        fclose(test);
        wait = false;
    }
    return 0;
}

int main(){
    signal(SIGUSR1, usr1Handler);
    signal(SIGINT, sigintHandler);

    amIAlone();

    while (!wait)
    {
        pause();
    }

    return 0;
}
