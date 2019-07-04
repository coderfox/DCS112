#include "utils.hpp"

using namespace std;

template <>
void write(std::ostream &out, const std::string &str)
{
    out.write(str.c_str(), sizeof(char) * (str.size() + 1));
}

template <>
void read(std::istream &in, std::string &str)
{
    getline(in, str, '\0');
}
