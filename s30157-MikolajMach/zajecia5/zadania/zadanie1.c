#include <stdio.h>
#include <unistd.h>

int main() {
    printf("PID: %d\n", getpid());
    printf("PPID: %d\n", getppid());
    while(1) {
        getchar();
    }
    return 0;
}

