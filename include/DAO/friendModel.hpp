#ifndef FRIENDMODEL_HPP
#define FRIENDMODEL_HPP

#include <user.hpp>
#include <jdbc.hpp>
#include <MSGenum.hpp>

class friendModel
{
private:
    /* data */
    MySQL daoObj;

private:
    friendModel(/* args */);
    ~friendModel();

public:
    static friendModel *getInstance();
    bool isFriend(user u1, user u2);
    void beFriend(user u1, user u2);
    void breakFriend(user u1, user u2);
};



#endif