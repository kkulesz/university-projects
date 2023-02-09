#include <stdio.h> /* FILE*/
#include <string.h> /* strcmp etc*/

#define BUFFER_SIZE 10*1024

int main( int argc, char** argv){
    FILE *first, *second;
    char first_buffer[BUFFER_SIZE];
    char second_buffer[BUFFER_SIZE];
    if( argc < 3){
        return -1;
    }
    first = fopen(argv[1], "r");
    if( first == NULL ){
        printf("First file does not exist\n");
        return -1;
    }
    second = fopen( argv[2], "r");
    if( second == NULL ){
        printf("Second file does not exist\n");
        return -1;
    }

    if( fread(&first_buffer, sizeof(char), BUFFER_SIZE, first) < 0 ){
        return -1;
    }
    if( fread(&second_buffer, sizeof(char), BUFFER_SIZE, second) < 0){
        return -1;
    }

    if( strcmp(first_buffer, second_buffer) != 0){
        return -1;
    }



    

    return 0;
}