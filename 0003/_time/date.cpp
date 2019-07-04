#include "date.hpp"
#include "utils.hpp"
#include <sstream>
#include <iomanip>

using namespace std;

Date::Date() : Date(0, 0, 0)
{
}

Date::Date(unsigned int year, unsigned int month, unsigned int day)
{
    _year = year;
    _month = month;
    _day = day;
}

Date::Date(string date)
{
    stringstream ss(date);
    ss >> *this;
}

bool Date::operator==(const Date &rhs) const
{
    return _year == rhs._year &&
           _month == rhs._month &&
           _day == rhs._day;
}

unsigned int Date::year() const
{
    return _year;
}

unsigned int Date::year(unsigned int value)
{
    return _year = value;
}

unsigned int Date::month() const
{
    return _month;
}

unsigned int Date::month(unsigned int value)
{
    return _month = value;
}

unsigned int Date::day() const
{
    return _day;
}

unsigned int Date::day(unsigned int value)
{
    return _day = value;
}

void Date::write(ostream &output) const
{
    ::write(output, _year);
    ::write(output, _month);
    ::write(output, _day);
}

void Date::read(istream &input)
{
    ::read(input, _year);
    ::read(input, _month);
    ::read(input, _day);
}

ostream &operator<<(ostream &out, const Date &date)
{
    out << setw(4) << setfill('0') << date._year << '/'
        << setw(2) << setfill('0') << date._month << '/'
        << setw(2) << setfill('0') << date._day;
    return out;
}

istream &operator>>(istream &in, Date &date)
{
    char chr;
    in >> date._year >> chr >> date._month >> chr >> date._day;
    return in;
}
