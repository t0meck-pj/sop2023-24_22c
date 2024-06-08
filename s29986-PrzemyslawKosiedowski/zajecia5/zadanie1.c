/* Napisz program, który:
 *      - przedstawi swój numer PID, oraz PPID
 *      - po wypisaniu, będzie czekał na standardowym wejściu na dane od
 *        użytkownika.
 *      - Uruchom program - nic nie podawaj na wejściu (program powinien czekać
 *        w nieskończoność).Uruchom nowy terminal. W nim za pomocą komendy kill
 *        zamknij ten program korzystając z PID wypisanego przez niego na
 *        początku.
 */

#include <stdio.h>
#include <unistd.h>

int main() {
        int number;
        printf("PID: %d\n", getpid());
        printf("PPID: %d\n", getppid());
        scanf("%d", &number);

        return 0;
}



/* Wykonanie:
 * s29986@szuflandia22:~/zadania/zajecia5$ ./zadanie1               s29986@szuflandia22:~/zadania/zajecia5$ kill 2149423
 * PID: 2149423                                                     s29986@szuflandia22:~/zadania/zajecia5$
 * PPID: 2027828
 * Zakończony
 */



/* Wniosek:
 * Program był zrobiony wspólnie na zajęciach. Wyżej przedstawiam jego
 * działanie z użyciem screen. Dzięki temu zadaniu dowiedziałem się jak w C
 * uzyskać PID i PPID procesu.
 */
