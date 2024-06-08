#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<wait.h>

int main(){
   
    pid_t child_pid;
    child_pid = fork();

    if(child_pid == 0){
        printf("Jestem dzieckiem: %d\n a o to moj rodzic: %d\n", getpid(), getppid());
    }
    else if (child_pid > 0)
    {
        printf("Jestem parentem: %d\n moje dziecko to: %d \n a moj rodzic to: %d \n", getpid(),child_pid, getppid());
        wait(NULL);
    }
    else if (child_pid < 0)
    {
        printf("Operacja zakonczona niepowodzeniem");
    }
    
    
    
    
   


    return 0;
}
