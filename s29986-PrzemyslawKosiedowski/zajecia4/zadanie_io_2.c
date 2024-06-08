/* Napisz program, który będzie pozwalał na wyświetlenie dowolnego pliku w
 * postaci takiej, jak w heksedytorach. Program powinien wypisać zawartość
 * pliku w postaci liczb szesnastkowych będących wartościami kolejnych bajtów
 * tego pliku. Warto zrobić tak, aby kolejne wartości były pogrupowane po 16,
 * 8 albo po 4 w celu poprawy czytelności. Pamiętaj!
 *      Nie wszystkie bajty da się wydrukować
 *      Niektóre są znakami specjalnymi
 *
 * Wynik powinien wyglądać tak:
 * ./hexviewer inputData
 * Loading file: inputData
 * 00000010  EC 8F 11 EE 07 93 ED DF C2 C3 D3 83 DE 72 A3 7A ▒.▒.▒▒▒▒▒Ӄ▒r▒z
 * 00000020  6F 34 C9 62 A7 BF BC F8 F9 E4 BD 3F 2E 9B D2 AF o4▒b▒▒▒▒▒▒?.▒ү
 * 00000030  E5 0F 1C B4 36 6B 95 70 98 7C 54 55 38 F1 88 56 ▒..▒6k▒p▒|TU8▒V
 * 00000040  B7 B9 7D 51 AE 43 9F C1 01 B5 C0 F5 DC F1 3F F6 ▒▒}Q▒C▒▒.▒▒▒▒▒?▒
 * 00000050  2D 7A CE 24 06 A3 98 F5 6B FA C9 02 19 FD 14 7E -z▒$.▒▒▒k▒▒..▒.~
 * 00000060  5E 9F 1D 1F 25 9B 29 65 A9 7C 18 EA 7F C7 F6 0A ^▒..%▒)e▒|.▒▒.
 * 00000070  FC 89 19 F2 73 4A B5 ED AC 0C 3E 3E 96 71 01 B4 ▒.▒sJ▒▒.>>▒q.▒
 * 00000080  98 33 07 20 72 C5 AF 29 63 F6 D2 77 AE 6E 31 64 ▒3. rů)c▒▒w▒n1d
 * 00000090  33 CE B2 3E 24 7D BE 97 6E FE E4 08 B4 6B 98 FA 3β>$}▒▒n▒▒.▒k▒▒
 * 000000A0  6D 72 BD 05 DD DC 28 EA 36 86 70 E9 7B 3F EF D3 mr▒.▒▒(▒6▒p▒{?▒▒
 * 000000B0  F6 D4 B7 1F 5F BE 58 C4 5A 1C 3B DD CD 31 04 34 ▒Է._▒X▒Z.;▒▒1.4
 * 000000C0  4A 65 2A 81 47 DE 89 06 A0 C3 16 7F D0 F1 E0 DA Je*▒Gމ.▒▒▒▒▒▒
 * 000000D0  0A 80 E1 CD ED 9D 18 CB 2B 19 2C 57 CB E4 96 15 .▒▒▒▒.▒+.,W▒▒.
 * 000000E0  A8 D8 CC 8A BE CC 5A A0 01 41 CC F2 06 46 12 50 ▒▒̊▒▒Z▒.A▒▒.F.P
 * 000000F0  B0 13 B6 D7 DB DB A9 A6 00 C0 14 4F 14 A8 C1 E0 ▒.▒▒▒۩▒.▒.O.▒▒▒
 * 00000100  A5 0B EF 56 C8 8E EE DF 86 A8 0C 01 72 59 A2 B3 ▒.▒VȎ▒߆▒..rY▒▒
 * 00000110  FF 30 F1 96 36 B5 76 46 9C 6F 67 B0 93 9F 2A 8B ▒0▒6▒vF▒og▒▒▒*▒
 * 00000120  02 94 19 6D 1D 50 8D 7B 30 5F F6 F4 7E 72 0B 5E .▒.m.P▒{0_▒▒~r.^
 * 00000130  E0 9E 6F E8 45 09 38 FE CB 6A E1 22 19 70 09 A2 ▒o▒E.8▒▒j▒".p.▒
 * 00000140  0B D7 89 9E 0B B9 06 A4 6A 63 B7 1B 7E 4A 24 7C .׉▒.▒.▒jc▒.~J$|
 * 00000150  59 AB E3 A8 BE BA 24 BE 12 A8 E0 53 29 C9 BC F2 Y▒㨾▒$▒.▒▒S)ɼ▒
 * 00000160  5B 87 BE 8F 3C B2 36 08 45 B8 3F 5B 65 83 31 63 [▒▒▒<▒6.E▒?[e▒1c
 * 00000170  7C 54 99 C9 F8 81 0A 15 2A 30 8A AD EA F2 E7 C6 |T▒▒▒..*0▒▒▒▒▒▒
 * 00000180  53 7B AC 41 B9 0C 7E 97 95 1F 76 8C 75 9E A3 1E S{▒A▒.~▒▒.v▒u▒▒.
 * 00000190  69 F8 51 8D 9B F0 44 36 06 A1 05 54 F5 38 25 06 i▒Q▒▒▒D6.▒.T▒8%.
 * 000001A0  E1 74 3E 62 19 BD E1 9B AA 0F 78 7E 21 64 F5 92 ▒t>b.▒ᛪ.x~!d▒
 * 000001B0  B6 99 6F 0C 53 DD AC B1 34 73 22 F4 38 92 1F F5 ▒▒o.Sݬ▒4s"▒8▒.▒
 * 000001C0  D3 0D 22 48 D0 D1 F0 22 14 C2 89 F0 87 F3 48 48 ▒."H▒▒▒".�▒▒HH
 * 000001D0  60 3D D6 25 5D 0F 29 47 38 CD E7 BE 8C A7 55 8B `=▒%].)G8▒羌▒U▒
 * 000001E0  BA 49 86 03 1F 60 A7 31 48 0C 5A 68 03 90 BF 29 ▒I▒..`▒1H.Zh.▒▒)
 * 000001F0  C2 5E 07 5F 31 B9 1E 8D 82 BF B0 84 BF 26 B1 A0 ▒^._1▒.▒▒▒▒▒▒&▒▒
 * 00000200  E7 3F BB 10 8D A3 B4 73 FC C5 40 4C D1 1C 3A 59 ▒?▒.▒▒▒s▒▒@L▒.:Y
 * Closing file: inputData
 *
 * Opis poszczególnych pól w wierszu:
 * adres_w_pliku  kolejne_N_bajtów_w_formie_hexadecymalnej  konkretne_bajty_wydrukowane_jako_tekst
 */

#include <stdio.h>
#include <ctype.h>

int main(int argc, char* argv[]) {
        FILE* file;
        char buffer[16];
        int offset = 0;
        size_t bytes;
        size_t i = 0;

        if (argc != 2) {
                printf("Błąd podczas przekazywania argumentów.\n");
                return 1;
        }

        file = fopen(argv[1], "rb");
        if (!file) {
                printf("Nie mozna otworzyc pliku.\n");
                return 1;
        }

        printf("Loading file: %s\n", argv[1]);

        while ((bytes = fread(buffer, 1, sizeof(buffer), file)) > 0) {
                printf("%08x  ", offset);

                for (i = 0; i < bytes; i++) {
                        printf("%02X ", buffer[i]);
                }

                for (i = bytes; i < 16; i++) {
                        printf("   ");
                }

                printf(" ");
                for (i = 0; i < bytes; i++) {
                        printf("%c", isprint(buffer[i]) ? buffer[i] : '.');
                }

                printf("\n");
                offset += 16;
        }

        printf("Closing file: %s\n", argv[1]);
        fclose(file);

        return 0;
}



/* Wynik:
 * s29986@szuflandia22:~/zadania/zajecia4$ ./zad_io_2 compile
 * Loading file: compile
 * 00000000  23 21 2F 62 69 6E 2F 62 61 73 68 0A 66 6F 72 20  #!/bin/bash.for
 * 00000010  66 69 6C 65 20 69 6E 20 2A 2E 63 3B 20 64 6F 0A  file in *.c; do.
 * 00000020  09 69 66 20 5B 5B 20 2D 66 20 22 24 66 69 6C 65  .if [[ -f "$file
 * 00000030  22 20 5D 5D 3B 20 74 68 65 6E 0A 09 09 67 63 63  " ]]; then...gcc
 * 00000040  20 2D 57 61 6C 6C 20 2D 2D 61 6E 73 69 20 2D 2D   -Wall --ansi --
 * 00000050  70 65 64 61 6E 74 69 63 20 2D 6F 20 22 24 7B 66  pedantic -o "${f
 * 00000060  69 6C 65 25 2E 63 7D 22 20 22 24 66 69 6C 65 22  ile%.c}" "$file"
 * 00000070  0A 09 66 69 0A 64 6F 6E 65 0A 0A                 ..fi.done..
 * Closing file: compile
 */


/* Wniosek:
 * Program otwiera plik w trybie binarnym. Następnie w każdej iteracji pętli
 * while odczytuje z niego dane blokami po 16 bajtów za pomocą fread i
 * wyświetla je na ekranie dwa razy: raz jako liczby szesnastkowe, a drugi raz
 * jako znaki ASCII. Jeśli znak nie jest drukowalny, program wyświetla zamiast
 * niego kropkę. Do sprawdzania, czy bajt jest drukowalny używam funkcji isprint
 * z biblioteki ctype.h. Pętla działa, dopóki fread zwraca liczbę wczytanych
 * bajtów większą od 0. Na sam koniec program zamyka plik.
 *
 * Działanie programu sprawdzam na zmodyfikowanym pliku z ćwiczenia 2.4 z 3
 * zjazdu (wygodniejsza kompilacja). Dzięki temu zadaniu nauczyłem się m.in.
 * jak otworzyć plik do odczytu w trybie binarnym i wyświetlać dane w formacie
 * szesnastkowym.
 */
