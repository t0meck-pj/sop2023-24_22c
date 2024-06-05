/*
This program reads data from a text file and prints them from last to first. The file should have the following format:
1. The first line should contain the number of integers in the file.
2. The next lines should contain the integers.

The program takes 0 or 1 arguments. If 0, it reads from stdin. If 1, it reads from a file with the name provided as an argument.
*/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    FILE *file;
    int n;
    int *arr;
    int i;

    if (argc == 1) {
        file = stdin;
    } else if (argc == 2) {
        file = fopen(argv[1], "r");
        if (file == NULL) {
            printf("Error while opening file\n");
            return 1;
        }
    } else {
        printf("Invalid number of arguments\n");
        return 1;
    }

    fscanf(file, "%d", &n);
    arr = (int*)malloc(n * sizeof(int));
    for (i = 0; i < n; i++) {
        fscanf(file, "%d", &arr[i]);
    }

    for (i = n - 1; i >= 0; i--) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    free(arr);
    if (file != stdin) {
        fclose(file);
    }
    return 0;
}