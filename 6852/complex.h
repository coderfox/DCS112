#ifndef _COMPLEXH
#define _COMPLEXH
#include<string>
#include<iostream>
class Complex {
  public:
    Complex();
    Complex(double re, double im);
    ~Complex();
    const double getReal(void) const;
    const double getImaginary(void) const;
    void setReal(double re);
    void setImaginary(double im);
    void fromString(const std::string& complexString);
    Complex operator+(const Complex& theComplex);
    Complex operator-(const Complex& theComplex);
    Complex operator*(const Complex& theComplex);
    Complex operator/(const Complex& theComplex);
  private:
    double real;
    double imag;
};
std::ostream& operator<<(std::ostream& out, Complex& theComplex);
#endif

