#include <stdio.h>

void draw(int);

int main (int argc, char **argv) {

    char character = *argv[1];
    int lines = character - '0';
    
    draw(lines);


    return 0;
}


void draw (int line_number){
    int line;
    int element;
    for(line = 1; line <= line_number; line++ ){
        for (element = 1; element <= line; element++){
            printf("X");
        }
        printf("\n");
    }        
}
