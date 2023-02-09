#ifndef _message_h_
#define _message_h_

#include <ctime>

#define IMPORTANT 1
#define NORMAL 0

class Message{
private:
    std::string nickname;
    std::string text;
    int priority;
    struct tm time_sent;
public:
    Message(std::string nickname, std::string text, int priority):nickname(nickname), text(text), priority(priority){
        time_t t = time(NULL);
        time_sent = *localtime(&t);
    };
    ~Message(){};

    std::string getNickname(){
        return this->nickname;
    }

    std::string getText(){
        return this->text;
    }

    int getPriority(){
        return this->priority;
    }
    struct tm getTime(){
        return time_sent;
    }
};


#endif //_message_h_