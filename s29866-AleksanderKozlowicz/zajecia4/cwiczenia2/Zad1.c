/* Napisz program wczytujący z pliku tekstowego ciąg liczb.
Format pliku jest taki:
liczba elementów ciągu (jako liczba naturalna)
Kolejne liczby - każda w nowej linii
Przykład:
3
5
1
9
Opis przykładu:
3 liczby do wczytania
liczby: 5, 1, 9
Niech program wypisze je w odwrotnej kolejności. Program powinien przyjmować zero albo jeden argument:
jeśli nie podano argumentu, to ma wczytywać ze standardowego wejścia
jeśli podano argument, to jest to nazwa pliku do wczytania
Skorzystaj z:
fopen
fclose
fscanf
Zabezpiecz przed przepełnieniem bufora.
Skorzystaj z funkcji do dynamicznej rezerwacji/alokacji pamięci:
malloc lub calloc
free */




#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *file;
    int *arr = NULL;
    int capacity = 0;
    int size = 0;
    int num;

    file = fopen("data.txt", "r");
    if (file == NULL) {
        printf("Error while opening file\n");
        return 1;
    }

    // Wczytywanie licznika elementów
    if (fscanf(file, "%d", &size) != 1 || size <= 0) {
        printf("Invalid number of elements in the file.\n");
        fclose(file);
        return 1;
    }

    // Dynamiczne alokowanie pamięci dla tablicy
    arr = (int*)malloc(size * sizeof(int));
    if (arr == NULL) {
        printf("Memory allocation failed.\n");
        fclose(file);
        return 1;
    }

    // Wczytywanie danych do tablicy
    while (fscanf(file, "%d", &num) == 1) {
        // Sprawdzanie czy tablica nie jest pełna
        if (capacity == size) {
            // Zwiększanie pojemności tablicy
            capacity = (capacity == 0) ? 1 : capacity * 2;
            int *temp = realloc(arr, capacity * sizeof(int));
            if (temp == NULL) {
                printf("Memory reallocation failed.\n");
                fclose(file);
                free(arr);
                return 1;
            }
            arr = temp;
        }
        // Dodawanie elementu do tablicy
        arr[size++] = num;
    }

    // Wyświetlanie zawartości tablicy
    printf("Elements read from file:\n");
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    // Zwalnianie zaalokowanej pamięci i zamykanie pliku
    free(arr);
    fclose(file);

    return 0;
}
