#define _POSIX_SOURCE
#include<stdio.h>
#include<signal.h>
#include<unistd.h>

int loop_break = 1;

void check_Mleko();
void handler(int signum){

    printf("Otrzymalem Sygnal %d\n", signum);
    remove("mleko.txt");
    loop_break = 0;
}

int main(){
    
    signal(SIGUSR1,handler);
    
    check_Mleko();

    while(loop_break){
        sleep(1);
    }


    return 0;
}

void check_Mleko(){
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
