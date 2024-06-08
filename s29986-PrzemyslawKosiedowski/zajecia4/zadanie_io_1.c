/* Napisz program wczytujący z pliku tekstowego ciąg liczb. Format pliku jest
 * taki:
 *      liczba elementów ciągu (jako liczba naturalna)
 *      Kolejne liczby - każda w nowej linii
 * Przykład:
 * 3
 * 5
 * 1
 * 9
 * Opis przykładu: 3 - liczby do wczytania, liczby -  5, 1, 9
 * Niech program wypisze je w odwrotnej kolejności. Program powinien przyjmować
 * zero albo jeden argument:
 *      jeśli nie podano argumentu, to ma wczytywać ze standardowego wejścia;
 *      jeśli podano argument, to jest to nazwa pliku do wczytania;
 * Skorzystaj z: fopen, fclose, fscanf. Zabezpiecz przed przepełnieniem bufora.
 * Skorzystaj z funkcji do dynamicznej rezerwacji/alokacji pamięci:
 * malloc lub calloc, free.
 */

#include <stdio.h>
#include <stdlib.h>

void read(int* numbers, int amount, FILE* file);
void print(int* numbers, int amount);

int main(int argc, char* argv[]) {
        FILE* file;
        int amount;
        int* numbers;

        if(argc == 1) {
                file = stdin;
        } else if(argc == 2) {
                file = fopen(argv[1], "r");
                if(file == NULL) {
                        printf("Plik o podanej nazwie nie istnieje.\n");
                        return 1;
                }
        } else {
                printf("Podano niewłaściwą ilość argumentów.\n");
                return 1;
        }

        fscanf(file, "%d", &amount);

        if(amount < 1) {
                printf("Liczba elementów do wypisania musi być dodatnia.\n");
                return 1;
        }

        numbers = (int*)calloc(amount, sizeof(int));
        if(numbers == NULL) {
                printf("Błąd podczas przydzielania pamięci.\n");
                return 1;
        }

        read(numbers, amount, file);

        if(file != stdin) {
                fclose(file);
        }
        print(numbers, amount);

        free(numbers);

        return 0;
}


void read(int* numbers, int amount, FILE* file) {
        int i = 0;
        for(i = 0; i < amount; i++) {
                fscanf(file, "%d", &numbers[i]);
        }
}

void print(int* numbers, int amount) {
        int i = 0;
        for(i = amount - 1; i >= 0; i--) {
                printf("%d\n", numbers[i]);
        }
}



/* Wynik:
 * s29986@szuflandia22:~/zadania/zajecia4$ ./zad_io_1
 * 4 1 2 8 3
 * 3
 * 8
 * 2
 * 1
 * s29986@szuflandia22:~/zadania/zajecia4$ vim test.txt
 * s29986@szuflandia22:~/zadania/zajecia4$ ./zad_io_1 test.txt
 * 2
 * 12
 * 9
 * 3
 * s29986@szuflandia22:~/zadania/zajecia4$ cat test.txt
 * 4
 * 3
 * 9
 * 12
 * 2
 * s29986@szuflandia22:~/zadania/zajecia4$ ./zad_io_1 a a tekts.txt
 * Podano niewłaściwą ilość argumentów
 */



/* Wniosek:
 * Ten program wczytuje dane ze sdtin bądź pliku, gdzie:
 * pierwsza liczba określa ilość elementów, a reszta jest wypisywana przez
 * program w odwrotnej kolejności. Posiada on również zabezpieczenie przed
 * przepełnieneiem bufora, ponieważ rozmiar tablicy, do której są wczytywane
 * dane, jest określany na podstawie liczby elementow do wczytania.
 * Do odczytywania i wypisywania elementów wykorzystuję printf i fscanf,
 * iterując po elementach pętlą for. Działania te zapisałem w odpowiednich
 * funkcjach. Nie są one potrzebne, ale użyłem ich,ponieważ chciałem wypróbować
 * budowanie ich w C.
 * Dowiedziałem się dzięki temu zadaniu jak działać na plikach i alokować
 * pamięć w C.
 */
