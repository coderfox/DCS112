#include "fraction.h"
#include <iostream>

using namespace std;

int fraction::gcd(const int &a, const int &b) const
{
    if (b == 0)
        return a;
    return gcd(b, a % b);
}
void fraction::simp()
{
    if (_denominator == 0)
        return;
    auto gcd = this->gcd(_denominator, _numerator);
    _denominator /= gcd;
    _numerator /= gcd;
    if (_denominator < 0)
    {
        _denominator = -_denominator;
        _numerator = -_numerator;
    }
}
fraction::fraction(const int &numerator, const int &denominator) : _numerator(numerator), _denominator(denominator)
{
    simp();
}
fraction::fraction(const fraction &rhs) : fraction(rhs._numerator, rhs._denominator)
{
}
void fraction::operator=(const fraction &rhs)
{
    _numerator = rhs._numerator;
    _denominator = rhs._denominator;
}
fraction fraction::operator+(const fraction &rhs) const
{
    if (_denominator == 0 || rhs._denominator == 0)
        return fraction(0, 0);
    auto deno_gcd = gcd(_denominator, rhs._denominator);
    auto numl = _numerator * (rhs._denominator / deno_gcd);
    auto numr = rhs._numerator * (_denominator / deno_gcd);
    auto frac = fraction(numl + numr, _denominator / deno_gcd * rhs._denominator);
    return frac;
}
fraction fraction::operator-(const fraction &rhs) const
{
    if (_denominator == 0 || rhs._denominator == 0)
        return fraction(0, 0);
    auto deno_gcd = gcd(_denominator, rhs._denominator);
    auto numl = _numerator * (rhs._denominator / deno_gcd);
    auto numr = rhs._numerator * (_denominator / deno_gcd);
    auto frac = fraction(numl - numr, _denominator / deno_gcd * rhs._denominator);
    return frac;
}
fraction fraction::operator*(const fraction &rhs) const
{
    auto frac = fraction(_numerator * rhs._numerator, _denominator * rhs._denominator);
    return frac;
}
fraction fraction::operator/(const fraction &rhs) const
{
    auto deno_gcd = gcd(_denominator, rhs._denominator);
    auto frac = fraction(_numerator * (rhs._denominator / deno_gcd), (_denominator / deno_gcd) * rhs._numerator);
    return frac;
}
void fraction::operator+=(const fraction &rhs)
{
    operator=((*this) + rhs);
}
void fraction::operator-=(const fraction &rhs)
{
    operator=((*this) - rhs);
}
void fraction::operator*=(const fraction &rhs)
{
    operator=((*this) * rhs);
}
void fraction::operator/=(const fraction &rhs)
{
    operator=((*this) / rhs);
}
bool fraction::operator==(const fraction &rhs) const
{
    return (_denominator == 0 && rhs._denominator == 0) ||
           (_denominator == rhs._denominator && _numerator == rhs._numerator);
}
bool fraction::operator!=(const fraction &rhs) const
{
    return !(operator==(rhs));
}
bool fraction::operator<(const fraction &rhs) const
{
    auto deno_gcd = gcd(_denominator, rhs._denominator);
    return (_numerator * (rhs._denominator / deno_gcd)) < (rhs._numerator * (_denominator / deno_gcd));
}
bool fraction::operator>(const fraction &rhs) const
{
    auto deno_gcd = gcd(_denominator, rhs._denominator);
    return (_numerator * (rhs._denominator / deno_gcd)) > (rhs._numerator * (_denominator / deno_gcd));
}
bool fraction::operator<=(const fraction &rhs) const
{
    return (_denominator == 0 || rhs._denominator == 0) || operator<(rhs) || operator==(rhs);
}
bool fraction::operator>=(const fraction &rhs) const
{
    return (_denominator == 0 || rhs._denominator == 0) || operator>(rhs) || operator==(rhs);
}
std::istream &operator>>(std::istream &in, fraction &rhs)
{
    in >> rhs._numerator >> rhs._denominator;
    rhs.simp();
    return in;
}
std::ostream &operator<<(std::ostream &out, const fraction &rhs)
{
    if (rhs._denominator == 0)
    {
        out << "NaN";
    }
    else
    {
        if (rhs._denominator == 1)
            out << rhs._numerator;
        else
            out << rhs._numerator << '/' << rhs._denominator;
    }
    return out;
}