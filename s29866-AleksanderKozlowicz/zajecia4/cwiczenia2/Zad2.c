/* Napisz program, który będzie pozwalał na wyświetlenie dowolnego pliku w postaci takiej, jak w heksedytorach. 
Program powinien wypisać zawartość pliku w postaci liczb szesnastkowych będących wartościami kolejnych bajtów tego pliku. 
Warto zrobić tak, aby kolejne wartości były pogrupowane po 16, 8 albo po 4 w celu poprawy czytelności.
Pamiętaj!
Nie wszystkie bajty da się wydrukować
Niektóre są znakami specjalnymi */



#include <stdio.h>

#define BYTES_PER_LINE 16

void printHex(FILE *file) {
    unsigned char buffer[BYTES_PER_LINE];
    size_t bytesRead;

    while ((bytesRead = fread(buffer, sizeof(unsigned char), BYTES_PER_LINE, file)) > 0) {
        for (size_t i = 0; i < bytesRead; i++) {
            printf("%02x ", buffer[i]);
        }
        printf("| ");
        for (size_t i = 0; i < bytesRead; i++) {
            printf("%c", (buffer[i] >= 32 && buffer[i] <= 126) ? buffer[i] : '.');
        }
        printf("\n");
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Użycie: %s <nazwa_pliku>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "rb");
    if (file == NULL) {
        printf("Nie można otworzyć pliku %s\n", argv[1]);
        return 1;
    }

    printf("Zawartość pliku '%s' w formacie heksadecymalnym:\n", argv[1]);
    printHex(file);

    fclose(file);
    return 0;
}
