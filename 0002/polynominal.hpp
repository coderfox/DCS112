#include <map>
#include <list>

class Polynominal
{
  private:
    std::map<unsigned int, int> _coefficients;

  public:
    Polynominal();
    Polynominal(std::list<std::pair<unsigned int, int>>);
    int &operator[](unsigned int rhs);
};
