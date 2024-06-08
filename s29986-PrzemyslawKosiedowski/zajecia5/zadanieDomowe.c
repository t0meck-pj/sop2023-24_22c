/* Napisz program, który wygeneruje drzewko procesów wyglądające tak
 * (oczywiście procesy nie będą się nazywały A, B, ...):
 * A \
 *   |\B \
 *   |   |\D
 *   |    \E
 *    \C \
 *        |\F
 *         \G
 * A jest rodzicem 2 procesów - B oraz C, a te są odpowiednio rodzicami D i E,
 * oraz F i G.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void createChild();

int main() {
        pid_t pidB;
        pid_t pidC;
        char buffer[50];

        pidB = fork();
        if (pidB == 0) {
                createChild();
                createChild();
                sleep(10);
                exit(0);
        } else if (pidB < 0) {
                printf("Błąd przy tworzeniu procesu B.");
                exit(1);
        }

        pidC = fork();
        if (pidC == 0) {
                createChild();
                createChild();
                sleep(10);
                exit(0);
        } else if (pidC < 0) {
                printf("Błąd przy tworzeniu procesu C.");
                exit(1);
        }

        sleep(1);
        sprintf(buffer, "pstree -ap %d | grep -v pstree", getpid());
        system(buffer);

        waitpid(pidB, NULL, 0);
        waitpid(pidC, NULL, 0);

        return 0;
}

void createChild() {
        if (fork() == 0) {
                sleep(10);
                exit(0);
        }
}



/* Wynik:
 * zadanieDomowe,2523270
 *  |-zadanieDomowe,2523276
 *  |   |-zadanieDomowe,2523278
 *  |   `-zadanieDomowe,2523280
 *  `-zadanieDomowe,2523277
 *      |-zadanieDomowe,2523279
 *      `-zadanieDomowe,2523281
 */



/* Wniosek:
 * Program tworzy drzewo procesów zgodne z zadaniem. Tym razem polecenie pstree
 * również w nim wykonuję, znacznie ułatwiło mi to sprawdzanie. Korzystam z
 * parametrów: a (wyłącza kompaktowanie dla procesów), p (wyświetla PID).
 * Dodatkowo filtruję wynik za pomocą grep -v, który usuwa z niego polecenie 
 * pstree.
 */
