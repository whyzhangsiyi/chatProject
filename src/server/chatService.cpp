#include "chatService.hpp"


//*********************    chatService的单例实现    ************************
chatService::chatService(/* args */) // 构造函数  在业务映射表里增加业务
{

    _usermodel=userModel::getInstance();
    _friendmodel=friendModel::getInstance();

    _msgHanderMap.insert({MSG_LOGIN_REQ, std::bind(&chatService::LOGIN, this, _1, _2, _3)});
    _msgHanderMap.insert({MSG_REG_REQ, std::bind(&chatService::REG, this, _1, _2, _3)});
    _msgHanderMap.insert({MSG_ADDFRIEND_REQ,std::bind(&chatService::addFriend,this,_1,_2,_3)});
    _msgHanderMap.insert({MSG_CHAT_ONE_TO_ONE_REQ, std::bind(&chatService::CHAT_ONE_TO_ONE, this, _1, _2, _3)});

}

chatService::~chatService() // 析构函数
{

}

MsgHandler chatService::getHandler(int msgId) // 业务处理分发函数
{
    auto it = _msgHanderMap.find(msgId);
    if (it == _msgHanderMap.end())
    {
        return [=](const TcpConnectionPtr &conn, json &js, Timestamp time) {};
    }
    else
    {
        return _msgHanderMap[msgId];
    }
}

chatService *chatService::getInstance() // 单例chatService
{
    static chatService serviceInstance;
    return &serviceInstance;
}

// ******************* 业务函数*******************//

void chatService::clientCloseWithException(const TcpConnectionPtr &conn)
{

    auto find = _onlineClientMap.find(conn);
    if (find != _onlineClientMap.end())
    {
        cout << __LINE__ << __FILE__ << endl;
        std::lock_guard<std::mutex> lg(_onLineClientMapMut);
        _usermodel->upDateStateToOffline(user((find->second)));
        _onlineClientMap.erase(find);
    }
}

void chatService::REG(const TcpConnectionPtr &conn, json &js, Timestamp time)
{
    user newUser(js);
    bool found = _usermodel->ifExistAccout(newUser);
    if (!found) // 不存在账户,可正常注册
    {
        _usermodel->addUser(newUser);
        json sendjs; //{"msgType":LOGIN_RES,"errorType":0,"name":"202119875236"}
        sendjs["msgType"] = MSG_REG_RES;
        sendjs["errorType"] = ERR_NOERROE;
        conn->send(sendjs.dump());
    }
    else // 账户已存在,注册失败
    {
        json sendjs; //{"msgType":LOGIN_RES,"errorType":0,"name":"202119875236"}
        sendjs["msgType"] = MSG_REG_RES;
        sendjs["errorType"] = ERR_USER_EXISTED;
        conn->send(sendjs.dump());
    }
}

void chatService::LOGIN(const TcpConnectionPtr &conn, json &js, Timestamp time)
{

    user LoginUser(js);
    pair<bool, user> found = _usermodel->findUserByaccoutAndPAssword(LoginUser);
    if (found.first)
    {
        {
            std::lock_guard<std::mutex> lg(_onLineClientMapMut);
            _onlineClientMap.insert({conn, js});
        }
        _usermodel->upDateStateToOnline(LoginUser);
        //{"msgType":LOGIN_RES,"errorType":0,"accout":"3eq3","name":"202119875236"}   //登录回复
        json sendjs;
        sendjs["msgType"] = MSG_LOGIN_RES;
        sendjs["errorType"] = ERR_NOERROE;
        sendjs["accout"] = found.second.getAccout();
        sendjs["name"] = found.second.getName();
        conn->send(sendjs.dump());
    }
    else
    {
        json sendjs;
        sendjs["msgType"] = MSG_LOGIN_RES;
        sendjs["errorType"] = ERR_USER_EXISTED;
        conn->send(sendjs.dump());
    }
}

void chatService::addFriend(const TcpConnectionPtr &conn, json &js, Timestamp time)
{

    user u;
    u.setAccout(js["reciver"]);
   if (_usermodel->ifExistAccout(u))
   {
    json sendjs;
    sendjs["msgType"]=MSG_ADDFRIEND_RES;
    sendjs["errorType"]=ERR_USER_NOTFOUND;
    conn->send(sendjs.dump());
   }
    // if (/* condition */)
    // {

    //     /* code */
    // }
    


 // {"msgType":"","inviter":"","reciver":""}
//  {"msgType":"","errorType":""}




}

void chatService::CHAT_ONE_TO_ONE(const TcpConnectionPtr &conn, json &js, Timestamp time)
{
}