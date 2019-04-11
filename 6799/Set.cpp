#include "Set.hpp"
#include <algorithm>

using namespace std;

Set::Set() : size(0)
{
}
Set::Set(int *m, int s)
{
    copy(m, m + s, members);
    size = s;
}
Set::Set(Set const &s)
{
    copy(s.members, s.members + s.size, members);
    size = s.size;
}

bool Set::append(int e)
{
    if (isInSet(e))
    {
        return false;
    }
    else
    {
        members[size++] = e;
        return true;
    }
}
bool Set::remove(int e)
{
    if (!isInSet(e))
    {
        return false;
    }
    else
    {
        swap(*find(members, members + size, e), members[size - 1]);
        size--;
        return true;
    }
}
bool Set::isEmptySet()
{
    return size == 0;
}
bool Set::isInSet(int e)
{
    return find(members, members + size, e) != members + size;
}

Set Set::operator&(const Set &s)
{
    Set set;
    for (int *cur = members; cur < members + size; cur++)
    {
        if (const_cast<Set &>(s).isInSet(*cur))
        {
            set.append(*cur);
        }
    }
    return set;
}
Set Set::operator|(const Set &s)
{
    Set set = *this;
    for (const int *cur = reinterpret_cast<const int *>(s.members); cur < s.members + s.size; cur++)
    {
        set.append(*cur);
    }
    return set;
}
Set Set::operator-(const Set &s)
{
    Set set = *this;
    for (int *cur = set.members; cur < set.members + set.size; cur++)
    {
        if (const_cast<Set &>(s).isInSet(*cur))
        {
            set.remove(*cur);
        }
    }
    return set;
}
Set Set::operator+(const Set &s)
{
    Set lhs = *this;
    Set rhs = s;
    return (lhs - rhs) | (rhs - lhs);
}

int *Set::getMembers()
{
    return members;
}
int Set::getSize()
{
    return size;
}
