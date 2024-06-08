/* Napisz program, który będzie pobierał jeden argument z wiersza poleceń  i
 * będzie obliczał w 2 procesach:
 *      - Proces rodzica: Wartość sumy liczb od 0 do wartości zadanej jako
 *        pierwszy argument wykonania programu.
 *      - Proces potomny: Wypisujący liczby nieparzyste od 1 do wartości
 *        zadanej jako pierwszy argument wykonania programu.
 *      - Program powinien wypisać wyniki w kolejności takiej, że najpierw
 *        wypisze wynik proces potomny, a następnie proces rodzica.
 *      - Nie korzystaj z komendy sleep.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {
        pid_t identity;
        int number;
        int sum = 0;
        int i;

        if (argc != 2) {
                printf("Podano złą ilość argumentów.\n");
                return 1;
        }

        number = atoi(argv[1]);

        identity = fork();
        if(identity < 0) {
                printf("Wystąpił błąd\n");
        } else if(identity == 0) {
                printf("Jestem dzieckiem || PID: %d || PPID: %d\n", getpid(), getppid());
                printf("Liczby nieparzyste: ");
                for (i = 1; i <= number; i++) {
                        if (i % 2 != 0) {
                                printf("%d ", i);
                        }
                }
        } else {
                wait(NULL);
                printf("\nJestem rodzicem || PID: %d || PPID: %d\n", getpid(), getppid());
                sum = number * (number + 1) / 2;
                printf("Suma liczb od 0 do %d: %d\n", number, sum);
        }

        return 0;
}



/* Wynik:
 * s29986@szuflandia22:~/zadania/zajecia5$ ./zadanie3 6
 * Jestem dzieckiem || PID: 2133273 || PPID: 2133268
 * Liczby nieparzyste: 1 3 5
 * Jestem rodzicem || PID: 2133268 || PPID: 3583214
 * Suma liczb od 0 do 6: 21
 * s29986@szuflandia22:~/zadania/zajecia5$ ./zadanie3 10
 * Jestem dzieckiem || PID: 2519555 || PPID: 2519552
 * Liczby nieparzyste: 1 3 5 7 9
 * Jestem rodzicem || PID: 2519552 || PPID: 3583214
 * Suma liczb od 0 do 10: 55
 */


/* Wniosek:
 * Do wykonania tego zadania zmodyfikowałem kod z zadania drugiego. Proces
 * rodzica czeka (wait(NULL)), aż dziecko wykona swoje zadanie (wypisze liczby
 * nieparzyste), po czym wykonuje własne (suma).
 */
