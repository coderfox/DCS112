#include "MyInteger.hpp"
#include <cmath>
#include <string>

MyInteger::MyInteger(int val) : value(val)
{
}
int MyInteger::getValue() const { return value; }
bool MyInteger::isEven() const { return isEven(value); }
bool MyInteger::isOdd() const { return isOdd(value); }
bool MyInteger::isPrime() const { return isPrime(value); }

bool MyInteger::isEven(int value)
{
    return value % 2 == 0;
}
bool MyInteger::isOdd(int value) { return value % 2 != 0; }
bool MyInteger::isPrime(int value)
{
    if (value == 1)
        return false;
    if (value == 2)
        return true;
    if (MyInteger::isEven(value))
        return false;
    for (int i = 3; i <= std::sqrt(value); i += 2)
    {
        if (value % i == 0)
            return false;
    }
    return true;
}
bool MyInteger::isEven(const MyInteger &val) { return val.isEven(); }
bool MyInteger::isOdd(const MyInteger &val) { return val.isOdd(); }
bool MyInteger::isPrime(const MyInteger &val) { return val.isPrime(); }
bool MyInteger::equals(int rhs) { return getValue() == rhs; }
bool MyInteger::equals(const MyInteger &rhs) { return value == rhs.getValue(); }
int MyInteger::parseInt(const std::string &str) { return std::stoi(str); }