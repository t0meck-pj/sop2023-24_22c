#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Użycie: %s <liczba>\n", argv[0]);
        return 1;
    }

    int n = atoi(argv[1]);

    int pid = fork();

    if (pid < 0) {
        perror("fork");
        return 1;
    } else if (pid == 0) {
        printf("Proces potomny: Liczby nieparzyste od 1 do %d:\n", n);
        for (int i = 1; i <= n; i += 2) {
            printf("%d ", i);
        }
        printf("\n");
        return 0;
    } else {
        int sum = 0;
        for (int i = 0; i <= n; ++i) {
            sum += i;
        }
        printf("Proces rodzica: Suma liczb od 0 do %d: %d\n", n, sum);
    }

    return 0;
}
