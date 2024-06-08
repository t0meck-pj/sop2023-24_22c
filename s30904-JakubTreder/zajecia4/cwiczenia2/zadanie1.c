#include <stdio.h>
#include <stdlib.h>

#define BYTES_PER_LINE 16
#define MAX_BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
    FILE *plik;
    unsigned char buffer[BYTES_PER_LINE];
    size_t bytes_read;
    int i, j;

    if (argc != 2) {
        printf("Użycie: %s <nazwa_pliku>\n", argv[0]);
        return 1;
    }

    plik = fopen(argv[1], "rb");
    if (plik == NULL) {
        printf("Nie można otworzyć pliku: %s\n", argv[1]);
        return 1;
    }

    printf("Ładowanie pliku: %s\n\n", argv[1]);

    i = 0;
    while ((bytes_read = fread(buffer, 1, BYTES_PER_LINE, plik)) > 0) {
        printf("%08X  ", i);

        for (j = 0; j < bytes_read; j++) {
            if (j == BYTES_PER_LINE / 2) {
                printf(" ");
            }
            printf("%02X ", buffer[j]);
        }

        for (; j < BYTES_PER_LINE; j++) {
            if (j == BYTES_PER_LINE / 2) {
                printf(" ");
            }
            printf("   ");
        }

        printf(" |");
        for (j = 0; j < bytes_read; j++) {
            if (buffer[j] >= 32 && buffer[j] <= 126) {
                printf("%c", buffer[j]);
            } else {
                printf(".");
            }
        }
        printf("|\n");

        i += BYTES_PER_LINE;
    }

    printf("Zamknięcie pliku: %s\n", argv[1]);
    fclose(plik);

    return 0;
}

