#include <algorithm>
#include "set.hpp"

using namespace std;

Set::Set()
{
    size = 0;
}
Set::Set(int *m, int s) : Set()
{
    copy_if(m, m + s, members, [this](const int e) {
        return (!isInSet(e) && ++size);
    });
}
bool Set::append(int e)
{
    if (!isInSet(e))
    {
        members[size++] = e;
        return true;
    }
    return false;
}
bool Set::remove(int e)
{
    int *ptr = find(members, members + size, e);
    if (ptr == members + size)
        return false;
    if (ptr != members + size - 1)
        swap(*ptr, *(members + size - 1));
    size--;
    return true;
}
bool Set::isEmptySet()
{
    return size == 0;
}
int *Set::getMembers()
{
    return members;
}
int Set::getSize()
{
    return size;
}
bool Set::isInSet(int e)
{
    return find(members, members + size, e) != members + size;
}
