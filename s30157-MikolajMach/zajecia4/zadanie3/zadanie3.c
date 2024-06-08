#include <stdio.h>
#include <stdlib.h>

int maximum(int a, int b) {
    return (a > b) ? a : b;
}

int minimum(int a, int b) {
    return (a < b) ? a : b;
}

int sum(int a, int b) {
    return a + b;
}

int main() {
    int (*functions[3])(int, int) = {maximum, minimum, sum};

    int functionId, elementCount;
    scanf("%d %d", &functionId, &elementCount);

    int v;
    scanf("%d", &v);

    for (int i = 1; i < elementCount; ++i) {
        int x;
        scanf("%d", &x);
        v = (*functions[functionId])(v, x);
    }

    printf("%d\n", v);

    return 0;
}

