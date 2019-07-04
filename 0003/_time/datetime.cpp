#include "datetime.hpp"
#include <sstream>
#include <iomanip>
#include "utils.hpp"

using namespace std;

DateTime::DateTime() : DateTime(0, 0, 0, 0, 0, 0)
{
}

DateTime::DateTime(unsigned int year,
                   unsigned int month,
                   unsigned int day,
                   unsigned int hour,
                   unsigned int minute,
                   unsigned int second) : Date(year, month, day)
{
    _hour = hour;
    _minute = minute;
    _second = second;
}

DateTime::DateTime(std::string datetime)
{
    stringstream ss(datetime);
    ss >> *this;
}

bool DateTime::operator==(const DateTime &rhs) const
{
    return Date::operator==(rhs) &&
           _hour == rhs._hour &&
           _minute == rhs._minute &&
           _second == rhs._second;
}

unsigned int DateTime::hour() const
{
    return _hour;
}

unsigned int DateTime::hour(unsigned int value)
{
    return _hour = value;
}

unsigned int DateTime::minute() const
{
    return _minute;
}

unsigned int DateTime::minute(unsigned int value)
{
    return _minute = value;
}

unsigned int DateTime::second() const
{
    return _second;
}

unsigned int DateTime::second(unsigned int value)
{
    return _second = value;
}

void DateTime::write(std::ostream &output) const
{
    Date::write(output);
    ::write(output, _hour);
    ::write(output, _minute);
    ::write(output, _second);
}
void DateTime::read(std::istream &input)
{
    Date::read(input);
    ::read(input, _hour);
    ::read(input, _minute);
    ::read(input, _second);
}

std::ostream &operator<<(std::ostream &out, const DateTime &datetime)
{
    out << static_cast<const Date &>(datetime) << ' '
        << setw(2) << setfill('0') << datetime._hour << ':'
        << setw(2) << setfill('0') << datetime._minute << ':'
        << setw(2) << setfill('0') << datetime._second;
    return out;
}

std::istream &operator>>(std::istream &in, DateTime &datetime)
{
    char chr;
    in >> static_cast<Date &>(datetime) >>
        datetime._hour >> chr >>
        datetime._minute >> chr >>
        datetime._second;
    return in;
}
