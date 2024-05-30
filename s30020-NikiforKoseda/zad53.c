#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void printUnevenNumbers(int n) {
    int i;
    for (i = 1; i <= n; i += 2) {
        printf("%d ", i);
    }
    printf("\n");
}

int main(int argc, char *argv[]) {
    int number;
    pid_t pid;

    if (argc != 2) {
        printf("Usage: %s <number>\n", argv[0]);
        return 1;
    }

    number = atoi(argv[1]);
    pid = fork();

    if (pid < 0) {
        printf("Fork failed.\n");
    } else if (pid == 0) {
        printUnevenNumbers(number);
    } else {
        wait(NULL); 
        printf("Result: %d\n", number + 1);
    }

    return 0;
}