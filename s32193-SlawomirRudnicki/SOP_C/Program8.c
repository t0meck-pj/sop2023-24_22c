#include<stdio.h>
#include<stdlib.h>
#include<wait.h>
#include<unistd.h>
#include<sys/types.h>

int main(int argc, char** argv){
    int i;
   
    
   for ( i = 0; i < 100; i++)
   {
        if(fork() == 0){
            printf("Childpid: %d Parentpid: %d \n", getpid(), getppid());
            exit(0);   
        }       
         
   }
    while(wait(NULL)>0);
   
    
    

    return 0;
}
