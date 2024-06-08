/* Napisz program, który uruchomi podproces za pomocą komendy fork. Niech
 * proces rodzica oczekuje na proces potomka. Oba procesy powinny wypisać swój
 * PID oraz PPID.
 */

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
        pid_t identity;
        identity = fork();

        if(identity == 0) {
                printf("Jestem dzieckiem\nPID: %d\nPPID: %d\n", getpid(), getppid());
        } else if(identity < 0) {
                printf("Wystąpił błąd\n");
        } else {
                wait(NULL);
                printf("Jestem rodzicem\nPID: %d\nPPID: %d\n", getpid(), getppid());
        }

        return 0;
}



/* Wykonanie:
 * s29986@szuflandia22:~/zadania/zajecia5$ ./zadanie2
 * Jestem dzieckiem
 * PID: 3614002
 * PPID: 3613998
 * Jestem rodzicem
 * PID: 3613998
 * PPID: 1618512
 * s29986@szuflandia22:~/zadania/zajecia5$ ./zadanie2
 * Jestem dzieckiem
 * PID: 3667455
 * PPID: 3667450
 * Jestem rodzicem
 * PID: 3667450
 * PPID: 1618512
 * s29986@szuflandia22:~/zadania/zajecia5$ ./zadanie2
 * Jestem dzieckiem
 * PID: 3671647
 * PPID: 3671645
 * Jestem rodzicem
 * PID: 3671645
 * PPID: 1618512
 * s29986@szuflandia22:~/zadania/zajecia5$ ./zadanie2
 * Jestem dzieckiem
 * PID: 3674349
 * PPID: 3674342
 * Jestem rodzicem
 * PID: 3674342
 * PPID: 1618512
 */



/* Wniosek:
 * Program był zrobiony wspólnie na zajęciach. Pokazuje on zastosowanie fork(),
 * który w trakcie wywołania tworzy nowy proces (kopię procesu rodzica). Taki
 * proces otrzymuje unikalny PID, a jego PPID jest ustawiony na PID procesu
 * rodzica. Po tej operacji oba procesy są wykonywane niezależnie (przynajmniej
 * tak to rozumiem).
 */
