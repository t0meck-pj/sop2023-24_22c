#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>


int main(int argc, char const *argv[])
{
    pid_t pid = getpid();
    pid_t ppid = getppid();
    
    printf("Mój PID: %d\n", pid);
    printf("Mój PPID: %d\n", ppid);
    /*czekanie  na  usera*/
    getchar();    
    return 0;
}

/* po wykoniu polecenia kill <pid> program został zakończony oraz wypisało mi na ekranie "Zakończono" */

