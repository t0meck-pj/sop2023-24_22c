/* Przygotuj program, który będzie pozwalał na uruchomienie tylko jednej swojej
 * instancji. Dodatkowo w momencie próby uruchomienia drugiej instancji będzie
 * powiadamiał już uruchomiony proces o tym. Można to zrobić tak:
 *  > Program uruchamia się i sprawdza, czy jest plik /tmp/lock
 *  > Jeśli taki plik nie istnieje, wtedy:
 *      - tworzony jest taki plik. Do niego zapisywany jest PID bieżącego
 *        procesu
 *      - program instaluje obsługę sygnału USR1, która w momencie otrzymania
 *        sygnału wypisuje tekst:
 *        "Wykryto próbę uruchomienia drugiej instancji programu."
 *      - program instaluje obsługę sygnału generowanego przez CTRL+C (poszukaj
 *        jaki to sygnał), która w momencie otrzymania tego sygnału skasuje
 *        plik /tmp/lock i spowoduje wyjście z pętli nieskończonej (patrz
 *        następny punkt)
 *      - program wykonuje pętlę nieskończoną zawierającą tylko instrukcję
 *        sleep.
 *  > Jeśli taki plik istnieje, wtedy:
 *      - Wczytywana jest zawartość tego pliku - pid procesu uruchomionego
 *      - generowany jest sygnał USR1 do procesu o pid takim jak wczytany
 *      - program kończy pracę
 */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>

#define PATH "/tmp/lockkk"

int kill(pid_t pid, int sig);

void sigusr1Handler(int signum);
void sigintHandler(int signum);

int main() {
        FILE *file;
        pid_t pid;

        file = fopen(PATH, "r");
        if (file != NULL) {
                fscanf(file, "%d", &pid);
                fclose(file);
                kill(pid, SIGUSR1);
                exit(0);
        } else {
                file = fopen(PATH, "w");
                if (file == NULL) {
                        printf("Błąd przy tworzeniu pliku.\n");
                        exit(1);
                }
                fprintf(file, "%d", getpid());
                fclose(file);

                signal(SIGUSR1, sigusr1Handler);
                signal(SIGINT, sigintHandler);
        }

        while (1) {
                sleep(1);
        }

        return 0;
}

void sigusr1Handler(int signum) {
        printf("Wykryto próbę uruchomienia drugiej instancji programu.\n");
}

void sigintHandler(int signum) {
        remove("/tmp/lockkk");
        printf("\nUsunięto plik /tmp/lockkk. Dobranoc.\n");
        exit(0);
}


/* Wykonanie (z użyciem screen):
 * s29986@szuflandia22:~/zadania/zajecia6$ ./zadanie2                                       s29986@szuflandia22:~/zadania/zajecia6$ cd /tmp; ls -l | grep s29986
 * Wykryto próbę uruchomienia drugiej instancji programu.                                   -rw-r--r-- 1 s29986     domain users   99 06-04 19:15 file.txt
 * ^C                                                                                       -rw------- 1 s29986     root         2894 06-05 10:24 krb5cc_54124
 * Usunięto plik /tmp/lockkk. Dobranoc.                                                     -rw-r--r-- 1 s29986     domain users    7 06-05 14:15 lockkk
 * s29986@szuflandia22:~/zadania/zajecia6$ cd /tmp; ls -l | grep s29986                     drwx------ 2 s29986     domain users 4096 06-03 14:47 tmux-54124
 * -rw-r--r-- 1 s29986     domain users   99 06-04 19:15 file.txt                           s29986@szuflandia22:/tmp$ ~/zadania/zajecia6/zadanie2
 * -rw------- 1 s29986     root         2894 06-05 10:24 krb5cc_54124                       s29986@szuflandia22:/tmp$
 * drwx------ 2 s29986     domain users 4096 06-03 14:47 tmux-54124
 * s29986@szuflandia22:/tmp$
 */



/* Wniosek:
 * Program obsługuje 2 przypadki. Pierwszy, tj. próbę uruchomienia drugiej
 * instancji programu i drugi, czyli pierwsze uruchomienie programu.
 *
 * W pierwszym przypadku, jeśli plik /tmp/lockkk istnieje (nazwę zmieniłem,
 * ponieważ już taki plik istniał w /tmp) to zostaje z niego odczytany PID
 * procesu pierwszej instancji. Następnie wysłany zostaje do niej sygnał
 * SIGUSR1. W tym momencie pierwsza instancja wyświetla odpowiedni komunikat,
 * a druga instancja kończy swoją pracę.
 *
 * W drugim przypadku program tworzy plik i zapisuje w nim swój PID. Następnie
 * instaluje obsługę sygnałów SIGUSR1 i SIGINT. Program działa, dopóki nie
 * zostanie do niego wysłany sygnał SIGINT (2). Może on zostać wysłany z innego
 * terminala lub poprzez CTRL+C. Po jego otrzymaniu program usuwa plik i
 * kończy działanie.
 *
 * Dzięki temu zadaniu dowiedziałem się jak manipulować pracą programu za
 * pomocą sygnałów i jak ograniczyć uruchomienie tylko jednej instancji
 * programu jednocześnie.
 */

