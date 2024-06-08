#include <stdio.h>
#include <stdlib.h>

void readNumbers(FILE *file, int **numbers, int *count) {
    fscanf(file, "%d", count);
    *numbers = (int *)malloc((*count) * sizeof(int));

    for (int i = 0; i < *count; ++i) {
        fscanf(file, "%d", &(*numbers)[i]);
    }
}

void printNumbersReversed(int *numbers, int count) {
    for (int i = count - 1; i >= 0; --i) {
        printf("%d\n", numbers[i]);
    }
}

int main(int argc, char *argv[]) {
    FILE *file = NULL;
    int *numbers = NULL;
    int count = 0;

    if (argc == 2) {
        file = fopen(argv[1], "r");
        if (file == NULL) {
            fprintf(stderr, "Nie można otworzyć pliku %s\n", argv[1]);
            return 1;
        }
    } else {
        file = stdin;
    }

    readNumbers(file, &numbers, &count);

    if (file != stdin) {
        fclose(file);
    }

    printNumbersReversed(numbers, count);

    free(numbers);
    return 0;
}

