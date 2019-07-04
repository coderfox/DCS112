#pragma once
#include <istream>
#include <ostream>
#include <string>
#include <vector>

template <typename T>
void write(std::ostream &out, const T &data)
{
    out.write(reinterpret_cast<const char *>(&data), sizeof(data));
}

template <typename T>
void read(std::istream &in, T &data)
{
    in.read(reinterpret_cast<char *>(&data), sizeof(data));
}

template <>
void write(std::ostream &out, const std::string &str);

template <>
void read(std::istream &in, std::string &str);

#define DEFN_GETTER_SETTER(TYPE, FIELD) \
    TYPE FIELD() const;                 \
    TYPE FIELD(TYPE value);

#define IMPL_GETTER_SETTER(CLASS, TYPE, FIELD) \
    TYPE CLASS::FIELD() const                  \
    {                                          \
        return _##FIELD;                       \
    }                                          \
    TYPE CLASS::FIELD(TYPE value)              \
    {                                          \
        return _##FIELD = value;               \
    }
