#pragma once
#include <string>
#include <istream>
#include <ostream>
#include "storable.hpp"

class Date : public IStorable
{
private:
    unsigned int _year;
    unsigned int _month;
    unsigned int _day;

public:
    Date();
    Date(unsigned int year, unsigned int month, unsigned int day);
    Date(std::string date);

    bool operator==(const Date &rhs) const;

    unsigned int year() const;
    unsigned int year(unsigned int value);
    unsigned int month() const;
    unsigned int month(unsigned int value);
    unsigned int day() const;
    unsigned int day(unsigned int value);

    void write(std::ostream &output) const;
    void read(std::istream &input);

    friend std::ostream &operator<<(std::ostream &out, const Date &date);
    friend std::istream &operator>>(std::istream &in, Date &date);
};
