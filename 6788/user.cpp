#include "global.hpp"
#include "user.hpp"
#include <cstring>

using namespace std;
using namespace Alipay;

user::user(const char *username, const char *password)
{
    strcpy(this->username, username);
    strcpy(this->password, password);
    balance = 0;
}
user::~user()
{
}
const char *user::getUsername() const
{
    return username;
}
const char *user::getPassword() const
{
    return password;
}
const void user::setUsername(const char *username)
{
    strcpy(this->username, username);
}
const void user::setPassword(const char *password)
{
    strcpy(this->password, password);
}
double user::getBalance()
{
    return balance;
}
bool user::withdraw(double amount)
{
    if (amount < 0)
        return false;
    if (balance < amount)
        return false;
    balance -= amount;
    return true;
}
bool user::deposite(double amount)
{
    if (amount < 0)
        return false;
    balance += amount;
    return true;
}