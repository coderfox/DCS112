#include "complex.h"
#include <sstream>
#include <iomanip>
#include <cstdio>
#include <cmath>

using namespace std;

Complex::Complex() : real(0), imag(0)
{
}
Complex::Complex(double re, double im) : real(re), imag(im)
{
}
Complex::~Complex()
{
}
const double Complex::getReal(void) const
{
    return real;
}
const double Complex::getImaginary(void) const
{
    return imag;
}
void Complex::setReal(double re)
{
    real = re;
}
void Complex::setImaginary(double im)
{
    imag = im;
}
void Complex::fromString(const std::string &complexString)
{
    sscanf(complexString.c_str(), "%lf%lf", &real, &imag);
}
Complex Complex::operator+(const Complex &rhs)
{
    return Complex(real + rhs.real, imag + rhs.imag);
}
Complex Complex::operator-(const Complex &rhs)
{
    return Complex(real - rhs.real, imag - rhs.imag);
}
Complex Complex::operator*(const Complex &rhs)
{
    return Complex(real * rhs.real - imag * rhs.imag, real * rhs.imag + imag * rhs.real);
}
Complex Complex::operator/(const Complex &rhs)
{
    auto mut = (rhs.real * rhs.real + rhs.imag * rhs.imag);
    return Complex(
        (real * rhs.real + imag * rhs.imag) / mut,
        (-real * rhs.imag + imag * rhs.real) / mut);
}

std::ostream &operator<<(std::ostream &out, Complex &rhs)
{
    auto real = rhs.getReal();
    auto imag = rhs.getImaginary();
    if (real == 0.0 && imag == 0.0)
        out << '0';
    else if (real == 0.0 && imag != 0.0)
        out << imag << 'i';
    else if (real != 0.0 && imag == 0.0)
        out << real;
    else if (real != 0.0 && imag != 0.0)
    {
        out << real << ' ';
        out << (imag > 0 ? '+' : '-') << ' ';
        if (abs(imag) != 1.0)
            out << abs(imag) << 'i';
        else
            out << 'i';
    }
    return out;
}
