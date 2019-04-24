#include "global.hpp"
#include "user.hpp"
#include "userController.hpp"
#include <cstring>
//#pragma warning(suppress : 4996)
using namespace Alipay;
using namespace std;
/*class user {
		char username[21];
		char password[21];
		double balance;
	*/
user::user(const char *username, const char *password)
{
    /*strncpy(this->username, username,21);
	strncpy(this->password, password,21);*/
    int lenp = strlen(password);
    int i = 0;
    for (i = 0; i < lenp; i++)
    {
        //this->password[i] = password[i];
        *(this->password + i) = *(password + i);
    }
    *(this->password + i) = '\0';
    int lenu = strlen(username);
    for (i = 0; i < lenu; i++)
    {
        //this->username[i] = username[i];
        *(this->username + i) = *(username + i);
    }
    *(this->username + i) = '\0';
    balance = 0;
}
user::~user()
{
    balance = 0.0;
    //empty
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
    string a = username;
    //int lenu = strlen(username);
    int lenu = a.length();
    int i = 0;
    for (i = 0; i < lenu; i++)
    {
        //this->username[i] = username[i];
        *(this->username + i) = *(username + i);
    }
    *(this->username + i) = '0';
}
const void user::setPassword(const char *password)
{
    //int lenp = strlen(password);
    string a = password;
    int lenp = a.length();
    int i = 0;
    for (i = 0; i < lenp; i++)
    {
        //this->password[i] = password[i];
        *(this->password + i) = *(password + i);
    }
    *(this->password + i) = '\0';
}
double user::getBalance()
{
    if (this != NULL)
    {
        return balance;
    }
}
bool user::withdraw(double amount)
{
    if (amount <= balance && amount > 0)
    {
        balance -= amount;
        return true;
    }
    else
    {
        return false;
    }
}
bool user::deposite(double amount)
{
    if (this == NULL)
    {
        return false;
    }
    if (amount > 0)
    {
        balance += amount;
        return true;
    }
    else
    {
        return false;
    }
}