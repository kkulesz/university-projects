#include "../../include/client/linda.h"
#include <csignal>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <sys/time.h>

unsigned char PATH_LENGTH_LIMIT = 100;
std::string server_filename;
std::string client_filename;
int sockfd;
struct sockaddr_un server_addr;
struct sockaddr_un client_addr;


void sig_handler(int signum){
    close(sockfd);
}

void set_timeout(time_t timeout){
    signal(SIGALRM, sig_handler);
    struct itimerval it_val;
    it_val.it_value.tv_sec = timeout/1000;
    it_val.it_value.tv_usec = (timeout*1000) % 1000000;
    it_val.it_interval = it_val.it_value;
    setitimer(ITIMER_REAL, &it_val, nullptr);
}

void init(){
    server_filename = "/tmp/linda_server";
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sun_family = AF_UNIX;
    strncpy(server_addr.sun_path, server_filename.c_str(), PATH_LENGTH_LIMIT);

    memset(&client_addr, 0, sizeof(client_addr));
    client_addr.sun_family = AF_UNIX;
    strncpy(client_addr.sun_path, client_filename.c_str(), PATH_LENGTH_LIMIT);

    if ((sockfd = socket(AF_UNIX, SOCK_STREAM, 0)) < 0) {
        perror("socket failed");
    }
    unlink(client_filename.c_str());
    if(bind(sockfd, (struct sockaddr *) &client_addr, sizeof(client_addr))){
        perror("bind failed");
    }

    if(connect(sockfd, (struct sockaddr *) &server_addr, sizeof(server_addr))){
        perror("connect failed");
    }
}

void send_to_server(const char* msg){
    long n = send(sockfd, msg, strlen(msg), 0);
    if (n < 0)
        perror("send failed");

    delete[] msg;
}

void wait_for_response(){
    char buf[512];
    memset(buf, 0, sizeof(buf));
    long rc = recv(sockfd, buf, sizeof(buf), 0);
    if (rc == -1) {
        printf("RECV ERROR = %s\n", strerror(errno));
        close(sockfd);
        exit(1);
    }

    close(sockfd);
}

std::optional<Tuple> wait_for_tuple(){
    char buf[512];
    memset(buf, 0, sizeof(buf));
    long rc = recv(sockfd, buf, sizeof(buf), 0);
    if (rc == -1) {
        //TODO: tutaj zawsze wypisuje się 'RECV ERROR = Bad file descriptor' jak mamy timeout, ja bym olał wypisywanie tego błędu
        // wiem ze brzydkie rozwiazanie, ale kij w to
        //printf("RECV ERROR = %s\n", strerror(errno));
        close(sockfd);
        return std::nullopt;
    }
    else {
        Tuple tuple = Tuple::deserialize(buf);
        close(sockfd);
        return tuple;
    }
}


std::optional<Tuple> communicate(const TuplePattern& pattern, time_t timeout = 0){
    init();
    char *msg = pattern.serialize();
    send_to_server(msg);
    if(timeout)
        set_timeout(timeout);
    return wait_for_tuple();
}

std::optional<Tuple> linda_read(const TuplePattern& pattern, time_t timeout = 0){
    client_filename = "/tmp/linda_read_" + std::to_string(getpid());
    return communicate(pattern, timeout);
}

std::optional<Tuple> linda_input(const TuplePattern& pattern, time_t timeout = 0){
    client_filename = "/tmp/linda_input_" + std::to_string(getpid());
    return communicate(pattern, timeout);
}

void linda_output(const Tuple& tuple){
    client_filename = "/tmp/linda_output_" + std::to_string(getpid());
    init();
    char *msg = tuple.serialize();
    send_to_server(msg);
    wait_for_response();
}