#include "user.hpp"
#include <cctype>
#include <string>

using namespace std;
using namespace alipay;

// username should be a combination of letters and numbers and the length should be in [6,20]
// correct: ["Alice1995", "Heart2you", "love2you", "5201314"]
// incorrect: ["222@_@222", "12306", "abc12?"]
// std::string username;

// password should be a combination of letters and numbers and the length should be in [8,20]
// correct: ["12345678", "abc00000000"]
// incorrect: ["123", "21?=_=?12"]
// std::string password;

// phone should be a number and the length should be fixed 13
// correct: ["8618819473230"]
// incorrect: ["110", "330"]
// std::string phone;

// Gender::Gender gender;

// because soil-rich use this system, so no decimal.
// long long int balance;

bool is_alnum(const char chr)
{
    if (chr >= 'A' && chr <= 'Z')
        return true;
    if (chr >= 'a' && chr <= 'z')
        return true;
    if (chr >= '0' && chr <= '9')
        return true;
    return false;
}
bool is_num(const char chr)
{
    return (chr >= '0' && chr <= '9');
}

// auxiliary function for format checking
bool User::verifyPasswordFormat(const std::string &password)
{
    if (password.length() < 8 || password.length() > 20)
        return false;
    for (auto iter = password.begin(); iter != password.end(); iter++)
    {
        if (!is_alnum(*iter))
        {
            return false;
        }
    }
    return true;
}
bool User::verifyUsernameFormat(const std::string &username)
{
    if (username.length() < 6 || username.length() > 20)
        return false;
    for (auto iter = username.begin(); iter != username.end(); iter++)
    {
        if (!is_alnum(*iter))
        {
            return false;
        }
    }
    return true;
}
bool User::verifyPhoneFormat(const std::string &phone)
{
    if (phone.length() != 13)
        return false;
    for (auto iter = phone.begin(); iter != phone.end(); iter++)
    {
        if (!is_num(*iter))
        {
            return false;
        }
    }
    return true;
}
// Because of the mistake of the architect of alibaba,
// all the parameters of these function use c strings(char *).
// you are smart, the transformation is not a problem

// if the input is a valid username, set it and return true
bool User::setUsername(const char *username)
{
    string uname(username);
    if (!verifyUsernameFormat(uname))
        return false;
    else
    {
        this->username = uname;
        return true;
    }
}

// You should confirm the old password and the new_password's format
bool User::setPassword(const char *new_password, const char *old_password)
{
    if (password != string(old_password))
        return false;
    else
    {
        string pass(new_password);
        if (!verifyPasswordFormat(pass))
            return false;
        password = pass;
        return true;
    }
}

bool User::setPhone(const char *new_phone_c)
{
    string new_phone(new_phone_c);
    if (!verifyPhoneFormat(new_phone))
        return false;
    else
    {
        phone = new_phone;
        return true;
    }
}

// You can not set the Gender to unknown again
bool User::setGender(Gender::Gender gender)
{
    if (gender == Gender::Unknown)
        return false;
    else
    {
        this->gender = gender;
        return true;
    }
}

std::string User::getUsername(void)
{
    return username;
}
std::string User::getPhone(void)
{
    return phone;
}
alipay::Gender::Gender User::getGender(void)
{
    return gender;
}

long long int User::getMoneyAmount(const char *password)
{
    if (this->password != string(password))
        return -1;
    else
        return balance;
}

bool User::deposit(long long int amount)
{
    if (amount < 0)
        return false;
    balance += amount;
    return true;
}

// password check is needed when withdraw
bool User::withdraw(long long int amount, const char *password)
{
    if (amount < 0)
        return false;
    if (this->password != string(password))
        return false;
    if (balance < amount)
        return false;
    balance -= amount;
    return true;
}
