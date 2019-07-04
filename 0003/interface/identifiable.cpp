#include <limits>
#include "identifiable.hpp"

using namespace std;

IIdentifiable::~IIdentifiable() {}

inline size_t max(size_t a, size_t b)
{
    return a > b ? a : b;
}

void IIdentifiable::set_id(size_t &counter)
{
    if (id() == numeric_limits<size_t>::max())
        id(counter++);
    else
        counter = max(id() + 1, counter);
}
