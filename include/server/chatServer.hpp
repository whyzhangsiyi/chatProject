#include<TcpServer.h>
#include<EventLoop.h>
#include <string>
#include "InetAddress.h"
#include<iostream>
#include "Timestamp.h"
#include<mutex>

/*基于muduo网络库开发服务器程序
1.组合tcp的server对象
2.创建eventLoop事件循环对象,在构造服务器对象时给其构造函数传入该事件循环对象的指针
3.明确tcpserver构造函数需要什么参数,输出当前服务器类的构造函数参数
4.在当前服务器类构造函数中注册处理连接的回调函数和处理读写事件的回调函数
5.设置合适的服务端线程数量,muduo回自动分配 I/O线程和工作线程*/
using namespace std;
using namespace muduo;
using namespace muduo::net;
using namespace placeholders;

class chatServer{

public:

chatServer(EventLoop* loop,const InetAddress& listenAddr,const string& nameArg)
:_loop(loop),_server(loop,listenAddr,nameArg){
    _server.setConnectionCallback(std::bind(&chatServer::onConnection,this,_1));
    _server.setMessageCallback(std::bind(&chatServer::onMessage,this,_1,_2,_3));
    _server.setThreadNum(4);
}

void start();
~chatServer(){}

private:
void onConnection(const TcpConnectionPtr& con);

void onMessage(const TcpConnectionPtr&con, Buffer*buffer, Timestamp time );

private:
EventLoop* _loop;
muduo::net::TcpServer _server;

};