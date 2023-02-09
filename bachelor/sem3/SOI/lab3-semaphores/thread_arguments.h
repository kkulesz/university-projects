#include "queue.h"

#define NICK_LENGTH 20

typedef struct user_thread_arg{
    queue* main_queue;
    char nickname[NICK_LENGTH];
}user_thread_arg;

void free_user_thread_arg(user_thread_arg* arg){
    if( arg != NULL){
        free(arg);
    }
}

typedef struct chat_thread_arg{
    queue* main_queue;
}chat_thread_arg;

void free_chat_thread_arg(chat_thread_arg* arg){
    if(arg != NULL){
        free(arg);
    }
}