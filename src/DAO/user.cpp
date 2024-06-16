#include <user.hpp>

user::user()
{
    _accout = "";
    _name = "";
    _password = "";
    _state = "offline";
}

user::user(json &js)
{
    fromJson(js);
}

user::~user()
{
}

string user::getAccout()
{
    return _accout;
}
string user::getName()
{
    return _name;
}
string user::getPassword()
{
    return _password;
}
string user::getState()
{
    return _state;
}

void user::setAccout(string accout)
{
    this->_accout = accout;
}
void user::setName(string name)
{
    this->_name = name;
}
void user::setPassword(string password)
{
    this->_password = password;
}
void user::setState(string state)
{
    this->_state = state;
}

user user::fromJson(json &js)
{

    auto findMember = js.find("name");
    if (findMember == js.end())
    {
        _name = "";
    }
    else
    {
        _name = findMember.value();
    }
    findMember = js.find("accout");
    if (findMember == js.end())
    {
        _accout = "";
    }
    else
    {
        _accout = findMember.value();
    }

    findMember = js.find("password");
    if (findMember == js.end())
    {
        _password = "";
    }
    else
    {
        _password = findMember.value();
    }

    findMember = js.find("state");
    if (findMember == js.end())
    {
        _state = "";
    }
    else
    {
        _state = findMember.value();
    }

    return *this;
}

json user::toJson(){

    json tojson;
    tojson["accout"]=getAccout();
    tojson["name"]=getName();
    tojson["password"]=getPassword();
    tojson["state"]=getState();
    return tojson;
}