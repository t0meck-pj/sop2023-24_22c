/*
Napisz program wyświetlający tradycyjną choinkę o zadanej wysokości. Wysokość niech będzie podana jako parametr wywołania programu. Będziemy kompilować przy użyciu -wall -pedantic --ansi
Przydatne hasła to:

atoi

argc

for
*/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    
    int height = atoi(argv[1]);
    int i, j;


    if (argc != 2) {
        printf("Usage: %s <height>\n", argv[0]);
        return 1;
    }

    for (i = 0; i < height; i++) {
        for (j = 0; j < height - i - 1; j++) {
            printf(" ");
        }
        for (j = 0; j < 2 * i + 1; j++) {
            printf("*");
        }
        printf("\n");
    }

    return 0;
}