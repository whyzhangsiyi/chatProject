#ifndef USERMODEL_HPP
#define USERMODEL_HPP
#include <jdbc.hpp>
#include <user.hpp>
#include <Format.h>
class userModel
{
private:
    MySQL daoObj;

private:
    userModel();
    ~userModel();

public:
    static userModel *getInstance();
    void addUser(user &u);
    pair<bool, user> findUserByaccoutAndPAssword(user &u);
    bool ifExistAccout(user u);
    int idOfUser(user u );
    bool ifOnline(user u);
    void upDateStateToOnline(user u);
    void upDateStateToOffline(user u);
};

#endif