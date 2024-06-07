#include<stdio.h>
#include<stdlib.h>
void fileReader(char*);

int main(int argc, char **argv){
    
    if(argv[1] != NULL){
        fileReader(argv[1]);
    }
    else{
        char file_to_read[30];
        scanf("%s", file_to_read);
        fileReader(file_to_read);
    }
    
    return 0;
}

void fileReader(char *file_to_read){
    FILE *file;
    
    int str1;
    int str2;
    int i;
    int loops = 0;
    int *full_array = malloc(100*sizeof(int));
    
    file = fopen(file_to_read,"r");
    
    fscanf(file,"%d", &str1);
    
    printf("\n Number of read numbers: %d \n", str1); 
    
    loops = str1;

    for (i = 0; i < loops; i++){
        fscanf(file,"%d", &str2);
        printf("\n %d \n", str2); 
        full_array[i] = str2;
    }
    full_array = realloc(full_array, str1*sizeof(int));

    for ( i = str1-1; i >= 0; i--)
    {
        printf("\n %d \n", full_array[i]);
    }
    


    fclose(file);


    
}