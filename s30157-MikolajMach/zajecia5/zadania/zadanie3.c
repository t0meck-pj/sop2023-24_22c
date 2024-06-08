#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int calculate_sum(int n) {
    int sum = 0;
    for (int i = 0; i <= n; ++i) {
        sum += i;
    }
    return sum;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <number>\n", argv[0]);
        return 1;
    }

    int n = atoi(argv[1]);

    pid_t child_pid = fork();

    if (child_pid == -1) {
        perror("fork");
        return 1;
    } else if (child_pid == 0) {
        printf("Proces potomny - Liczby nieparzyste:\n");
        for (int i = 1; i <= n; i += 2) {
            printf("%d ", i);
        }
        printf("\n");
    } else {
        int sum = calculate_sum(n);
        wait(NULL);
        printf("Proces rodzica - Suma liczb od 0 do %d: %d\n", n, sum);
    }

    return 0;
}
