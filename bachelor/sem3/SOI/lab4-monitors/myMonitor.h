#ifndef _my_monitor_h_
#define _my_monitor_h_

#include "monitor.h"
#include "myQueue.h"

#define MIN_MESSAGE_LENGTH 8
#define MAX_MESSAGE_LENGTH 64

void printHint(std::string nickname){
	std::cout<<"\t\t\t\t\t\t"<<nickname<<" dodaje wiadomosc\n";
}

class MyMonitor : public Monitor{
private:
	int max_buffer_size;
	int actual_size;
    Condition full,empty;
	MyQueue* queue;
public:
    MyMonitor(const int size) :max_buffer_size(size), actual_size(0) {
		try{
			queue = new MyQueue();
		}catch(std::bad_alloc&){
			std::cout<<"Bad alloc"<<std::endl;
			exit(1);
		}
	}
	~MyMonitor(){
		delete queue;
	}


	void insertMessage(Message* new_mess){
		if( new_mess->getText().size()<MIN_MESSAGE_LENGTH || new_mess->getText().size()>MAX_MESSAGE_LENGTH ){
			delete new_mess;
			return;
		}
		enter();
		if(actual_size == max_buffer_size){
			wait(full);
		}
		queue->insertMessage(new_mess);
		//printHint( new_mess->getNickname() );
		++actual_size;
		if(actual_size == 1){
			signal(empty);
		}
		leave();
	}
	Message* takeMessage(){
		Message* tmp;
		enter();
		if( actual_size==0 ){
			wait(empty);
		}
		--actual_size;
		tmp = queue->pop();
		if(actual_size == max_buffer_size-1){
			signal(full);
		}
		leave();
		return tmp;
	}

	void printQueue(){
		enter();
		queue->print();
		leave();
	}
};

#endif //_my_monitor_h_