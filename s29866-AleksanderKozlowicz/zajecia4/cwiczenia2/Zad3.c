#include <stdio.h>
#include <stdlib.h>

int maximum(int a, int b) {
    return (a > b) ? a : b;
}

int minimum(int a, int b) {
    return (a < b) ? a : b;
}

int suma(int a, int b) {
    return a + b;
}

int main() {
    int (*functions[3])(int, int) = {maximum, minimum, suma};

    int functionId, elementCount;
    printf("Podaj numer funkcji (0 - maksimum, 1 - minimum, 2 - suma): ");
    scanf("%d", &functionId);
    if (functionId < 0 || functionId > 2) {
        printf("Nieprawidłowy numer funkcji\n");
        return 1;
    }

    printf("Podaj liczbę elementów ciągu: ");
    scanf("%d", &elementCount);
    if (elementCount <= 0) {
        printf("Liczba elementów musi być dodatnia\n");
        return 1;
    }

    int v;
    printf("Podaj %d liczb: ", elementCount);
    scanf("%d", &v);

    for (int i = 1; i < elementCount; i++) {
        int element;
        scanf("%d", &element);
        v = functions[functionId](v, element);
    }

    printf("Wynik: %d\n", v);

    return 0;
}
