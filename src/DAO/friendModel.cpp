#include <friendModel.hpp>
#include <Format.h>
friendModel::friendModel(/* args */)
{
}

friendModel::~friendModel()
{
}


 friendModel* friendModel::getInstance(){

    static friendModel friendmodel;
    return &friendmodel;
}

bool friendModel::isFriend(user u1, user u2)
{
    string sql = util::Format("select *  from friendId_t where userid=(select id from user_t where  accout='{0}') and friendid=(select id from user_t where  accout='{1}');", u1.getAccout(), u2.getAccout());
    auto res = daoObj.DbQuery(sql);
    ResultSet *set = res->getRealResultSetPtr();
    if (set->next())
    {
        return true;
    }
    return false;
}
void friendModel::beFriend(user u1, user u2) {

    string sql = util::Format("select *  from friendId_t where userid=(select id from user_t where  accout='{0}') and friendid=(select id from user_t where  accout='{1}');", u1.getAccout(), u2.getAccout());
    auto res = daoObj.DbQuery(sql);
    ResultSet *set = res->getRealResultSetPtr();


    // string sql2 =util::Format("INSERT INTO friendId_t (userid,friendid) VALUES ({0},{2});",)

    // if (isFriend(u1,u2))
    // {
    
    // json sendjs;
    // sendjs["msgType"]=MSG_ADDFRIEND_RES;
    // sendjs["errorType"]=ERR_HAD_BEEN_FRIEND;
    // }
    



}
void friendModel::breakFriend(user u1, user u2) {}