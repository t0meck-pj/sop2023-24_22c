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
    if (argc != 2) {
        printf("Usage: %s <wysokosc>\n", argv[0]);
        return 1;
    }

    int wysokosc = atoi(argv[1]);

    for (int i = 1; i <= wysokosc; i++) {
        for (int j = 0; j < wysokosc - i; j++) {
            printf(" ");
        }
        for (int j = 0; j < 2 * i - 1; j++) {
            printf("*");
        }
        printf("\n");
    }

    for (int i = 0; i < wysokosc - 1; i++) {
        printf(" ");
    }
    printf("|\n");

    return 0;
}
