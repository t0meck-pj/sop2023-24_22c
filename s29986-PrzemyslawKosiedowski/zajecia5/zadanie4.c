/* Napisz program, który uruchomi 100 procesów w taki sposób, że każdy kolejny
 * potomek stworzy potomka. Niech każdy proces poczeka na zakończenie procesu
 * potomka. Możesz korzystać z oczekiwania na wejście lub z komendy sleep i
 * zobacz czy drzewko procesów jest takie jak się spodziewasz (możesz w tym
 * celu ograniczyć liczbę procesów do 10). Zobacz podpowiedź na początku tej
 * strony. Czyli drzewo procesów ma wynikowo wyglądać tak:
 *      główny -> potomek1 -> potomek2 -> ... -> potomek99 -> potomek100
 * Przydatne przy sprawdzaniu:
 *      Drzewo procesów można wydrukować poleceniem pstree
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
                        sleep(1);
                } else if(pid > 0) {
                        wait(NULL);
                        printf("Potomek %d: Zakończono\n", i + 1);
                        sleep(2);
                        break;
                } else {
                        printf("Błąd podczas tworzenia procesu potomka.\n");
                        return 1;
                }
        }

        if(i == 0) {
                printf("Główny: Zakończono\n");
        }

        return 0;
}



/* Wynik programu:
 * s29986@szuflandia22:~/zadania/zajecia5$ ./zadanie4 10
 * Główny 0 || PID: 3022247 || PPID: 2856529
 * Potomek 1 || PID: 3022255 || PPID: 3022247
 * Potomek 2 || PID: 3026161 || PPID: 3022255
 * Potomek 3 || PID: 3030079 || PPID: 3026161
 * Potomek 4 || PID: 3033876 || PPID: 3030079
 * Potomek 5 || PID: 3037663 || PPID: 3033876
 * Potomek 6 || PID: 3041418 || PPID: 3037663
 * Potomek 7 || PID: 3045176 || PPID: 3041418
 * Potomek 8 || PID: 3048969 || PPID: 3045176
 * Potomek 9 || PID: 3052751 || PPID: 3048969
 * Potomek 10 || PID: 3056567 || PPID: 3052751
 * Potomek 10: Zakończono
 * Potomek 9: Zakończono
 * Potomek 8: Zakończono
 * Potomek 7: Zakończono
 * Potomek 6: Zakończono
 * Potomek 5: Zakończono
 * Potomek 4: Zakończono
 * Potomek 3: Zakończono
 * Potomek 2: Zakończono
 * Potomek 1: Zakończono
 * Główny: Zakończono
 */



/* Wynik pstree (pracowało w tym czasie 10 potomków):
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
           |-sshd-+-sshd---sshd---bash---screen---screen-+-bash---zadanie4---zadanie4---zadanie4---zadanie4---zadanie4---zadanie4---za+
           |      |                                      `-bash---pstree
           |      |-2*[sshd---sshd---bash---ssh]
           |      |-sshd---sshd---bash---man---pager
           |      |-sshd---sshd---bash
           |      |-5*[sshd---sshd---sftp-server]
           |      |-sshd---sshd---bash---cat
           |      `-sshd---sshd
           |-10*[systemd---(sd-pam)]
           |-systemd-journal
           |-systemd-logind
           |-systemd-timesyn---{systemd-timesyn}
           |-systemd-udevd
           |-vmtoolsd---{vmtoolsd}
           |-winbindd---5*[winbindd]
           |-3*[zad6]
           |-zadanie6
           |-zadanieS1
           `-3*[zadanies1signal]
 */



/* Wniosek:
 * Program domyślnie tworzy 100 procesów potomnych. Dodałem możliwość
 * wprowadzania ilości procesów potomnych do utworzenia dla własnej wygody przy
 * testowaniu. Wykorzystałem do tego celu również polecenie sleep. Dla lepszej
 * czytelności wyświetlam komunikat o wyłączonym procesie głównym tylko dla
 * pierwszego rodzica.
 * Dzięki temu zadaniu dowiedziałem się jak wydrukować drzewo procesów.
 */
