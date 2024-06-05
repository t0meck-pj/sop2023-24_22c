/*
This program reads data from text file. FIle should have this format:
1. First line should contain number of integers in file
2. Next lines should contain integers
*/

#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *file;
    int n;
    int *arr;
    int i;

    file = fopen("data.txt", "r");
    if (file == NULL) {
        printf("Error while opening file\n");
        return 1;
    }

    fscanf(file, "%d", &n);
    arr = (int*)malloc(n * sizeof(int));
    for (i = 0; i < n; i++) {
        fscanf(file, "%d", &arr[i]);
    }

    for (i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    free(arr);
    fclose(file);
    return 0;
}