#include "userModel.hpp"

userModel *userModel::getInstance()
{

    static userModel usermodel;
    return &usermodel;
}

userModel::userModel(/* args */)
{
}

userModel::~userModel()
{
}

void userModel::addUser(user &u)
{
    u.setState("offline");
    string formatSql = util::Format("INSERT INTO user_t (accout,name, password, state) VALUES ('{0}','{1}','{2}','{3}');", u.getAccout(), u.getName(), u.getPassword(), u.getState());
    daoObj.DbUpdate(formatSql);
}

bool userModel::ifOnline(user u)
{

    string sql = util::Format("select state from user_t where accout='{0}';", u.getAccout());
    auto res = daoObj.DbQuery(sql);
    ResultSet *set = res->getRealResultSetPtr();
    if (set->next())
    {
        string state = set->getString("state");
        if (state == string("online"))
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    
}

int userModel::idOfUser(user u)
{

    string sql = util::Format("select id from user_t where accout='{0}';", u.getAccout());
    auto res = daoObj.DbQuery(sql);
    ResultSet *set = res->getRealResultSetPtr();
    return set->getInt("id");
}

bool userModel::ifExistAccout(user u)
{
    string sql = util::Format("select id from user_t where accout='{0}';", u.getAccout());
    auto res = daoObj.DbQuery(sql);
    ResultSet *set = res->getRealResultSetPtr();
    if (set->next())
    {
        return true;
    }
    return false;
}

pair<bool, user> userModel::findUserByaccoutAndPAssword(user &u)
{
    string sql = util::Format("select * from user_t where accout='{0}' and password='{1}';", u.getAccout(), u.getPassword());
    auto res = daoObj.DbQuery(sql);
    ResultSet *set = res->getRealResultSetPtr();
    user us;
    if (set->next())
    {
        us.setAccout(set->getString("accout"));
        us.setName(set->getString("name"));
        us.setPassword(set->getString("password"));
        us.setState(set->getString("state"));
        return pair<bool, user>(true, us);
    }
    else
    {
        return pair<bool, user>(false, user());
    }
}

void userModel::upDateStateToOnline(user u)
{
    string fomatsql = util::Format("UPDATE chat.user_t SET state = 'online' WHERE accout = '{}';", u.getAccout());
    daoObj.DbUpdate(fomatsql);
}

void userModel::upDateStateToOffline(user u)
{
    string fomatsql = util::Format("UPDATE chat.user_t SET state = 'offline' WHERE accout = {};", u.getAccout());
    daoObj.DbExcuteSql(fomatsql);
}