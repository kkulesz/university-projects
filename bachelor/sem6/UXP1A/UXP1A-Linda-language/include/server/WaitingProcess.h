#ifndef UXP1A_LINDA_WAITINGPROCESS_H
#define UXP1A_LINDA_WAITINGPROCESS_H

#include <unistd.h>
#include "../tuple/Tuple.h"
#include "../tuple/TuplePattern.h"

class WaitingProcessInfo {
public:
    WaitingProcessInfo(pid_t pid, int readPipeDescriptor, int writePipeDescriptor, const TuplePattern &pattern, bool isInput)
        : pid(pid), readPipeDescriptor(readPipeDescriptor), writePipeDescriptor(writePipeDescriptor), pattern(pattern), isInput_(isInput) {}

public:
    pid_t getPid() const {
        return pid;
    }
    void setPid(pid_t p) {
        WaitingProcessInfo::pid = p;
    }
    int getReadPipeDescriptor() const {
        return readPipeDescriptor;
    }
    void setReadPipeDescriptor(int pipeDescriptor) {
        WaitingProcessInfo::readPipeDescriptor = pipeDescriptor;
    }
    int getWritePipeDescriptor() const {
        return writePipeDescriptor;
    }
    void setWritePipeDescriptor(int pipeDescriptor) {
        WaitingProcessInfo::writePipeDescriptor = pipeDescriptor;
    }
    const TuplePattern &getPattern() const {
        return pattern;
    }
    void setPattern(const TuplePattern &p) {
        WaitingProcessInfo::pattern = p;
    }
    bool isInput() const {
        return isInput_;
    }
    void setIsInput(bool isInput) {
        WaitingProcessInfo::isInput_ = isInput;
    }

private:
    pid_t pid;
    int readPipeDescriptor;
    int writePipeDescriptor;
    TuplePattern pattern;
    bool isInput_;

};

class WaitingProcess{
public:
    WaitingProcess(int readPipe, int writePipe, int socket) : readPipeDescriptor(readPipe), writePipeDescriptor(writePipe), clientSocket(socket){}
    void run();

private:
    int readPipeDescriptor;
    int writePipeDescriptor;
    int clientSocket;
    char buffer[512];
    const char* RESPONSE_OK = "OK";
    const char* RESPONSE_FAIL = "FAIL";
};

#endif//UXP1A_LINDA_WAITINGPROCESS_H
