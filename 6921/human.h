#ifndef HUMAN
#define HUMAN

#include <string>
#include <iostream>
#include "animal.h"

using namespace std;

class human : public animal
{
  private:
    string _name;

  public:
    human(string name);
    void greeting() const;
};

human::human(string name) : animal(string("Human"), 2), _name(name)
{
}
void human::greeting() const
{
    cout << "Hello, I'm " << _name << "." << endl;
}

#endif