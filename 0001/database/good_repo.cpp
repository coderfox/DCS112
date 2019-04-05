#include <exception>
#include <list>
#include <algorithm>
#include <iostream>
#include "good_repo.hpp"

using namespace std;

void GoodRepository::save(const Good &good)
{
    if (good.get_count() > 0)
        _goods[good.get_name()] = good;
}
void GoodRepository::remove(const Good &good)
{
    _goods.erase(good.get_name());
}
bool GoodRepository::contains(const string &name)
{
    return _goods.count(name) >= 1;
}
Good &GoodRepository::find_by_name(const string &name)
{
    return _goods[name];
}
list<Good> GoodRepository::get_all() const
{
    list<Good> valueList;
    transform(_goods.begin(), _goods.end(), back_inserter(valueList),
              [](const map<string, Good>::value_type &val) { return val.second; });
    return valueList;
}
GoodRepository::GoodRepository()
{
    _goods = Map();
}

void GoodRepository::write(ostream &output) const
{
    size_t cnt = _goods.size();
    output.write(reinterpret_cast<const char *>(&cnt), sizeof(cnt));
    for (auto iter = _goods.begin(); iter != _goods.end(); iter++)
    {
        (*iter).second.write(output);
    }
}
void GoodRepository::read(istream &input)
{
    size_t cnt = 0;
    input.read(reinterpret_cast<char *>(&cnt), sizeof(cnt));
    for (size_t i = 0; i < cnt; i++)
    {
        auto good = Good();
        good.read(input);
        save(good);
    }
}