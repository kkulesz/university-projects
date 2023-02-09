#include <iostream>
#include <thread>
#include <unistd.h>     //sleep

#include "myMonitor.h"
#include "message.h"

#define MAX_NUM_OF_MESSEGES 5

#define NORMAL_TEXTERS_NUMBER 3
#define IMPORTANT_TEXTER_NUMBER 1 

#define TEXTER_SLEEP_TIME 1
#define READER_SLEEP_TIME 1

Message* generateMessage(std::string nickname, int priority, std::string text , int suffix);
void scenerio(const bool CHAT_AVAILABLE,const int NORMAL_TEXTERS, const int IMPORTANT_TEXTERS);

MyMonitor monitor(MAX_NUM_OF_MESSEGES);

void* texter(std::string nickname, int priority, std::string text){
    int i = 1;
    while( true ){
        Message* new_mess = generateMessage(nickname, priority, text, i);
        monitor.insertMessage(new_mess);
        sleep(TEXTER_SLEEP_TIME);
        ++i;
    }
    
    return nullptr;
}

void *reader(){
    std::cout<<"    Sent\t\t\t\t\tDisplayed\n";
    while( true ){
        sleep(READER_SLEEP_TIME);
        Message* mess = monitor.takeMessage();
        struct tm time_sent = mess->getTime();
        time_t t = time(NULL);
        struct tm time_displayed = *localtime(&t);
                                                        /*(0) 21:37:00 Nickname: treść wiadomości*/
        std::cout<<"("<<mess->getPriority()<<") "<<time_sent.tm_hour<<":"<<time_sent.tm_min<<":"<<time_sent.tm_sec
                    <<"\t"<<mess->getNickname()<<":\t"<<mess->getText()<<"\t"
                    <<time_displayed.tm_hour<<":"<<time_displayed.tm_min<<":"<<time_displayed.tm_sec<<std::endl;
        delete mess;
    }

    
    return nullptr;
}


int main(int argc, char** argv){
    
    if(argc>1){
        int option = atoi(argv[1]);
        if( option == 0){
            std::cout<<"EMPTY BUFFER"<<std::endl;
            scenerio(true,0,0);
        }else if( option == 1){
            std::cout<<"FULL BUFFER"<<std::endl;
            scenerio(false,1,0);
        }else if( option == 2){
            std::cout<<"JUST NORMAL MESSAGES"<<std::endl;
            scenerio(true,2,0);
        }else if( option == 3){
            std::cout<<"JUST IMPORTANT MESSAGES"<<std::endl;
            scenerio(true,0,2);
        }else if( option == 4){
            std::cout<<"CHECKING IF IMPORATNT MESSAGES ARE BEFOR NORMAL"<<std::endl;
            scenerio(true,1,1);
        }
        
    }else{
        scenerio(true,NORMAL_TEXTERS_NUMBER,IMPORTANT_TEXTER_NUMBER);
    }
    //delete monitor;
    return 0;
}


Message* generateMessage(std::string nickname, int priority, std::string text , int suffix){
    text += std::to_string(suffix);
    Message* new_mess;
    try{
        new_mess = new Message(nickname, text, priority);
    }catch(std::bad_alloc&){
        std::cout<<"Bad alloc"<<std::endl;
        exit(1);
    }
    return new_mess;
}


void scenerio(const bool CHAT_AVAILABLE,const int NORMAL_TEXTERS, const int IMPORTANT_TEXTERS){

    std::thread normalTexterThread[NORMAL_TEXTERS];
    std::thread importantTexterThread[IMPORTANT_TEXTERS];

    /*INITIALIZATION*/
    for(int i=0; i<NORMAL_TEXTERS; ++i){
        normalTexterThread[i] = std::thread(texter, "NormalUser"+std::to_string(i+1), NORMAL, "Wiadomosc nr");
    }
    for(int i=0; i<IMPORTANT_TEXTERS; ++i){
        importantTexterThread[i] = std::thread(texter, "Important"+std::to_string(i+1), IMPORTANT, "Wazna wiad nr");
    }

    if(CHAT_AVAILABLE==true){
        std::thread readerThread(reader);
        readerThread.join();
    }

    /*JOINING*/
    for(int i=0; i<NORMAL_TEXTERS; ++i){
        normalTexterThread[i].join();
    }
    for(int i=0; i<IMPORTANT_TEXTERS; ++i){
        importantTexterThread[i].join();
    }
}