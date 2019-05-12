#include <iostream>

using namespace std;

class Car
{
public:
    Car()
    {
        cout << "Construct a car" << endl;
    }
};

class Wheel
{
public:
    Wheel()
    {
        cout << "Construct a wheel" << endl;
    }
};

class RedCar : Car
{
public:
    RedCar()
    {
        cout << "Construct a red car" << endl;
    }

private:
    Wheel _wheels[4];
};
