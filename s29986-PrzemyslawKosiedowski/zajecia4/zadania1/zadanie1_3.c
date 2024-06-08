/* Napisz program wyświetlający tradycyjną choinkę o zadanej wysokości.
 * Wysokość niech będzie podana jako parametr wywołania programu. Przydatne
 * hasła to: atoi, argc, argv, for
 */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
        int i = 0;
        int j = 0;
        int height = 0;

        if(argc != 2) {
                printf("Błąd - należy podać 1 argument.\n");
                return 1;
        }
        height = atoi(argv[1]);

        if(height < 1) {
                printf("Wysokość musi być liczbą dodatnią\n");
                return 1;
        }

        printf("Choinka o wysokości %d:\n", height);
        for(i = 0; i < height; i++) {
                for(j = 0; j < height - i - 1; j++) {
                        printf(" ");
                }
                for(j = 0; j < 2 * i + 1; j++) {
                        printf("*");
                }
                printf("\n");
        }

        return 0;
}

/* Wniosek:
 * Program sprawdza, czy został uruchomiony z odpowiednią liczbą argumentów,
 * jeśli tak, to konwertuje go na liczbę całkowitą (atoi z stdlib.h) i sprawdza,
 * czy ten argument jest dodatni. Jeśli jest, to przystępuje do drukowania
 * choinki dzięki pętli for. Jeśli któryś ze wcześniejszych warunków się nie
 * zgadza, to wyświetla odpowiedni komunikat i kończy działanie z kodem błędu 1.
 *
 * Dzięki temu zadaniu dowiedziałem się o istnieniu funkcji atoi oraz czym są:
 * argc - liczba argumentów przekazanych do programu
 * argv - tablica ciągów, która reprezentuje argumenty wiersza polecenia
 *        wprowadzone przez użytkownika.
 * Znalazłem to tutaj (dokumentacja C):
 * https://learn.microsoft.com/pl-pl/cpp/c-language/argument-description?view=msvc-170
 */
