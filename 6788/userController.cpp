#include "global.hpp"
#include "user.hpp"
#include "userController.hpp"
#include <cstring>
#include <iostream>
using namespace Alipay;
using namespace std;
/*double interest_rate;
user* users[MAX_USER];
int usercount;
int getUserIndex(const char* username) const;
MAX_USER 10000
*/
/*class user {
		char username[21];
		char password[21];
		double balance;
	*/
int userController::getUserIndex(const char *username) const
{
    int flag = 0;
    int i = 0;
    for (i = 0; i < usercount; i++)
    {
        flag = strcmp(users[i]->getUsername(), username);
        if (flag == 0)
        {
            break;
        }
    }
    /*string a = username;
	string b;
	for (i = 0; i < usercount; i++) {
		b = users[i]->getUsername();
		if (a == b) {
			break;
		}
	}*/
    return i;
}
userController::userController(double interest_rate)
{
    this->interest_rate = interest_rate;
    for (int i = 0; i < MAX_USER; i++)
    {
        users[i] = NULL;
    }
    usercount = 0;
}
userController::~userController()
{
    int i = 0;
    while (users[i])
    {
        delete users[i];
        i++;
        if (i == MAX_USER)
        {
            break;
        }
    }
    usercount = 0;
}
bool userController::createUser(const char *username, const char *password)
{
    /*int i = 0;
	while (this->users[i]) {
		i++;
		if (i == MAX_USER) {
			break;
		}
	}*/
    string tmpname = username;
    int lenname = tmpname.length();
    int flag1 = 0;
    for (int i = 0; i < lenname; i++)
    {
        if ((tmpname.at(i) >= 48 && tmpname.at(i) <= 57) || (tmpname.at(i) >= 65 && tmpname.at(i) <= 90) || (tmpname.at(i) >= 97 && tmpname.at(i) <= 122))
        {
            flag1 = 1;
        }
        else
        {
            flag1 = 0;
            break;
        }
    }
    if (lenname < 6 || lenname > 20)
    {
        flag1 = 0;
    }
    string tmppass = password;
    int lenpass = tmppass.length();
    int flag2 = 0;
    for (int i = 0; i < lenpass; i++)
    {
        if ((tmppass.at(i) >= 48 && tmppass.at(i) <= 57) || (tmppass.at(i) >= 65 && tmppass.at(i) <= 90) || (tmppass.at(i) >= 97 && tmppass.at(i) <= 122))
        {
            flag2 = 1;
        }
        else
        {
            flag2 = 0;
            break;
        }
    }
    if (lenpass < 8 || lenpass > 20)
    {
        flag2 = 0;
    }
    if (flag1 == 0 || flag2 == 0)
    {
        return false;
    }
    else if (usercount == MAX_USER)
    {
        return false;
    }
    else
    {
        this->users[usercount] = new user(username, password);
        usercount++;
        if (users[usercount - 1])
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}
bool userController::deposite(const char *username, double amount)
{
    int i = getUserIndex(username);
    if (amount > 0)
    {
        users[i]->deposite(amount);
        return true;
    }
    else
    {
        return false;
    }
}
bool userController::withdraw(const char *username, double amount)
{
    int i = getUserIndex(username);
    if (amount > 0 && amount < users[i]->getBalance())
    {
        users[i]->withdraw(amount);
        return true;
    }
    else
    {
        return false;
    }
}
std::string userController::getUserInfoByName(const char *username) const
{
    int i = getUserIndex(username);
    string ret = "username:";
    ret.append(username);
    ret.append("\n");
    ret.append("password:*********\nbalance:");
    int temp = users[i]->getBalance();
    char a[20] = {0};
    int wei = 0;
    int j = 0;
    while (temp)
    {
        a[j] = temp % 10 + '0';
        temp = temp / 10;
        j++;
        wei++;
    }
    temp = users[i]->getBalance();
    for (j = wei - 1; j >= 0; j--)
    {
        ret = ret + a[j];
    }
    return ret;
}
int userController::getUserCount(void) const
{
    return usercount;
}
bool userController::removeUserByUsername(const char *username)
{
    int i = getUserIndex(username);
    if (i == usercount)
    {
        return false;
    }
    users[i]->setPassword(users[usercount - 1]->getPassword());
    users[i]->setUsername(users[usercount - 1]->getUsername());
    delete users[usercount - 1];
    usercount--;
    return true;
}
bool userController::setInterest(double interest)
{
    if (interest > 0)
    {
        interest_rate = interest;
        return true;
    }
    else
    {
        return false;
    }
}
void userController::payInterest(void)
{
    //double temp = 0;
    for (int i = 0; i < usercount; i++)
    {
        //temp = users[i]->getBalance() - (users[i]->getBalance())*interest_rate;
        users[i]->deposite((users[i]->getBalance()) * interest_rate);
    }
}