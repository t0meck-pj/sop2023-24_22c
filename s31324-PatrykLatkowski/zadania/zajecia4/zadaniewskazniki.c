#include <stdio.h>

int (*maksimum)(int, int);
int (*minimum)(int, int);
int (*suma)(int, int);

int znajdzMax(int a, int b) {
    return (a > b) ? a : b;
}

int znajdzMin(int a, int b) {
    return (a < b) ? a : b;
}

int obliczSume(int a, int b) {
    return a + b;
}

int main() {
    maksimum = &znajdzMax;
    minimum = &znajdzMin;
    suma = &obliczSume;

    int idOperacji, liczbaElementow;

    printf("Podaj numer operacji (0 - maksimum, 1 - minimum, 2 - suma): ");
    scanf("%d", &idOperacji);

    printf("Podaj liczbê elementów: ");
    scanf("%d", &liczbaElementow);

    int tablica[liczbaElementow];

    printf("Podaj elementy:\n");
    for (int i = 0; i < liczbaElementow; ++i) {
        scanf("%d", &tablica[i]);
    }

    int wynik = tablica[0];
    for (int i = 1; i < liczbaElementow; ++i) {
        if (idOperacji == 0) {
            wynik = (*maksimum)(wynik, tablica[i]);
        } else if (idOperacji == 1) {
            wynik = (*minimum)(wynik, tablica[i]);
        } else if (idOperacji == 2) {
            wynik = (*suma)(wynik, tablica[i]);
        }
    }

    printf("Wynik: %d\n", wynik);

    return 0;
}

