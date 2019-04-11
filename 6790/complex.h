
#include <iostream>
#include <iomanip>

using namespace std;

class Complex
{

    double real, imag;

  public:
    Complex(double x = 0, double y = 0); // constructor, set real = x, imag = y

    void print(); //output the complex number with proper form. e.g. 1+2i

    friend Complex add(const Complex &, const Complex &); // return sum of two complex numbers

    friend Complex multiply(const Complex &, const Complex &); // return product of two complex numbers
};

Complex::Complex(double x, double y) : real(x), imag(y) {}

void Complex::print()
{
    if (real == 0 && imag == 0)
        cout << '0' << endl;
    else if (real == 0 && imag != 0)
        cout << imag << 'i' << endl;
    else if (real != 0 && imag == 0)
        cout << real << endl;
    else if (real != 0 && imag != 0)
        cout << real << showpos << imag << 'i' << noshowpos << endl;
}

Complex add(const Complex &lhs, const Complex &rhs)
{
    return Complex(lhs.real + rhs.real, lhs.imag + rhs.imag);
}

Complex multiply(const Complex &lhs, const Complex &rhs)
{
    return Complex(lhs.real * rhs.real - lhs.imag * rhs.imag,
                   lhs.real * rhs.imag + lhs.imag * rhs.real);
}
