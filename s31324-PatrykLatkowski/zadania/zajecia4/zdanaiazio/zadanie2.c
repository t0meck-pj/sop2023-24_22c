#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void hexDump(const char* fileName) {
    FILE* filePtr = fopen(fileName, "rb");
    if (filePtr == NULL) {
        perror("Nie można otworzyć pliku");
        return;
    }

    printf("Loading file: %s\n\n", fileName);

    const size_t chunkSize = 16;
    unsigned char dataBuffer[chunkSize];
    size_t fileOffset = 0;
    size_t i;

    while (1) {
        size_t bytesRead = fread(dataBuffer, 1, chunkSize, filePtr);
        if (bytesRead == 0) break;

        printf("%08lx  ", fileOffset);

        for (i = 0; i < bytesRead; ++i) {
            printf("%02x ", dataBuffer[i]);
        }

        if (bytesRead < chunkSize) {
            for (i = bytesRead; i < chunkSize; ++i) {
                printf("   ");
            }
        }

        printf(" ");
        for (i = 0; i < bytesRead; ++i) {
            printf("%c", isprint(dataBuffer[i]) ? dataBuffer[i] : '.');
        }

        printf("\n");
        fileOffset += bytesRead;
    }

    fclose(filePtr);
    printf("Closing file: %s\n", fileName);
}

int main() {
    char filePath[256];
    printf("Podaj ścieżkę do pliku: ");
    scanf("%255s", filePath);

    hexDump(filePath);

    return 0;
}