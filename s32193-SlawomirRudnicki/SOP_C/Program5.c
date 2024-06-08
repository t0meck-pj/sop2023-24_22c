#include<stdio.h>
#include<stdlib.h>

int sum(int,int);
int max(int,int);
int min(int,int);

typedef int (*f) (int, int);

f func[3] = {&sum, &max, &min};

int main(int argc, char **argv){
    int i;
    int sum = *argv[3] - '0';
    
    for (i = 1; i < *argv[2] -'0'; i++)
    {
        sum = func[*argv[1] -'0'](sum, (*argv[3+i] - '0'));
    }

    printf("%d \n", sum);
  
    
    return 0;
}

int sum(int a, int b){
    
    return a+b;
}
int max(int a, int b){
    if( a >= b){
        return a;
    }
    return b;
}
int min(int a, int b){
    if( a <= b){
        return a;
    }
    return b;
}
