#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void signalHandler(int signal){
    if(signal == SIGUSR1){
        printf("Wykryto probe uruchomienia drugiej instancji programu.\n");
    }
    else if(signal == SIGINT){
        remove("/tmp/lock");
        exit(0);
    }
}

int main(){
    int file;
    
    signal(SIGUSR1, signalHandler);
    signal(SIGINT, signalHandler);

    file = open("/tmp/lock", O_CREAT | O_EXCL | O_RDWR, 0666);
    if(file == -1){
        printf("File already exists\n");
        kill(getpid(), SIGUSR1);
        exit(1);
    }
    else{
        int pid = getpid();
        write(file, &pid, sizeof(pid));
    }

    while(1){
        sleep(1);
    }
}