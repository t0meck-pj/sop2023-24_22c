/* Przerób ten program tak, aby wartość była zwracana jako kod zakończenia
 * programu. Wyświetl tą wartość z linii komend. Przydatne komendy: return
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

        return sum;
}

/* Wniosek:
 * Zmieniłem sposób wypisywania wyniku, tj. zamiast printf używam return. Wynik
 * można sprawdzić poleceniem echo $?. Tak jak w przypadku zadania z ciągiem
 * Fibonacciego w Bashu, warto pamiętać, że return zwraca wartości od 0 do 255,
 * więc ten sposób wypisywania działa tylko w przypadku mniejszych sum.
 */
