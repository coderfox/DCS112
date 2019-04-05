#include <iostream>
#include "good.hpp"

std::string Good::get_name() const
{
    return _name;
}
unsigned int Good::get_count() const
{
    return _count;
}
void Good::set_name(std::string name)
{
    _name = name;
}
void Good::set_count(unsigned int count)
{
    _count = count;
}
Good::Good()
{
    _name = std::string();
    _count = 0;
}
Good::Good(std::string name, unsigned int count = 0)
{
    _name = name;
    _count = count;
}

void Good::write(std::ostream &output) const
{
    output.write(_name.c_str(), sizeof(char) * (_name.size() + 1));
    output.write(reinterpret_cast<const char *>(&_count), sizeof(_count));
}
void Good::read(std::istream &input)
{
    std::getline(input, _name, '\0');
    input.read(reinterpret_cast<char *>(&_count), sizeof(_count));
}
