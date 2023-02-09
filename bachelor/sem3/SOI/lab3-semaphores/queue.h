#include "message.h"

#define NORMAL_USER 0
#define VIP_USER 1
#define ADMIN_USER 2

typedef struct node{
    message* message;
    struct node* next;
}node;

node* init_node(message* mess){
    node* new_node = malloc( sizeof(node) );
    if(new_node == NULL){
        exit(1);
    }
    new_node->message = mess;
    new_node->next = NULL;
    return new_node;
}

void free_node(node* node){
    free_message(node->message);
    if(node != NULL){
        free(node);
    }
}

typedef struct queue{
    int size;
    node* head;
    node* tail;
}queue;

queue* init_queue(){
    queue* fifo = malloc( sizeof(queue) );
    if( fifo == NULL ){
        exit(1);
    }
    fifo->size = 0;
    fifo->head = NULL;
    fifo->tail = NULL;
    
    return fifo;
}

void free_queue(queue* queue){
    if(queue == NULL)
        return;
    while( queue->head != NULL ){
        node* tmp = queue->head;
        queue->head = queue->head->next;

        free_node(tmp);
        --(queue->size);
    }
    free(queue);
}

void insert_normal(queue* fifo, message* message){
    node* new_node = init_node(message);
    if(fifo->head == NULL){
        fifo->head = new_node;
    }else{
        fifo->tail->next = new_node;
    }
    fifo->tail = new_node;
}
void insert_vip(queue* lifo, message* message){
    node* new_node = init_node(message);
    if(lifo->tail == NULL){
        lifo->tail = new_node;
    }
    new_node->next = lifo->head;
    lifo->head = new_node;
}

void insert_message(queue* queue, message* message, int user_flag){
    if( user_flag == NORMAL_USER){
        insert_normal(queue,message);
    }else if( user_flag==VIP_USER || user_flag==ADMIN_USER ){
        insert_vip(queue,message);
    }else{
        exit(1);
    }
    ++(queue->size);
}

message* pop(queue* fifo){
    if(fifo->head == NULL){
        return NULL;
    }

    message* mess = fifo->head->message;
    node* tmp = fifo->head;
    if(fifo->head == fifo->tail){
        fifo->tail = fifo->head->next;
    }
    fifo->head = fifo->head->next;
    free(tmp);
    --(fifo->size);
    return mess;
}


//niepotrzebne
void clear_queue(queue* fifo, int user_flag){
    if( user_flag!=ADMIN_USER ){
        return;
    }
    free_queue(fifo);
}