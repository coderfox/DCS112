#include "COMPLEX.h"
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>

using namespace std;

COMPLEX::COMPLEX(double re, double im) : real(re), image(im)
{
}
COMPLEX::COMPLEX(const COMPLEX &other) : COMPLEX(other.real, other.image)
{
}
COMPLEX COMPLEX::operator+(const COMPLEX &rhs)
{
    return COMPLEX(real + rhs.real, image + rhs.image);
}
COMPLEX COMPLEX::operator-(const COMPLEX &rhs)
{
    return COMPLEX(real - rhs.real, image - rhs.image);
}
COMPLEX COMPLEX::operator-()
{
    return COMPLEX(-real, -image);
}
COMPLEX COMPLEX::operator=(const COMPLEX &other)
{
    real = other.real;
    image = other.image;
    return *this;
}

COMPLEX &COMPLEX::operator++()
{
    real++;
    image++;
    return *this;
}

COMPLEX COMPLEX::operator++(int)
{
    COMPLEX tmp = *this;
    operator++();
    return tmp;
}

COMPLEX &COMPLEX::operator--()
{
    real--;
    image--;
    return *this;
}

COMPLEX COMPLEX::operator--(int)
{
    COMPLEX tmp = *this;
    operator--();
    return tmp;
}

void COMPLEX::print()
{
    if (real == 0.0 && image == 0.0)
        cout << '0';
    else if (real == 0.0 && image != 0.0)
        cout << image << 'i';
    else if (real != 0.0 && image == 0.0)
        cout << real;
    else if (real != 0.0 && image != 0.0)
    {
        cout << real;
        cout << (image > 0 ? '+' : '-');
        if (abs(image) != 1.0)
            cout << abs(image) << 'i';
        else
            cout << 'i';
    }
    cout << endl;
}
