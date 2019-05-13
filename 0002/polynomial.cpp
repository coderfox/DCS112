#include <map>
#include <list>
#include <initializer_list>
#include <sstream>
#include <cmath>
#include "polynomial.hpp"

using namespace std;

// ===== Constructors =====

Polynomial::Polynomial()
{
}

Polynomial::Polynomial(list<pair<unsigned int, int>> list)
{
    for (auto iter = list.begin(); iter != list.end(); iter++)
    {
        // filter out "0" coefficients
        if (iter->second != 0)
            _coefficients[iter->first] = iter->second;
    }
}

Polynomial::Polynomial(initializer_list<int> list)
{
    auto degree = list.size() - 1;
    for (auto iter = list.begin();
         iter != list.end();
         iter++, degree--)
    {
        // filter out "0" coefficients
        if (*iter != 0)
            _coefficients[degree] = *iter;
    }
}

// ===== Utilities =====
void Polynomial::garbage_collect()
{
    for (auto iter = _coefficients.begin(); iter != _coefficients.end(); iter++)
    {
        // remove zero coefficients
        if (iter->second == 0)
            _coefficients.erase(iter);
    }
}

// ===== Accessors =====

int &Polynomial::operator[](unsigned int rhs)
{
    return _coefficients[rhs];
}

int Polynomial::get(unsigned int power) const
{
    try
    {
        return _coefficients.at(power);
    }
    catch (out_of_range &)
    {
        return 0;
    }
}

// ===== Operators =====

bool Polynomial::operator==(const Polynomial &rhs) const
{
    for (auto iter : _coefficients)
    {
        if (iter.second != rhs.get(iter.first))
            return false;
    }
    for (auto iter : rhs._coefficients)
    {
        if (iter.second != get(iter.first))
            return false;
    }
    return true;
}

Polynomial Polynomial::operator-() const
{
    return Polynomial() - *this;
}

Polynomial Polynomial::operator+(const Polynomial &rhs) const
{
    auto poly = *this;
    for (auto iter : rhs._coefficients)
    {
        poly[iter.first] += iter.second;
    }
    return poly;
}

Polynomial Polynomial::operator-(const Polynomial &rhs) const
{
    auto poly = *this;
    for (auto iter : rhs._coefficients)
    {
        poly[iter.first] -= iter.second;
    }
    return poly;
}

Polynomial Polynomial::operator*(const Polynomial &rhs) const
{
    Polynomial poly;
    for (auto lhs_iter : _coefficients)
    {
        for (auto rhs_iter : rhs._coefficients)
        {
            poly[lhs_iter.first + rhs_iter.first] += lhs_iter.second * rhs_iter.second;
        }
    }
    return poly;
}

Polynomial Polynomial::derive() const
{
    Polynomial poly;
    for (auto iter : _coefficients)
    {
        if (iter.first != 0)
            poly[iter.first - 1] = iter.first * iter.second;
    }
    return poly;
}

int Polynomial::eval(int x) const
{
    auto res = 0;
    for (auto iter : _coefficients)
    {
        res += pow(x, iter.first) * iter.second;
    }
    return res;
}

// ===== I/O =====

string Polynomial::to_string() const
{
    stringstream ss;
    ss << *this;
    return ss.str();
}

ostream &operator<<(ostream &ostream, const Polynomial &poly)
{
    // output 0 for constantly zero polynomial
    if (poly._coefficients.empty())
        ostream << "0";

    // separator output flag
    bool flag = false;
    for (auto iter : poly._coefficients)
    {
        // skip out "0" coefficients
        if (iter.second == 0)
            continue;
        // use positive/negative symbol as output separator
        if (flag)
            ostream << showpos;

        // output coefficient
        if (
            // if coefficient is not 0 or +1/-1, output coefficient
            (iter.second != 0 && iter.second != 1 && iter.second != -1) ||
            // if the monomial is constant, output coefficient
            iter.first == 0)
            ostream << iter.second << noshowpos;
        // silence coefficient otherwise
        // but provide sign on "1" when separator flag on
        else if (flag && (iter.second == 1 || iter.second == -1))
            ostream << (iter.second > 0 ? '+' : '-');

        // output variable
        // filter out 0
        if (iter.second != 0)
        {
            if (iter.first > 1)
                ostream << "x^" << iter.first;
            else if (iter.first == 1)
                // if the monomial is (Cx), do not output power symbol
                ostream << "x";
        }

        // set separator flag
        flag = true;
    }

    return ostream;
}
