#include <stdio.h>
#include <unistd.h>

int main() {

    int number;
    printf("PID: %d\n", getpid());
    printf("PPID: %d\n", getppid());

    scanf("%d", &number);

    return 0;

}
