#include <stdio.h>
int sum(int, int);

int main () {
    int x = 0;
    int y = 0;
    printf("Podaj liczby x oraz y: ");
    scanf("%d", &x);
    scanf("%d", &y);
    printf("%d \n", sum(x,y));
    return sum(x,y);
}

int sum(int a, int b){
    return a+b;
}
