#include <stdio.h>
#include <stdbool.h>
int main() {
        int sum = 0, a, n, i;
        printf("Ile liczb chcesz podac? ");
        scanf("%d", &n);
        for(i = 0; i < n; i++){
                printf("Podaj liczbe do dodania: ");
                scanf("%d", &a);
                sum += a;
        }
        return sum;
}
