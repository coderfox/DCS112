#ifndef H_STORABLE
#define H_STORABLE

#include <iostream>

class IStorable
{
public:
  virtual void write(std::ostream &output) const = 0;
  virtual void read(std::istream &input) = 0;
};

#endif
