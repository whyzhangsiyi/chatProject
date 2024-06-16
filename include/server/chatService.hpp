#ifndef CHATSERVICE_H
#define CHATSERVICE_H

#include <unordered_map>
#include <functional>
#include <TcpServer.h>
#include <Timestamp.h>
#include <TcpConnection.h>
#include <json.hpp>
#include <namespace.hpp>
#include <iostream>
#include <MSGenum.hpp>
#include <user.hpp>

#include<userModel.hpp>
#include<mutex>
#include<friendModel.hpp>
// 单例模式的chatservice

using MsgHandler = function<void(const TcpConnectionPtr &conn, json &js, Timestamp time)>;

class chatService
{

public:
    static chatService *getInstance();
    MsgHandler getHandler(int msgId);
    void  clientCloseWithException(const TcpConnectionPtr &conn);


private:
    chatService(/* args */);
    ~chatService();

private: // 业务函数
    void LOGIN(const TcpConnectionPtr &conn, json &js, Timestamp time);
    void REG(const TcpConnectionPtr &conn, json &js, Timestamp time);
    void addFriend(const TcpConnectionPtr &conn, json &js, Timestamp time);
    void CHAT_ONE_TO_ONE(const TcpConnectionPtr &conn, json &js, Timestamp time);


private: 
    // ** 业务函数映射表
    unordered_map<int, MsgHandler> _msgHanderMap;
    unordered_map< TcpConnectionPtr,json>_onlineClientMap;
    std::mutex _onLineClientMapMut;

    //** dao层
    userModel* _usermodel;
    friendModel* _friendmodel;

};

#endif