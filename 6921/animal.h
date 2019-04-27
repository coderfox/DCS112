#ifndef ANIMAL
#define ANIMAL

#include <string>
#include <iostream>

using namespace std;

class animal
{
  private:
    string _species;
    int _eyes;

  public:
    animal(string species, int eyes);
    void print_eyes();
};

animal::animal(string species, int eyes) : _species(species), _eyes(eyes)
{
}
void animal::print_eyes()
{
    cout << _species << " has " << _eyes << " eyes." << endl;
}

#endif
