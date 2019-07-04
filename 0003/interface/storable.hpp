#pragma once

#include <iostream>

class IStorable
{
public:
    virtual void write(std::ostream &output) const = 0;
    virtual void read(std::istream &input) = 0;
};
