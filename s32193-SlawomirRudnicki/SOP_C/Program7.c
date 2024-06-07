#include<stdio.h>
#include<stdlib.h>
#include<wait.h>
#include<unistd.h>
#include<sys/types.h>

int main(int argc, char** argv){
    int child_iter;
    int parent_iter;
    int child_operation = 1;
    int parent_operation = 0;
    pid_t child_pid = fork();

    if(child_pid < 0){
        printf("Operacja zakonczona niepowodzeniem \n");
    }
    else if (child_pid == 0)
    {
        for (child_iter=0; child_iter<(*argv[1]-'0'); child_iter++)
        {
            printf("Value: %d\n",child_operation);
            child_operation+=2;
        }
        
    }else{
        wait(NULL);
        for (parent_iter = 0; parent_iter <= (*argv[1]-'0'); parent_iter++)
        {
            parent_operation+=parent_iter;
            printf("Value2: %d\n", parent_operation);
        }
    }
    return 0;
}


    