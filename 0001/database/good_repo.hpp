#ifndef H_GOOD_REPO
#define H_GOOD_REPO

#include <vector>
#include <map>
#include <string>
#include <list>
#include "good.hpp"
#include "storable.hpp"

class GoodRepository : public IStorable
{
public:
  typedef std::map<std::string, Good> Map;

  void save(const Good &good);
  void remove(const Good &good);
  bool contains(const std::string &name);
  Good &find_by_name(const std::string &name);
  std::list<Good> get_all() const;
  GoodRepository();

  void write(std::ostream &output) const;
  void read(std::istream &input);

private:
  Map _goods;
};

#endif
