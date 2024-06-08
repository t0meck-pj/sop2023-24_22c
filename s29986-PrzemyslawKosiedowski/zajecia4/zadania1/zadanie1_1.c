/* Napisz program obliczający sumę liczb wprowadzonych przez użytkownika (ze
 * standardowego wejścia) i wypisujący wynik na standardowe wyjście. Przydatne
 * hasła to: scanf, printf, operatory arytmetyczne, if, for albo while
 */

#include <stdio.h>

int main() {
        int x = 0;
        int sum = 0;
        int condition = 0;

        printf("Program zakończy się, gdy wprowadzona wartość nie będzie liczbą.\n");
        do {
                condition = 0;
                x = 0;
                printf("Podaj liczbę: ");
                condition = scanf("%d", &x);
                sum += x;
        } while (condition != 0);

        printf("Wynik: %d\n", sum);

        return 0;
}

/* Wniosek:
 * Program pobiera od użytkownika liczby i sumuje je, na koniec wypisuje wynik.
 * Wykorzystuje do tego scanf(), który zwraca 1, dopóki wprowadzana wartość
 * jest liczbą.
 * Dzięki temu zadaniu dowiedziałem się jak wykorzystywać wartości, które
 * zwracają funkcje oraz jak kompilować kod.
 */
