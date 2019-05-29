#include <iostream>

using std::cout;
using std::endl;

/*
    Default Constructor of Cat is Running
    Constructor of Cat is Running 6
    Constructor of Tiger is Running 6
    Constructor of Cat is Running 18
    Constructor of Tiger is Running 18
    Destructor of Tiger is Running 18
    Destructor of Cat is Running 18
    Destructor of Tiger is Running 6
    Destructor of Cat is Running 6
    Destructor of Cat is Running 0
    */

class Cat
{
    int data;

public:
    Cat() : data(0)
    {
        cout << "Default Constructor of Cat is Running" << endl;
    }
    Cat(int data) : data(data)
    {
        cout << "Constructor of Cat is Running " << data << endl;
    }
    ~Cat()
    {
        cout << "Destructor of Cat is Running " << data << endl;
    }
};

class Tiger : public Cat
{
    int data;

public:
    Tiger() : Cat(), data(0)
    {
        cout << "Default Constructor of Tiger is Running" << endl;
    }
    Tiger(int data) : Cat(data), data(data)
    {
        cout << "Constructor of Tiger is Running " << data << endl;
    }
    ~Tiger()
    {
        cout << "Destructor of Tiger is Running " << data << endl;
    }
};