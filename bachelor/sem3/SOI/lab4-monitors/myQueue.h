#ifndef _my_queue_h_
#define _my_queue_h_

#include "message.h"

struct Node{
    Node(Message* mess):next(nullptr), message(mess){}
    ~Node(){
        delete message;
        //delete next;
    }
    Node* next;
    Message* message;
};

class MyQueue{
public:
    MyQueue(): head(nullptr), tail(nullptr), last_important(nullptr), size(0){}
    ~MyQueue(){
        while (head){
            Node* tmp = head;
            head = head->next;
            delete tmp;
        }
    }

    void insertMessage(Message* new_mess){
        if(new_mess->getPriority() == NORMAL){
            insertNormal(new_mess);
        }else if( new_mess->getPriority() == IMPORTANT){
            insertImportant(new_mess);
        }
        ++size;
    }

    Message* pop(){
        if( head == nullptr ){
            return nullptr;
        }

        if( head == last_important){
            last_important = nullptr;
        }
        if( head == tail){
            tail = nullptr;
        }
        Node* tmp = head;
        head = head->next;
        Message* mess = tmp->message;
        tmp->message = nullptr;
        //tmp->next = nullptr;
        delete tmp;
        --size;
        return mess;
    }

    void print(){
        Node* tmp = head;
        while(tmp){
            Message* tmp_mess = tmp->message;
            std::cout<<tmp_mess->getText()<<"\t";
            tmp = tmp->next;
        }
        std::cout<<std::endl;
    }
    int getSize(){
        return size;
    }
private:
    Node* head, *tail, *last_important;
    int size;

    void insertNormal(Message* new_mess){
        Node* new_node;
        try{
            new_node = new Node(new_mess);
        }catch(std::bad_alloc&){
            std::cout<<"Bad alloc"<<std::endl;
            exit(1);
        }
        if(head == nullptr){
            head = new_node;
        }else{
            tail->next = new_node;
        }
        tail = new_node;
    }
    void insertImportant(Message* new_mess){
        Node* new_node;
        try{
            new_node = new Node(new_mess);
        }catch(std::bad_alloc&){
            std::cout<<"Bad alloc"<<std::endl;
            exit(1);
        }if(head == nullptr){
            head = new_node;
            tail = new_node;
        }else if( last_important == nullptr){
            new_node->next = head;
            head = new_node;
        }else{
            Node* tmp = last_important->next;
            last_important->next = new_node;
            new_node->next = tmp;
            if(tail == last_important){
                tail = new_node;
            }
        }
        last_important = new_node;
    }
};

#endif //_my_queue_h_