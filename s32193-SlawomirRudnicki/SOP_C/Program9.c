#include<stdio.h>
#include<stdlib.h>
#include<wait.h>
#include<unistd.h>
#include<sys/types.h>

int main(){
    int i;
    
    for(i=0; i<10; i++){
        if(fork()>0){
            printf("child: %d parent: %d \n", getpid(), getppid());
            fork();
            exit(0);
        }    
    }
    while(wait(NULL)>0);
    return 0;
}