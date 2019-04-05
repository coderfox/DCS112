#include <iostream>
using namespace std;

class Double
{
   private:
     double data;

   public:
     Double();
     Double(double data);
     double getDouble() const;
     void setDouble(double data);
     void add(const Double &other);
     void sub(const Double &other);
     void mul(const Double &other);
     bool div(const Double &other);
};

// #include "Double.h"

Double::Double() : data(0)
{
}
Double::Double(double data) : data(data)
{
}
double Double::getDouble() const
{
     return data;
}
void Double::setDouble(double data)
{
     this->data = data;
}
void Double::add(const Double &other)
{
     data += other.getDouble();
}
void Double::sub(const Double &other)
{
     data -= other.getDouble();
}
void Double::mul(const Double &other)
{
     data *= other.getDouble();
}
bool Double::div(const Double &other)
{
     if (other.getDouble() == 0)
          return false;
     data /= other.getDouble();
     return true;
}