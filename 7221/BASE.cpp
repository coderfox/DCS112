// 两个父类 分别为 baseA，baseB,
// 两个子类 derivedA和derivedB都继承baseA和baseB
// 最后的子类是Derived ，继承derivedA和derivedB

#include <iostream>

using namespace std;

class baseA
{
public:
    baseA()
    {
        cout << "This is baseA class." << endl;
    }
};
class baseB
{
public:
    baseB()
    {
        cout << "This is baseB class." << endl;
    }
};
class derivedA : public virtual baseA, public baseB
{
public:
    derivedA()
    {
        cout << "This is derivedA class." << endl;
    }
};
class derivedB : public virtual baseA, public virtual baseB
{
public:
    derivedB()
    {
        cout << "This is derivedB class." << endl;
    }
};
class Derived : public derivedB, public derivedA
{
public:
    Derived()
    {
        cout << "This is Derived class." << endl;
    }
};
