#ifndef H_GOOD
#define H_GOOD

#include <string>
#include "storable.hpp"

class Good final : public IStorable
{
public:
  std::string get_name() const;
  unsigned int get_count() const;
  void set_name(std::string name);
  void set_count(unsigned int count);
  Good();
  Good(std::string name);
  Good(std::string name, unsigned int count);

  void write(std::ostream &output) const;
  void read(std::istream &input);

private:
  std::string _name;
  unsigned int _count;
};

#endif
