#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
        pid_t child = fork();
	
	if(child == 0 )
	{
		printf("Jestem dzieciekiem. %d\n", getpid());
        } else
		{wait(NULL); printf("Jestem rodzicem. %d\n", getpid());}
    return 0;
}

