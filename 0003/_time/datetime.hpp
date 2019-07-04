#include "date.hpp"

class DateTime : public Date
{
private:
    unsigned int _hour;
    unsigned int _minute;
    unsigned int _second;

public:
    DateTime();
    DateTime(unsigned int year, unsigned int month, unsigned int day,
             unsigned int hour, unsigned int minute, unsigned int second);
    DateTime(std::string datetime);

    bool operator==(const DateTime &rhs) const;

    unsigned int hour() const;
    unsigned int hour(unsigned int value);
    unsigned int minute() const;
    unsigned int minute(unsigned int value);
    unsigned int second() const;
    unsigned int second(unsigned int value);

    void write(std::ostream &output) const;
    void read(std::istream &input);

    friend std::ostream &operator<<(std::ostream &out, const DateTime &datetime);
    friend std::istream &operator>>(std::istream &in, DateTime &datetime);
};
