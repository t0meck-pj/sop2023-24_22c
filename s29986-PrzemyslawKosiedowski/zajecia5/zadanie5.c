/* Napisz program, który uruchomi 100 procesów potomnych w taki sposób, że
 * będzie jeden rodzic i 100 potomków. Proces główny niech oczekuje na
 * zakończenie wszystkich procesów potomnych.
 * Przydatne funkcje: waitpid i wait
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {
        pid_t pid;
        int i = 0;
        int num_children = 100;
        if(argc == 2) {
                num_children = atoi(argv[1]);
        }

        printf("Główny %d || PID: %d || PPID: %d\n", i, getpid(), getppid());

        for(i = 0; i < num_children; i++) {
                pid = fork();

                if(pid == 0) {
                        printf("Potomek %d || PID: %d || PPID: %d\n", i + 1, getpid(), getppid());
                        sleep(10);
                        exit(0);
                } else if(pid > 0) {
                        /* Rodzic nowego potomka nic nie robi */
                } else {
                        printf("Błąd podczas tworzenia procesu potomka.\n");
                        return 1;
                }
        }

        for(i = 0; i < num_children; i++) {
                waitpid(-1, NULL, 0);
                sleep(1);
        }

        printf("Główny: Zakończono\n");

        return 0;
}




/* Wykonanie:
 * s29986@szuflandia22:~/zadania/zajecia5$ ./zadanie5 10
 * Główny 0 || PID: 4003437 || PPID: 3644766
 * Potomek 3 || PID: 4003445 || PPID: 4003437
 * Potomek 4 || PID: 4003447 || PPID: 4003437
 * Potomek 5 || PID: 4003448 || PPID: 4003437
 * Potomek 9 || PID: 4003452 || PPID: 4003437
 * Potomek 8 || PID: 4003451 || PPID: 4003437
 * Potomek 6 || PID: 4003449 || PPID: 4003437
 * Potomek 10 || PID: 4003453 || PPID: 4003437
 * Potomek 7 || PID: 4003450 || PPID: 4003437
 * Potomek 1 || PID: 4003443 || PPID: 4003437
 * Potomek 2 || PID: 4003444 || PPID: 4003437
 * Główny: Zakończono
 */


/* Wynik pstree (w trakcie działania wszystkich procesów):
 * systemd-+-VGAuthService
          |-agetty
          |-apache2---10*[apache2]
          |-bash
          |-cron
          |-dbus-daemon
          |-dhclient---3*[{dhclient}]
          |-exim4
          |-mariadbd---7*[{mariadbd}]
          |-mongod---32*[{mongod}]
          |-nmbd
          |-rpc.statd
          |-rpcbind
          |-rsyslogd---3*[{rsyslogd}]
          |-screen---bash---i_am_groot.sh---sleep
          |-screen---bash---zadanie6---zadanie6
          |-smbd-+-cleanupd
          |      |-lpqd
          |      `-smbd-notifyd
          |-sshd-+-sshd---sshd---bash---screen---screen-+-bash---zadanie5---10*[zadanie5]
          |      |                                      `-bash---pstree
          |      |-2*[sshd---sshd---bash---ssh]
          |      |-sshd---sshd---bash
          |      `-sshd---sshd---bash---vim
          |-11*[systemd---(sd-pam)]
          |-systemd-journal
          |-systemd-logind
          |-systemd-timesyn---{systemd-timesyn}
          |-systemd-udevd
          |-vmtoolsd---{vmtoolsd}
          |-winbindd---4*[winbindd]
          |-3*[zad6]
          |-zadanie6
          |-zadanieS1
          `-3*[zadanies1signal]
 */



/* Wniosek:
 * Do wykonania tego zadania zmodyfikowałem kod z zadania poprzedniego.
 * Pozwoliłem sobie również zostawić możliwość wprowadzenia dowolnej ilości
 * procesów potomnych do uruchomienia. Zostawiłem również sleep(), aby móc za
 * pomocą pstree sprawdzić, jak wygląda drzewo procesów, gdy są uruchomione
 * wszystkie na raz. Przedstawiam również wynik działania programu tylko dla 10
 * procesów potomnych dla lepszej czytelności.
 *
 * W tym programie proces główny kończy swoją pracę dopiero wtedy, gdy
 * wszystkie procesy potomne zakończą się. Dzieje się tak dzięki funkcji
 * waitpid(-1, NULL, 0), gdzie:
 *
 *  >  -1 oznacza, że funkcja waitpid będzie czekać na dowolny proces potomny;
 *
 *  >  NULL oznacza, że nie jesteśmy zainteresowani statusem zakończenia
 *     procesu potomnego;
 *
 *  >  0 oznacza, że nie używa żadnych specjalnych opcji;
 *
 * Dzięki temu zadaniu nauczyłem się kolejnego sposobu na zarządzanie
 * procesami, w tym przypadku ich zakończeniem za pomocą funkcji waitpid().
 */
