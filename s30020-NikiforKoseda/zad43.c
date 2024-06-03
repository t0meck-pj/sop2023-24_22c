#include <stdio.h>

void fibonacci_linear(int n) {
    int t1 = 0, t2 = 1, nextTerm;

    for (int i = 1; i <= n; ++i) {
        nextTerm = t1 + t2;
        t1 = t2;
        t2 = nextTerm;
    }
    printf("%d", t1);
}

int fibonacci_recursive(int n) {
    if (n == 0) {
        return 0;
    } else if (n == 1) {
        return 1;
    } else {
        return fibonacci_recursive(n-1) + fibonacci_recursive(n-2);
    }
}

int main() {
    int n = 10; 
    fibonacci_linear(n);
    printf("\n");
    printf("%d", fibonacci_recursive(n));
    return 0;
}