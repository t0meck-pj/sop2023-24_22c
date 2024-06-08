#include <stdio.h>
#include <stdlib.h>

int findMax(int a, int b) {
    return (a > b) ? a : b;
}

int findMin(int a, int b) {
    return (a < b) ? a : b;
}

int calculateSum(int a, int b) {
    return a + b;
}

int main() {
    int (*operations[3])(int, int) = {findMax, findMin, calculateSum};

    int operationId, elementCount;
    printf("Wybierz operację (0 - maksimum, 1 - minimum, 2 - suma): ");
    scanf("%d", &operationId);
    if (operationId < 0 || operationId > 2) {
        printf("Nieprawidłowy wybór operacji\n");
        return 1;
    }

    printf("Podaj liczbę elementów: ");
    scanf("%d", &elementCount);
    if (elementCount <= 0) {
        printf("Liczba elementów musi być dodatnia\n");
        return 1;
    }

    int value;
    printf("Podaj %d liczb: ", elementCount);
    scanf("%d", &value);

    for (int i = 1; i < elementCount; i++) {
        int element;
        scanf("%d", &element);
        value = operations[operationId](value, element);
    }

    printf("Wynik: %d\n", value);

    return 0;
}
