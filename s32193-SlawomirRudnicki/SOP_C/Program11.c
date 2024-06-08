#define _POSIX_SOURCE
#include<stdio.h>
#include<signal.h>
#include<unistd.h>

int loop_break = 1;

void check_Lock();
void sigaction_register();
void handler(int signum){

    printf("Otrzymalem Sygnal %d\n", signum);
    remove("mleko.txt");
    loop_break = 0;
}

int main(){
    
    /*signal(SIGUSR1,handler);*/
    sigaction_register();
    
    check_Lock();

    while(loop_break){
        sleep(1);
    }


    return 0;
}

void check_Lock(){
    FILE *file;
    int pid;

    if(!access("mleko.txt", F_OK)){
        file = fopen("mleko.txt", "r");
        fscanf(file,"%d",&pid);
        kill(pid, SIGUSR1);
        raise(9);
    }
    else{
        file = fopen("mleko.txt", "w");
        fprintf(file, "%d", getpid());
        fclose(file);
    }
}


void sigaction_register(){
    struct sigaction act;
    act.sa_handler = handler;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    sigaction(SIGUSR1, &act, NULL);
}
