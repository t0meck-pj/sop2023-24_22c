#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[]) {
        int height, i, j, k;

        height = atoi(argv[1]);

        for (i = 0; i < height; i++) {
                for (j = 0; j < height - i - 1; j++) {
                        printf(" ");
                }
                for (k = 0; k < 2 * i + 1; k++) {
                        printf("*");
                }
                printf("\n");
        }
        return 0;
}
