#pragma once
#include <vector>
#include <map>
#include <string>
#include <list>
#include "identifiable.hpp"
#include "storable.hpp"
#include "utils.hpp"
#include "exceptions.hpp"

template <class T>
class Repository final : public IStorable
{
    static_assert(std::is_convertible<T *, IStorable *>::value, "T must inherit IStorable as public");
    static_assert(std::is_convertible<T *, IIdentifiable *>::value, "T must inherit IIdentifiable as public");

public:
    typedef std::map<size_t, std::shared_ptr<T>> Map;

    Repository();

    template <typename... _Args>
    T &insert(_Args... __args);
    T &insert(T data);
    // void save(const T &data);
    void remove(const T &data);
    bool contains(const size_t &id);
    T &find_by_id(const size_t &id);
    std::list<std::shared_ptr<T>> get_all() const;

    void write(std::ostream &output) const;
    void read(std::istream &input);

private:
    Map _datas;
    size_t _counter = 0;
};

template <typename T>
template <typename... _Args>
T &Repository<T>::insert(_Args... __args)
{
    T data(__args...);
    return insert(data);
}

template <class T>
T &Repository<T>::insert(T data)
{
    data.set_id(_counter);
    return *(_datas[data.id()] = std::make_shared<T>(data));
}

/* template <class T>
void Repository<T>::save(const T &data)
{
    if (data.id() == std::numeric_limits<size_t>::max())
        throw InvalidIdentifier();
    _datas[data.id()] = data;
} */

template <class T>
void Repository<T>::remove(const T &data)
{
    _datas.erase(data.id());
}

template <class T>
bool Repository<T>::contains(const size_t &id)
{
    return _datas.count(id) >= 1;
}

template <class T>
T &Repository<T>::find_by_id(const size_t &id)
{
    if (!contains(id))
        throw EntityNotExists();
    return *_datas[id];
}

template <class T>
std::list<std::shared_ptr<T>> Repository<T>::get_all() const
{
    std::list<std::shared_ptr<T>> valueList;
    transform(_datas.begin(), _datas.end(), back_inserter(valueList),
              [](const typename Repository<T>::Map::value_type &val) { return val.second; });
    return valueList;
}

template <class T>
Repository<T>::Repository()
{
    _datas = Map();
}

template <class T>
void Repository<T>::write(std::ostream &output) const
{
    ::write(output, _datas.size());
    ::write(output, _counter);
    for (auto iter : _datas)
    {
        (iter).second->write(output);
    }
}

template <class T>
void Repository<T>::read(std::istream &input)
{
    size_t cnt = 0;
    ::read(input, cnt);
    ::read(input, _counter);
    for (size_t i = 0; i < cnt; i++)
    {
        T data;
        data.read(input);
        insert(data);
    }
}
