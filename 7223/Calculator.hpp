#include <string>
#include <sstream>
#include "Exception.hpp"

using namespace std;

int get_number(istringstream &in)
{
    char next;
    in >> next;
    auto pos = static_cast<int>(in.tellg()) - 1;
    if ((next < '0' || next > '9') && next != '+' && next != '-')
        throw IllegalSymbolException(pos);
    if (next < '0' || next > '9')
        throw MissingOperandException(pos);
    return next - '0';
}

bool get_signal(istringstream &in)
{
    char next;
    in >> next;
    if (next != '+' && next != '-')
    {
        if (next >= '0' && next <= '9')
            throw MissingOperatorException(static_cast<int>(in.tellg()) - 1);
        else
            throw IllegalSymbolException(static_cast<int>(in.tellg()) - 1);
    }
    switch (next)
    {
    case '+':
        return true;
    case '-':
        return false;
    }
}

struct calculator
{
    int calculate(string str)
    {
        if (str.empty())
            throw EmptyExpressionException();

        istringstream in(str);

        int value = 0;

        value = get_number(in);
        while (!in.eof())
        {
            auto signal = get_signal(in);
            // if (in.eof())
            //     throw MissingOperandException(str.length());
            auto incr = get_number(in);
            value += signal ? incr : -incr;
        }
        return value;
    }
};