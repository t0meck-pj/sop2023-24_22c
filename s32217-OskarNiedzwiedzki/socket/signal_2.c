#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <signal.h>

void lock_handler(int);
void ctrlc_handler(int);

int main(){
	FILE* f = NULL;
	int pid=0;
	char buffer[32];
	struct sigaction sigusr1, struct sigaction ctrlc;

	sigusr1.sa_handler=lock_handler;
	ctrlc.sa_handler=ctrlc_handler;


	f = fopen("/tmp/s32217_flock","r");
	if(f == NULL)
		f = fopen("/tmp/s32217_flock","w");

	/*if there is pid inside file, get it, and send SIGUSR1 to it*/
	if(fscanf(f,"%d", &pid)==1){
		sprintf(buffer,"kill -10 %d", pid);
		system(buffer);
		fclose(f);
		exit(EXIT_FAILURE);
	}

	sigaction(SIGUSR1,&sigusr1,NULL); /*create lock signal*/
	sigaction(SIGINT,&ctrlc, NULL); /*ctrl + c signal handler*/
	fprintf(f,"%d\n", getpid());   /*write pid into lock file*/
	fclose(f); /*close the file, to save it*/

	while(1){
		printf("Running...\n");
		sleep(10);
	}

}

void lock_handler(int signum){
	printf("Wykryto probe uruchomienia drugiej instacji programu...\n");
}

void ctrlc_handler(int signum){
	system("rm /tmp/s32217_flock");
	printf("\nReceived SIGINT signal, lock file has been deleted\nExiting...");
	exit(EXIT_SUCCESS);
}

