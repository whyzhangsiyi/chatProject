#include "chatServer.hpp"
#include <iostream>
#include"chatService.hpp"

void chatServer::start()
{
    _server.start();
}
void chatServer::onConnection(const TcpConnectionPtr &conn)
{
    if (conn->connected())
    {
        std::cout << conn->peerAddress().toIpPort() << "  connected ";
    }
    else
    {
        chatService::getInstance()->clientCloseWithException(conn);
        std::cout << conn->peerAddress().toIpPort() << "  disconnected ";
        conn->shutdown();
    }
}

void chatServer::onMessage(const TcpConnectionPtr &conn, Buffer *buffer, Timestamp time)
{
    string buf = buffer->retrieveAllAsString();
    json js=json::parse(buf);
    auto handler =chatService::getInstance()->getHandler(js["msgType"].get<int>());
    handler(conn,js,time);
}