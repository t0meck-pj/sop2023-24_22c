/*This code should compile using -Wall --ansi --pedantic gcc parameters*/
#include <stdio.h>

int main(int argc, char *argv[]) {
    FILE *file;
    int count = 0;
    int ch;
    int i;
    unsigned char buffer[16];
    unsigned int hexValue = 0x00000010; 

    if (argc < 2) {
        printf("Please provide a file name as an argument.\n");
        return 1;
    }

    file = fopen(argv[1], "r");
    if (file == NULL) {
        printf("Failed to open the file.\n");
        return 1;
    }

    while ((ch = fgetc(file)) != EOF) {
        buffer[count % 16] = ch; 
        count++;

        if (count % 16 == 0) {
            printf("%08X  ", hexValue);
            hexValue += 16;
            for (i = 0; i < 16; i++) {
                printf("%02X ", buffer[i]);
            }
            printf("  ");
            for (i = 0; i < 16; i++) {
                if (buffer[i] >= 32 && buffer[i] <= 126) {
                    printf("%c", buffer[i]);
                } else {
                    printf(".");
                }
            }
            printf("\n");
        }
    }

    fclose(file);
    return 0;
}
