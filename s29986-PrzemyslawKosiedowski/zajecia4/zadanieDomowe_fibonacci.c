/* Napisz program liczący kolejne wartości ciągu Fibonacciego w wersji:
 * rekursywnej (rekurencyjnej) i iteracyjnej
 */

#include <stdio.h>
#include <stdlib.h>

int fibRec(int number);
int fibIter(int number);

int main(int argc, char* argv[]) {
        int number = 0;
        if(argc != 2) {
                printf("Błąd - należy podać 1 argument.\n");
                return 1;
        }
        number = atoi(argv[1]);

        if(number <= 0) {
                printf("Podano zły argument.\n");
                return 1;
        }

        printf("Wynik dla %d (rekurencja): %d\n", number, fibRec(number));
        printf("Wynik dla %d (iteracja): %d\n", number, fibIter(number));

        return 0;
}

int fibRec(int number) {
        if(number == 1 || number == 2) {
                return 1;
        }
        return(fibRec(number - 1) + fibRec(number - 2));
}

int fibIter(int number) {
        int a = 0;
        int b = 1;
        int c = 0;
        int i;

        if(number == 1) {
                return 1;
        }

        for(i = 2; i <= number; i++) {
                c = a + b;
                a = b;
                b = c;
        }
        return b;
}



/* Wynik:
 * s29986@szuflandia22:~/zadania/zajecia4/zadanieDomowe$ ./zad_fib 10
 * Wynik dla 10 (rekurencja): 55
 * Wynik dla 10 (iteracja): 55
 * s29986@szuflandia22:~/zadania/zajecia4/zadanieDomowe$ ./zad_fib 20
 * Wynik dla 20 (rekurencja): 6765
 * Wynik dla 20 (iteracja): 6765
 */


/* Wniosek:
 * Obie wersje działają prawidłowo. Dodatkowo program posiada zabezpieczenia
 * przed wprowadzaniem błędnych danych.
 */
