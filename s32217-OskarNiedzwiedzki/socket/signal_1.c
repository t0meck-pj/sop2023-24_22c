#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void signal_sigusr1(int signum){
	printf("\nSIGUSR1 Received\nEnding program...\n");
	exit(EXIT_SUCCESS);
}

int main(){
	signal(SIGUSR1, signal_sigusr1);
	printf("my pid: %d\nNow i am gonna enter loop, send me SIGUSR1 to end me\n",getpid());
       	while(1){
		printf("Waiting for SIGUSR1...\n");
		sleep(10);
	}

	return EXIT_SUCCESS;
}
