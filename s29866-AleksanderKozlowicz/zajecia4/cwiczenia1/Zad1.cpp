#include <iostream>
#include <cstdio>

int sum(int, int);

int main() {
  int a, b;
  printf("Podaj pierwsza liczbe: ");
  scanf("%d", &a);
  printf("Podaj druga liczbe: ");
  scanf("%d", &b);

  printf("Suma: %d\n", sum(a, b));
}

int sum(int a, int b){
  return a+b;
}

