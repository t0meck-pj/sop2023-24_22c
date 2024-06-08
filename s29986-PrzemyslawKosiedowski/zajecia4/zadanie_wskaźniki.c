/* Napisz program z 3 funkcjami, każda funkcja niech będzie miała taką
 * sygnaturkę: int (*f)(int,int)
 *      - Niech będą to funkcje: maksimum, minimum oraz suma.
 *
 * Zapamiętaj wskaźniki do tych funkcji w tablicy trójelementowej
 *
 * Niech program pobiera kolejno wartości:
 *      - functionId - liczba od 0 do 2 oznaczająca indeks funkcji w tablicy
 *      - elementCount - liczba elementów ciągu do pobrania
 *      - kolejno liczby w ilości elementCount
 *
 * Niech program przetwarza wczytaną tablicę w taki sposób, że:
 *      - Niech v przyjmie wartość pierwszego elementu
 *      - w pętli po wszystkich elementach od drugiego (indeks 1 w tablicy)
 *              - wykona funkcję o numerze functionId przekazując jako argumenty
 *                v oraz element o aktualnym indeksie. Niech wynik zostanie
 *                zapisany do v
 *      - Wypisze wartość v na koniec
 *
 * Czyli piszemy program który pozwoli na wykonanie albo sumy, albo znalezienia
 * maksimum, albo znalezienia minimum z elementCount liczb. Program nie będzie
 * korzystał z instrukcji warunkowych (w pętli głównej) do wyboru jaka funkcja
 * ma być wykonana.
 * Czyli nigdzie w kodzie nie może pojawić się instrukcja if ani switch.
 *
 * Korzystając z wiedzy z poprzedniego zadania, napisz funkcję, która będzie
 * przetwarzała tablicę za pomocą uniwersalnej funkcji podanej jako argument
 * funkcji. Na przykład:
 * int wynik = forAll(tablica, liczbaElementow, maksimum);
 * gdzie maksimum to nazwa funkcji porownojacej dwie wartosci
 */

#include <stdio.h>
#include <stdlib.h>

int (*functions[3])(int, int);

int max(int a, int b);
int min(int a, int b);
int sum(int a, int b);

int forAll(int* elements, int amount, int (*f)(int, int));

int main(int argc, char* argv[]) {
        int functionId;
        int elementCount;
        int result;
        int* elements;
        int i;
        int scanResult;

        functions[0] = max;
        functions[1] = min;
        functions[2] = sum;


        if(argc != 1) {
                printf("Błąd - Program należy uruchomić bez podawania argumentów.\n");
                return 1;
        }

        printf("Podaj indeks funkcji (0 - maksimum, 1 - minimum, 2 - suma): ");
        scanf("%d", &functionId);
        if(functionId < 0 || functionId > 2) {
                printf("Podano niepoprawny indeks.\n");
                return 1;
        }

        printf("Podaj ilość elementów: ");
        if(scanf("%d", &elementCount) != 1 || elementCount < 1) {
                printf("Podano niepoprawną ilość elementów.\n");
                return 1;
        }

        elements = (int*)malloc(sizeof(int) * elementCount);
        if(elements == NULL) {
                printf("Błąd podczas przydzielania pamięci.\n");
                return 1;
        }

        for (i = 0; i < elementCount; i++) {
                do {
                        printf("Podaj element %d: ", i+1);
                        scanResult = scanf("%d", &elements[i]);
                        while(getchar() != '\n');
                } while(scanResult != 1);
        }
        result = forAll(elements, elementCount, functions[functionId]);
        printf("Wynik: %d\n", result);
        free(elements);

        return 0;
}


/* Funkcje */
int max(int a, int b) {
        return (a > b) ? a : b;
}

int min(int a, int b) {
        return (a < b) ? a : b;
}

int sum(int a, int b) {
        return a + b;
}

int forAll(int* elements, int amount, int (*f)(int, int)) {
        int v = elements[0];
        int i = 0;
        for (i = 1; i < amount; i++) {
                v = f(v, elements[i]);
        }
        return v;
}



/* Wynik:
 * s29986@szuflandia22:~/zadania/zajecia4$ ./zad_pointer
 * Podaj indeks funkcji (0 - maksimum, 1 - minimum, 2 - suma): 0
 * Podaj ilość elementów: 3
 * Podaj element 1: 2
 * Podaj element 2: a
 * Podaj element 2: 3
 * Podaj element 3: 4
 * Wynik: 4
 * s29986@szuflandia22:~/zadania/zajecia4$ ./zad_pointer
 * Podaj indeks funkcji (0 - maksimum, 1 - minimum, 2 - suma): 1
 * Podaj ilość elementów: 2
 * Podaj element 1: 6
 * Podaj element 2: -1
 * Wynik: -1
 * s29986@szuflandia22:~/zadania/zajecia4$ ./zad_pointer
 * Podaj indeks funkcji (0 - maksimum, 1 - minimum, 2 - suma): 2
 * Podaj ilość elementów: 3
 * Podaj element 1: 1
 * Podaj element 2: 2
 * Podaj element 3: 3
 * Wynik: 6
 */



/* Wniosek:
 * Program zaczyna od zdefiniowania tablicy wstaźników do funkji. Przetwarza ją
 * funkcja forAll. Na początek program pyta się o funkcję, która ma być
 * wykonana (0 - maksimum, 1 - minimum, 2 - suma) oraz ilość elementów do
 * wprowadzenia. Następnie podawane przez użytkownika elementy są wprowadzane
 * do tablicy elements. Na koniec do zmiennej result zostaje przypisany wynik
 * funkcji, która została wybrana za pomocą forAll oraz zostaje on wyświetlony.
 * Wykorzytuję instrukcje warunkowe jedynie do sprawdzania poprawności
 * wprowadzanych danych.
 *
 * To zadanie nauczyło mnie, że wskaźniki mogą również wskazywać na funkcje.
 * Moim zdaniem tablica wskaźników do funkcji jest bardziej elastyczna w
 * porównaniu do instrukcji warunkowych, poniewaz pozwala np. na łatwiejsze
 * dodawanie funkcji do kodu.
 */
