#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
    pid_t pid;
    pid = fork();
    if(pid == 0){
        pid = fork();
        if(pid == 0){
            pid = fork();
            if(pid == 0){
                printf("G\n");
            }
            else{
                wait(NULL);
                printf("F\n");
            }
        }
        else{
            wait(NULL);
            pid = fork();
            if(pid == 0){
                printf("E\n");
            }
            else{
                wait(NULL);
                printf("D\n");
            }
        }
    }
    else{
        wait(NULL);
        pid = fork();
        if(pid == 0){
            printf("C\n");
        }
        else{
            wait(NULL);
            printf("A\n");
        }
    }
    return 0;
}