#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void print_odd_numbers(int limit) {
    for (int i = 1; i <= limit; i += 2) {
        printf("%d ", i);
    }
    printf("\n");
}

void sum_numbers_and_print(int limit) {
    int sum = 0;
    for (int i = 0; i <= limit; i++) {
        sum += i;
    }
    printf("Sum of numbers from 0 to %d is: %d\n", limit, sum);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <number>\n", argv[0]);
        return 1;
    }

    int limit = atoi(argv[1]);
    if (limit < 0) {
        fprintf(stderr, "The number must be non-negative.\n");
        return 1;
    }

    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        return 1;
    } else if (pid == 0) {
        print_odd_numbers(limit);
        exit(0);
    } else {
        
        int status;
        wait(&status); 
        sum_numbers_and_print(limit);
    }

    return 0;
}
