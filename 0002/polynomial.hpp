#include <map>
#include <list>
#include <initializer_list>
#include <ostream>
#include <functional>

class Polynomial
{
  private:
    std::map<unsigned int, int, std::greater<>> _coefficients;

    void garbage_collect();

  public:
    Polynomial();
    Polynomial(std::list<std::pair<unsigned int, int>> list);
    Polynomial(std::initializer_list<int> list);

    int &operator[](unsigned int rhs);
    int get(unsigned int power) const;

    bool operator==(const Polynomial &rhs) const;
    Polynomial operator-() const;
    Polynomial operator+(const Polynomial &rhs) const;
    Polynomial operator-(const Polynomial &rhs) const;
    Polynomial operator*(const Polynomial &rhs) const;
    Polynomial derive() const;
    int eval(int x) const;

    std::string to_string() const;
    friend std::ostream &operator<<(std::ostream &ostream, const Polynomial &poly);
};
