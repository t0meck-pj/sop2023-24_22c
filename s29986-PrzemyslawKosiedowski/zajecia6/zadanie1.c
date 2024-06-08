/* Przygotuj prosty programik, który:
 *      - Wypisze na ekranie swój PID
 *      - będzie czekał w pętli nieskończonej do momentu otrzymania sygnału
 *        użytkownika (SIGUSR1)
 *      - W momencie otrzymania tego sygnału program powinien wypisać na
 *        ekranie, że dostał sygnał i się zakończyć.
 */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void handler(int signum) {
        printf("Otrzymano sygnał SIGUSR1, dobranoc.\n");
        exit(1);
}

int main() {
        printf("Wyślij SIGUSR1 (10), aby zamknąć program. ");
        printf("PID: %d\n", getpid());

        signal(SIGUSR1, handler);

        while(1) {
                sleep(1);
        }

        return 0;
}



/* Wykonanie (z użyciem screen):
 * s29986@szuflandia22:~/zadania/zajecia6$ ./zadanie1               s29986@szuflandia22:~/zadania/zajecia6$ kill -10 2658274
 * Wyślij SIGUSR1 (10), aby zamknąć program. PID: 2658274           s29986@szuflandia22:~/zadania/zajecia6$
 * Otrzymano sygnał SIGUSR1, dobranoc.
 * s29986@szuflandia22:~/zadania/zajecia6$
 */



/* Wniosek:
 * Po zarejestrowaniu obsługi sygnału program działa w pętli,
 * dopóki nie otrzyma sygnału SIGUSR1. Gdy sygnał zostanie przechwycony,
 * wywołana zostaje funkcja handler, która wyświetla komunikat i kończy
 * działanie programu. To zadanie pokazało mi podstawy obsługi sygnałów.
 */
