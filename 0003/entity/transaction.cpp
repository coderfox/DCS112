#include "transaction.hpp"
#include "utils.hpp"
#include <ctime>
#include <limits>

using namespace std;

Transaction::Transaction() : Transaction(0, "")
{
}

Transaction::Transaction(cent_diff_t difference, string note) : _difference(difference), _note(note)
{
    _id = numeric_limits<size_t>::max();
    _time = ::time(nullptr);
}

Transaction::Transaction(cent_t previous, cent_t current, string note) : Transaction(current - previous, note)
{
}

size_t Transaction::id()
{
    return _id;
}

/* size_t Transaction::id(size_t value)
{
    return _id = value;
} */

cent_diff_t Transaction::difference()
{
    return _difference;
}

cent_diff_t Transaction::difference(cent_diff_t value)
{
    return _difference = value;
}

time_t Transaction::time()
{
    return _time;
}

time_t Transaction::time(time_t value)
{
    return _time = value;
}

std::string Transaction::note()
{
    return _note;
}

std::string Transaction::note(std::string value)
{
    return _note = value;
}

void Transaction::write(std::ostream &output) const
{
    ::write(output, _id);
    ::write(output, _difference);
    ::write(output, _time);
    ::write(output, _note);
}

void Transaction::read(std::istream &input)
{
    ::read(input, _id);
    ::read(input, _difference);
    ::read(input, _time);
    ::read(input, _note);
}

size_t Transaction::id() const
{
    return _id;
}

void Transaction::id(size_t value)
{
    _id = value;
}
