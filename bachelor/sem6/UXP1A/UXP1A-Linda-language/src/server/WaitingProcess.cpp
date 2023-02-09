#include "../../include/server/WaitingProcess.h"
#include <cstring>
#include <sys/socket.h>

void WaitingProcess::run() {
    memset(buffer, 0, sizeof(buffer));
    read(readPipeDescriptor, buffer, sizeof(buffer));
    size_t currentReturnCode = send(clientSocket, buffer, strlen(buffer), 0);
    std::cout << " WAITING PROCESS RESPONSES " <<buffer<< std::endl;
    memset(buffer, 0, sizeof(buffer));
    if (currentReturnCode == -1) {
        printf("SEND ERROR: %s", strerror(errno));
        strcpy(buffer, RESPONSE_FAIL);
        write(writePipeDescriptor, buffer, strlen(buffer));
    }
    else {
        strcpy(buffer, RESPONSE_OK);
        write(writePipeDescriptor, buffer, strlen(buffer));
        printf("Data sent!\n");
    }
    close(readPipeDescriptor);
    close(writePipeDescriptor);
    close(clientSocket);
    exit(0);
}