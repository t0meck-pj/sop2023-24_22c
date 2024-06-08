#include<stdio.h>
#include<signal.h>
#include<unistd.h>

void handler(int signum){
    printf("HELLO THERE \n");
}

int main(){
    
    signal(SIGINT, SIG_IGN);
    signal(SIGUSR1,handler);

    pause();

    return 0;
}
