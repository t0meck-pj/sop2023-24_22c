#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void hex_printer(char*);

int main (int argc, char **argv){

    hex_printer(argv[1]);

    return 0;
}

void hex_printer(char *file_name){

    int i;
    int k;
    int iterator = 0;
    int character = 0;
    int line_counter = 0;
    int character_counter=0;
    int *character_array = malloc(1000*sizeof(int));
    FILE *file;
    file = fopen(file_name, "rb");


    /*while((character = fgetc(file))!=EOF){
        printf(" %02X ", character);
        line_counter++;
        if(line_counter % 16==0){
            printf("\n");
        }
    }
    printf("\n");
    */
    while((character = fgetc(file))!= EOF){
        character_array[character_counter] = character;
        character_counter++;
    }
    character_array = realloc(character_array, character_counter*sizeof(int));

    for ( i = 0; i < character_counter; i++)
    {
        printf(" %02X ", character_array[i]);
        line_counter++;
        if ( line_counter % 16 == 0){
            for (k = 0; k < 16; k++)
            {
                if(character_array[iterator] != 10){
                printf("%c",character_array[iterator]);
                }
                else{
                    printf(".");
                }
                iterator++;
                
            }
            printf("\n");
        }
    }
    
    
}
