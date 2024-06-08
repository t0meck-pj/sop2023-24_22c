#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void printHexLine(unsigned char *buffer, int size, long offset) {
    printf("%08lX  ", offset);

    for (int i = 0; i < 16; ++i) {
        if (i < size) {
            printf("%02X ", buffer[i]);
        } else {
            printf("   ");
        }
    }

    printf(" ");

    for (int i = 0; i < 16; ++i) {
        if (i < size) {
            if (isprint(buffer[i])) {
                printf("%c", buffer[i]);
            } else {
                printf(".");
            }
        } else {
            printf(" ");
        }
    }

    printf("\n");
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "rb");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    printf("Loading file: %s\n\n", argv[1]);

    unsigned char buffer[16];
    size_t bytesRead;
    long offset = 0;

    while ((bytesRead = fread(buffer, 1, sizeof(buffer), file)) > 0) {
        printHexLine(buffer, bytesRead, offset);
        offset += bytesRead;
    }

    if (ferror(file)) {
        perror("Error reading file");
    }

    fclose(file);
    printf("\nClosing file: %s\n", argv[1]);

    return 0;
}
