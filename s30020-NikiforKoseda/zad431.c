#include <stdio.h>
#include <stdlib.h>

typedef int (*func_ptr)(int, int);

int sum(int a, int b) {
    return a + b;
}

int max(int a, int b) {
    if (a > b) {
        return a;
    } else {
        return b;
    }
}

int min(int a, int b) {
    if (a < b) {
        return a;
    } else {
        return b;
    }
}

int main() {
    int choice;
    int amount;
    int numbers[amount];
    int i;

    func_ptr funcs[3];

    funcs[0] = sum;
    funcs[1] = max;
    funcs[2] = min;

    printf("Enter a number from 0 to 2: ");
    scanf("%d", &choice);

    printf("Enter the amount of numbers: ");
    scanf("%d", &amount);

    printf("Enter %d numbers:\n", amount);
    for (i = 0; i < amount; i++) {
        scanf("%d", &numbers[i]);
    }

    for (i = 0; i < amount - 1; i++) {
        numbers[i + 1] = funcs[choice](numbers[i], numbers[i + 1]);
    }

    return 0;
}
