
#ifndef MSGENUM_HPP
#define MSGENUM_HPP
enum MSG_TYPE {

MSG_LOGIN_REQ=1,
MSG_LOGIN_RES,
MSG_REG_REQ,
MSG_REG_RES,
MSG_ADDFRIEND_REQ,
MSG_ADDFRIEND_RES,
MSG_CHAT_ONE_TO_ONE_REQ,
MSG_CHAT_ONE_TO_ONE_RES



};

enum ERROR_TYPE{


    ERR_NOERROE=0,
    ERR_USER_NOTFOUND,
    ERR_USER_EXISTED,
    ERR_HAD_BEEN_FRIEND


};


#endif