#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main () {
	pid_t child;
	child = fork();
	/*
	printf("Child = %d\n", child);
        printf("PID: %d\n", getpid());
        printf("PPID: %d\n", getppid());
        scanf ("%d", &number);
	*/
	if (child == 0){
	printf("Jestem dzieckiem: %d %d\n", getpid(), getppid() );
	}
	else if (child < 0){
	printf("Wystapil blad");
}
	else {
	wait(NULL);
	printf("jestem rodzicem: %d %d\n", getpid(), getppid() );
	}

        return 0;
}

