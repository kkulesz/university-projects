#include <stdio.h>      /* printf */
#include <pthread.h>    /* pthread */
#include <unistd.h>     /* sleep*/
#include <semaphore.h>  /* sem_t*/
#include <time.h>       /* time*/
#include <signal.h>     /*signal*/

#include "thread_arguments.h"

#define MAX_MESSEGES 5//how many messages can our queue contain

/*=======USERS========*/
#define NUM_OF_NORMALS 3
#define NUM_OF_VIPS 1
#define NUM_OF_ADMINS 1

/*======FREQUENCY========*/
#define NORMAL_SLEEP_TIME 1
#define VIP_SLEEP_TIME 3
#define ADMIN_SLEEP_TIME 10
#define CHAT_SLEEP_TIME 1

/*======NUM_OF_ACTIONS=====*/
#define NORMAL_MESSAGES 6//how many messages will users send
#define VIP_MESSEGES 3
#define ADMIN_CLEARS 1


#define MAX_SUFFIX_SIZE 3
const char* COMMENT_PREFIX = "\t\t\t\t";

sem_t mutex;
sem_t full;//do not save to full
sem_t empty;//do not read from empty

void addSuffix(char* nick_skelleton, int suffix_to_add);
queue* generateMessages(char* nickname, char* message_skelleton, int number_of_messeges);


void scenerio(queue* main_queue, const int NORMAL_USERS, const int VIP_USERS, const int ADMIN_USERS);
void sig_handler( int signo ){
    if(signo == SIGALRM){
        exit(0);
    }
}

void* normal_user(void* arg){
    user_thread_arg* argument = arg;
    queue* main_queue = argument->main_queue;
    char* nickname = argument->nickname;
    queue* messages = generateMessages(nickname,"nr_",NORMAL_MESSAGES);
    while( messages->head != NULL ){
        sleep(NORMAL_SLEEP_TIME);
        message* new_mess = pop( messages );
        sem_wait(&full);
        sem_wait(&mutex);
        /*========================================================*/
        printf("%s/* %s\t dodaje wiadomosc*/\n", COMMENT_PREFIX, nickname);
        insert_message(main_queue, new_mess, NORMAL_USER);
        /*========================================================*/
        sem_post(&mutex);
        sem_post(&empty);
    }
    free_queue(messages);
   return NULL;
}

void* vip_user(void* arg){
    user_thread_arg* argument = arg;
    queue* main_queue = argument->main_queue;
    char* nickname = argument->nickname;
    queue* messages = generateMessages(nickname,"nr_",VIP_MESSEGES);

    while( messages->head ){
        sleep(VIP_SLEEP_TIME);
        message* mess = pop( messages );
        sem_wait(&full);
        sem_wait(&mutex);
        /*========================================================*/
        printf("%s/* %s\t dodaje wiadomosc*/\n", COMMENT_PREFIX, nickname);
        insert_message(main_queue,mess, VIP_USER);
        /*========================================================*/
        sem_post(&mutex);
        sem_post(&empty);
    }
    free_queue(messages);
    return NULL;
}

void* admin_user(void* arg){
    user_thread_arg* argument = arg;
    queue* main_queue = argument->main_queue;
    char* nickname = argument->nickname;
    int i = 0;
    for(i = 0; i<ADMIN_CLEARS; ++i){
        sleep(ADMIN_SLEEP_TIME);
        //clear_queue(main_queue, ADMIN_USER);
        sem_wait(&mutex);
        /*========================================================*/    
        while(main_queue->head != NULL){
            sem_wait(&empty);
            message* mess = pop(main_queue);
            sem_post(&full);
            free_message(mess);
        }
        printf("%s/* %s\t czyści chat*/\n", COMMENT_PREFIX, nickname);
        /*========================================================*/ 
        sem_post(&mutex);  
    }
    return NULL;
}

void* chat_thread(void* arg){
    chat_thread_arg* argument = arg;
    queue* main_queue = argument->main_queue;
    printf("(Size)Time\tMessage\t\tUser\t\tAction\n");
    printf("==================================================================\n");
    while(1){
        sleep(CHAT_SLEEP_TIME);
        alarm(5);// leave if nothing happens for 5 sec
        sem_wait(&empty);
        sem_wait(&mutex);
        /*========================================================*/
        message* mess = pop(main_queue);
        int size = main_queue->size;
       
        if(mess != NULL) {
            time_t t = time(NULL);
            struct tm tm = *localtime(&t);
            printf("(%d)%d:%d:%d\t%s: %s\n",size, tm.tm_hour, tm.tm_min, tm.tm_sec, mess->sender_nickname, mess->text);
            free(mess);
        }
        /*========================================================*/
        sem_post(&mutex);
        sem_post(&full);
        
    }
    return NULL;
}

int main(int argc, char** argv){
    signal(SIGALRM, *sig_handler);//sets return code to 0 if alarm is executed
    sem_init(&mutex,0,1);
    sem_init(&full,0,MAX_MESSEGES);
    sem_init(&empty,0,0);

    queue* main_queue = init_queue();

    int i=0;
    if(argc>1){
        i = atoi(argv[1]);
    }
    if(i == 1){//EMPTY BUFFER
        printf("EMPTY BUFFER TEST\n");
        scenerio(main_queue,0,0,0);
    }else if(i==2){//FULL BUFFER
        printf("FULL BUFFER TEST\n");
        scenerio(main_queue ,3,0,0);
    }else if(i==3){//VIP FIRST
        printf("VIP FIRST TEST\n");
        scenerio(main_queue ,2,1,0);
    }else if(i==4){//ADMIN CLEARS CHAT
        printf("ADMIN CLEARS CHAT TEST\n");
        scenerio(main_queue ,3,0,1);
    }else{
        printf("Default\n");
        scenerio( main_queue, NUM_OF_NORMALS, NUM_OF_VIPS, NUM_OF_ADMINS);
    }
        
    sem_destroy(&mutex);
    sem_destroy(&full);
    sem_destroy(&empty);
    return 0;
}


void addSuffix(char* text_skelleton, int suffix_to_add){
    char suffix[MAX_SUFFIX_SIZE];
    suffix[0]='\0';
    sprintf(suffix,"%d",suffix_to_add);
    strcat(text_skelleton, suffix);
}


queue* generateMessages(char* nickname, char* message_skelleton, int number_of_messeges){
    queue* new_queue = init_queue();
    char text[MESSAGE_LENGTH];
    for(int i = 0; i<number_of_messeges;++i){
        strcpy(text, message_skelleton);
        addSuffix(text, i+1);

        message* new_message = init_message(nickname, text);
        insert_message(new_queue, new_message, NORMAL_USER);
    }
    return new_queue;
}

void scenerio(queue* main_queue,const int NORMAL_USERS, const int VIP_USERS, const int ADMIN_USERS){
    //queue* main_queue = init_queue();

    user_thread_arg normal_args[NORMAL_USERS];
    user_thread_arg vip_args[VIP_USERS];
    user_thread_arg admin_args[ADMIN_USERS];
    pthread_t normals[NORMAL_USERS];
    pthread_t vips[VIP_USERS];
    pthread_t admins[ADMIN_USERS];

    chat_thread_arg chat_argument;;
    pthread_t chat;


    chat_argument.main_queue = main_queue;
    pthread_create(&chat, NULL, chat_thread, &chat_argument);

    /*================NORMALS==============*/
    for(int i = 0; i <NORMAL_USERS; ++i){
        normal_args[i].main_queue = main_queue;
        strcpy(normal_args[i].nickname,"Normal_");
        addSuffix(normal_args[i].nickname, i+1);
        pthread_create(&normals[i], NULL, normal_user, &normal_args[i]);
    }
    /*===============VIPS=================*/
    for(int i = 0; i<VIP_USERS; ++i){
        vip_args[i].main_queue = main_queue;
        strcpy(vip_args[i].nickname,"VIP_");
        addSuffix(vip_args[i].nickname, i+1);
        pthread_create(&vips[i], NULL, vip_user, &vip_args[i]);
    }
    /*==============ADMINS===================*/
    for(int i = 0; i<ADMIN_USERS; ++i){
        admin_args[i].main_queue = main_queue;
        strcpy(admin_args[i].nickname,"Admin_");
        addSuffix(admin_args[i].nickname, i+1);
        pthread_create(&admins[i], NULL, admin_user, &admin_args[i]);
    }



    /*==================JOINING=====================*/
    for(int i=0; i<NORMAL_USERS; ++i){
        pthread_join(normals[i], NULL);
    }
    for(int i=0; i<VIP_USERS; ++i){
        pthread_join(vips[i], NULL);
    }
    for(int i=0; i<ADMIN_USERS; ++i){
        pthread_join(admins[i], NULL);
    }
    pthread_join(chat, NULL);

    free_queue(main_queue);
}
