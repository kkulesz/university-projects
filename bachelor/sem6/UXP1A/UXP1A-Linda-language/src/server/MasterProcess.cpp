#include "../../include/server/MasterProcess.h"
#include <sys/wait.h>

[[noreturn]] void MasterProcess::run() {
    init();
    int i = 1;
    while (true) {
        try {
            acceptClient();
            receive();
            std::cout<<i <<": ";
            processMessage();
            ++i;
        }catch (std::exception& e){
            std::cout<<"Exception: "<<e.what()<<std::endl;
        }
    }
}

void MasterProcess::init() {
    printf("initializing MasterProcess...\n");
    if ((socketFileDescriptor = socket(AF_UNIX, SOCK_STREAM, 0)) < 0) {
        perror("socket failed");
    }

    unlink(serverFilename.c_str());
    currentReturnCode = bind(socketFileDescriptor, (struct sockaddr *) &serverAddr, serverAddressLength);
    if (currentReturnCode == -1) {
        printf("BIND ERROR: %s\n", strerror(errno));
        close(socketFileDescriptor);
        exit(1);
    }

    currentReturnCode = listen(socketFileDescriptor, QUEUE_LENGTH);
    if (currentReturnCode == -1) {
        printf("LISTEN ERROR: %s\n", strerror(errno));
        close(socketFileDescriptor);
        exit(1);
    }

    printf("socket listening...\n");
}

void MasterProcess::acceptClient() {
    printf("-------------------------\n");
    printf("waiting for client...\n");
    clientSocket = accept(socketFileDescriptor, (struct sockaddr *) &clientAddr, &serverAddressLength);
    if (clientSocket == -1){
        printf("ACCEPT ERROR: %s\n", strerror(errno));
    }

    clientAddressLength = sizeof(clientAddr);
    currentReturnCode = getpeername(clientSocket, (struct sockaddr *) &clientAddr, &clientAddressLength);
    if (currentReturnCode == -1){
        printf("GETPEERNAME ERROR: %s\n", strerror(errno));
    }
    else {
//        printf("Client socket filepath: %s\n", clientAddr.sun_path);
    }
}

void MasterProcess::receive() {

    memset(buffer, 0, sizeof(buffer));
    long bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
    if (bytesReceived == -1){
        printf("RECV ERROR: %s\n", strerror(errno));
        close(clientSocket);
    }
    else {
//        printf("DATA RECEIVED = %s\n", buffer);
    }

}

void MasterProcess::processMessage() {
    printf("processing message...\n");
    if( strstr(clientAddr.sun_path, "linda_output") != nullptr){
        processOutput();
    }else if( strstr(clientAddr.sun_path, "linda_read") != nullptr){
        processRead();
    }else if( strstr(clientAddr.sun_path, "linda_input") != nullptr){
        processInput();
    }
}

void MasterProcess::processOutput() {
    printf("linda_output...\n");
    Tuple tuple = Tuple::deserialize(buffer);
    tuple.print();
    if(waitingProcesses.empty()) {
        tuples.emplace_back(tuple);
    } else{
        checkWaitingProcesses(tuple);
    }
    respond();
}

void MasterProcess::processRead() {
    printf("linda_read...\n");
    TuplePattern pattern = TuplePattern::deserialize(buffer);
    pattern.print();
    std::optional<Tuple> tuple;
    if((tuple = pattern.findMatching(tuples))){
        sendTuple(tuple.value());
    }else{
        createAwaitingProcess(pattern, false);
    }
}

void MasterProcess::processInput() {
    printf("linda_input...\n");
    TuplePattern pattern = TuplePattern::deserialize(buffer);
    pattern.print();
    std::optional<Tuple> tuple;
    if((tuple = pattern.deleteMatching(tuples))){
        if(!sendTuple(tuple.value()))
            tuples.emplace_back(tuple.value());
    }else{
        createAwaitingProcess(pattern, true);
    }
}

bool MasterProcess::sendTuple(const Tuple& tuple) {
    char *msg = tuple.serialize();
    currentReturnCode = send(clientSocket, msg, strlen(msg), 0);
    delete[] msg;
    close(clientSocket);
    return (currentReturnCode != -1);
}

void MasterProcess::respond() {
    memset(buffer, 0, sizeof(buffer));
    strcpy(buffer, RESPONSE);
    send(clientSocket, buffer, strlen(buffer), 0);
    close(clientSocket);
}

void MasterProcess::createAwaitingProcess(const TuplePattern& pattern, bool isInput) {
    printf("creating waiting process...\n");
    int fd1[2];
    int fd2[2];
    if (pipe(fd1)==-1)
    {
        fprintf(stderr, "Pipe Failed" );
    }
    if (pipe(fd2)==-1)
    {
        fprintf(stderr, "Pipe Failed" );
    }
    pid_t pid = fork();
    if(pid < 0) {
        fprintf(stderr, "fork Failed");
    }else if( pid > 0){
        close(fd1[0]);
        close(fd2[1]);
        WaitingProcessInfo waitingProcess = WaitingProcessInfo(pid, fd2[0], fd1[1], pattern, isInput );
        waitingProcesses.emplace_back(waitingProcess);
        close(clientSocket);
    }else{
        WaitingProcess waitingProcess = WaitingProcess(fd1[0], fd2[1], clientSocket);
        waitingProcess.run();
    }
}

void MasterProcess::checkWaitingProcesses(const Tuple& tuple) {
    auto it = waitingProcesses.begin();
    while(it != waitingProcesses.end()) {
        if(it->getPattern().checkIfMatch(tuple)){
            memset(buffer, 0, sizeof(buffer));
            char* serialized = tuple.serialize();
            write(it->getWritePipeDescriptor(), serialized, strlen(serialized));
            read(it->getReadPipeDescriptor(), buffer, sizeof(buffer));
            if(it->isInput()) {
                if (strcmp(RESPONSE, buffer) == 0) {
                    getChildReturnValue(it);
                    return;
                }
            }
            getChildReturnValue(it);
        } else
            ++it;
    }
    tuples.emplace_back(tuple);
}

void MasterProcess::getChildReturnValue(std::vector<WaitingProcessInfo>::iterator iterator) {
    int status;
    waitpid(iterator->getPid(), &status, 0);
    waitingProcesses.erase(iterator);
}
