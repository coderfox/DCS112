#include <cmath>
#include <iostream>
#include "6790/complex.h"
using namespace std;
int main()
{
    double real, imag;
    while (cin >> real >> imag)
    {
        Complex a = Complex(real, imag);
        cin >> real >> imag;
        Complex b = Complex(real, imag);
        Complex c = add(a, b);
        c.print();
        Complex d = multiply(a, b);
        d.print();
    }
}