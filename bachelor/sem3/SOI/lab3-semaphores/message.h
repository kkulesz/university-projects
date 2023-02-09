#include <stdlib.h>
#include <string.h> /*strcat() strcpy()*/

#define MESSAGE_LENGTH 101

typedef struct message{
    char* sender_nickname;
    char text[MESSAGE_LENGTH];
}message;

message* init_message(char* nickname, char* text){
    message* new_mess = malloc( sizeof(message) );
    if( new_mess == NULL ){
        exit(1);
    }
    new_mess->sender_nickname = nickname;
    strcpy(new_mess->text, text);
    return new_mess;
}

void free_message(message* mess){
    //free(mess->text);
    if( mess != NULL ){
        free(mess);
    }
}