#include "chatServer.hpp"

int main(int argc ,char* argv[]){

    EventLoop loop;
    char* ip=argv[1];
    uint16_t port=atoi(argv[2]);
    InetAddress serverAddr(ip,port);
    chatServer server(&loop,serverAddr,"chatServer");
    server.start();
    loop.loop(); 
    return 0;
}