#include <stdio.h>

int main() {
    int a, b;
    printf("Enter 2 numbers: ");
    scanf("%d %d", &a, &b);
    getchar(); 
    printf("Sum: %d\n", a + b);

    printf("Press any key to continue...");
    getchar();

    return a + b;
}