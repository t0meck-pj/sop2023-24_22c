#include <stdio.h>
int sum(int, int);
int main() {
	int LastScanned  = 0;
	int result  = 0;
	int q = 0
	do {
		q = 0;
		LastScanned = 0;
		printf("Podaj liczbe do dodania: ");
		q = scanf("%d", &LastScanned);
		result += LastScanned;
		q = 0;
	} while (scanf(q != 0));
	printf("Podaj pierwsza liczbe: ");
	scanf("%d", &LastScanned);
	printf("Wynik dodawania: %d\n", sum(x, y));
	return 0;
}
int sum(int a, int b) {
	return a+b;
}
