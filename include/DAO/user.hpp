#ifndef USER_HPP
#define USER_HPP
#include <string>
#include <namespace.hpp>
class user
{
private:
    string _accout;
    string _name;
    string _password;
    string _state;
    /* data */
public:
    user();
    user(json&);
    ~user();

    string getAccout();
    string getName();
    string getPassword();
    string getState();
    user fromJson(json&);
    json toJson();

    void setAccout(string);
    void setName(string);
    void setPassword(string);
    void setState(string);
};

#endif