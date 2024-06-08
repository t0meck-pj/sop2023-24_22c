/* Napisz prosty program chat-u, który będzie korzystał z pliku w katalogu
 * /tmp do przekazywania wiadomości. Zastanów się jak to zrobić.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PATH "/tmp/file.txt"
#define END_CHAT_COMMAND "end_chat"
#define BUFFER 256

void writeToFile(const char *message);
void readFromFile();

int main() {
        char message[BUFFER];

        do {
                readFromFile();
                printf("Wpisz swoją wiadomość: ");
                fgets(message, sizeof(message), stdin);
                message[strcspn(message, "\n")] = 0;
                if (strcmp(message, END_CHAT_COMMAND) != 0) {
                        writeToFile(message);
                        system("clear");
                }
        } while (strcmp(message, END_CHAT_COMMAND) != 0);

        return 0;
}


void writeToFile(const char *message) {
        FILE *file;
        file = fopen(PATH, "a");
        if (file != NULL) {
                fprintf(file, "%s\n", message);
                fclose(file);
        } else {
                printf("Nie można otworzyć pliku do zapisu.\n");
        }
}

void readFromFile() {
        char message[BUFFER];
        FILE *file;
        file = fopen(PATH, "r");
        if (file != NULL) {
                while (fgets(message, sizeof(message), file)) {
                        printf("%s", message);
                }
                fclose(file);
        } else {
                printf("Plik do odczytu nie istnieje. Napisz wiadomość, aby go stworzyć.\n");
        }
}



/* Wykonanie (za pomocą screen):
 * s29986@szuflandia22:~/zadania/zajecia5$ ./zadanie6                                                s29986@szuflandia22:~/zadania/zajecia5$ ./zadanie6
 * Plik do odczytu nie istnieje. Napisz wiadomość, aby go stworzyć.                                  wiadomość1
 * Wpisz swoją wiadomość: wiadomość1                                                                 wiadomość1.1
 * wiadomość1                                                                                        wiadomość2.1
 * wiadomość1.1                                                                                      wiadomość3.1
 * wiadomość2.1                                                                                      wiadomość4.1
 * wiadomość3.1                                                                                      Wpisz swoją wiadomość: end_chat
 * wiadomość4.1                                                                                      s29986@szuflandia22:~/zadania/zajecia5$
 * wiadomość2
 * wiadomość3
 * Wpisz swoją wiadomość: end_chat
 * s29986@szuflandia22:~/zadania/zajecia5$
 */


/* Wniosek:
 * Trochę myślałem nad tym jak to rozwiązać i na nic lepszego nie wpadłem.
 * Mógłbym wykorzystać proces główny do odczytywania danych i proces potomka do
 * zapisywania danych, ale uznałem, że nie ma tutaj takiej potrzeby.
 *
 * Ten program działa w pętli, w której najpierw są wyświetlane wszystkie
 * wiadomości, po czym użytkownik może wysyłać kolejne do pliku. Zakończyć go
 * można wpisując "end_chat" (wykorzystuję do tego wynik strcmp z biblioteki
 * string.h). Do zapisywania i odczytywania z pliku wykorzstuje wcześniej
 * przygotowane funkcje (writeToFile i readFromFile).
 */
