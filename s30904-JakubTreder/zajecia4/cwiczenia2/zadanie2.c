#include <stdio.h>
#include <stdlib.h>

#define LINE_WIDTH 16

void displayHex(FILE *fp) {
    unsigned char buf[LINE_WIDTH];
    size_t n;

    while ((n = fread(buf, 1, LINE_WIDTH, fp)) > 0) {
        for (size_t i = 0; i < n; i++) {
            printf("%02X ", buf[i]);
        }
        for (size_t i = n; i < LINE_WIDTH; i++) {
            printf("   ");
        }
        printf(" | ");
        for (size_t i = 0; i < n; i++) {
            if (buf[i] >= 32 && buf[i] <= 126) {
                printf("%c", buf[i]);
            } else {
                printf(".");
            }
        }
        printf("\n");
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Użycie: %s <plik>\n", argv[0]);
        return 1;
    }

    FILE *fp = fopen(argv[1], "rb");
    if (fp == NULL) {
        printf("Nie można otworzyć pliku: %s\n", argv[1]);
        return 1;
    }

    printf("Zawartość pliku '%s' w formacie heksadecymalnym:\n", argv[1]);
    displayHex(fp);

    fclose(fp);
    return 0;
}
