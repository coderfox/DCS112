#include "global.hpp"
#include "user.hpp"
#include "userController.hpp"
#include <string>
#include <algorithm>
#include <iomanip>
#include <sstream>
#include <cstring>
#include <iostream>

using namespace std;
using namespace Alipay;

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
bool verifyPasswordFormat(const char *password)
{
    if (strlen(password) < 8 || strlen(password) > 20)
        return false;
    for (const char *chr = password; *chr != '\0'; chr++)
    {
        if (!is_alnum(*chr))
        {
            return false;
        }
    }
    return true;
}
bool verifyUsernameFormat(const char *username)
{
    if (strlen(username) < 6 || strlen(username) > 20)
        return false;
    for (const char *chr = username; *chr != '\0'; chr++)
    {
        if (!is_alnum(*chr))
        {
            return false;
        }
    }
    return true;
}

userController::userController(double interest_rate)
    : interest_rate(interest_rate), usercount(0)
{
}
userController::~userController()
{
    for (int i = 0; i < usercount; i++)
    {
        delete users[i];
    }
}
int userController::getUserIndex(const char *username) const
{
    for (int i = 0; i < usercount; i++)
    {
        if (!strcmp(users[i]->getUsername(), username))
        {
            return i;
        }
    }
    return -1;
}
bool userController::createUser(const char *username, const char *password)
{
    if (!verifyUsernameFormat(username) || !verifyPasswordFormat(password))
        return false;
    if (getUserIndex(username) >= 0)
        return false;
    users[usercount++] = new user(username, password);
    return true;
}
bool userController::deposite(const char *username, double amount)
{
    if (getUserIndex(username) < 0)
        return false;
    return users[getUserIndex(username)]->deposite(amount);
}
bool userController::withdraw(const char *username, double amount)
{
    if (getUserIndex(username) < 0)
        return false;
    return users[getUserIndex(username)]->withdraw(amount);
}
std::string userController::getUserInfoByName(const char *username) const
{
    if (getUserIndex(username) < 0)
        return "No such user!";
    user *u = users[getUserIndex(username)];
    stringstream ss;
    ss << "username:" << u->getUsername() << endl
       << "password:*********" << endl
       << "balance:" << u->getBalance();
    return ss.str();
}
int userController::getUserCount(void) const
{
    return usercount;
}
bool userController::removeUserByUsername(const char *username)
{
    int index = getUserIndex(username);
    if (index < 0)
        return false;
    // cout << "[DELETE] " << index << ' ' << usercount << endl;
    if (index != usercount - 1)
        swap(users[index], users[usercount - 1]);
    usercount--;
    // cout << "[DELETE] " << username << ' ' << users[usercount] << endl;
    delete users[usercount];
    return true;
}
bool userController::setInterest(double interest)
{
    interest_rate = interest;
    return true;
}
void userController::payInterest(void)
{
    for (int i = 0; i < usercount; i++)
    {
        user *u = users[i];
        u->deposite(u->getBalance() * interest_rate);
    }
}