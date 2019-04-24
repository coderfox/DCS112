#include <iostream>
#include "IntegerSet.h"

using namespace std;

#define ARRAY_END 101

IntegerSet::IntegerSet(int s[], int l) : IntegerSet() // constructor that takes an initial set
{
    for (int *ptr = s; ptr < s + l; ptr++)
    {
        insertElement(*ptr);
    }
}
IntegerSet IntegerSet::unionOfSets(const IntegerSet &rhs)
{
    IntegerSet ret;
    for (const int *ptr = set; ptr < set + ARRAY_END; ptr++)
    {
        if (*ptr == 1)
            ret.set[ptr - set] = 1;
    }
    for (const int *ptr = rhs.set; ptr < rhs.set + ARRAY_END; ptr++)
    {
        if (*ptr == 1)
            ret.set[ptr - rhs.set] = 1;
    }
    return ret;
}
IntegerSet IntegerSet::intersectionOfSets(const IntegerSet &rhs)
{
    IntegerSet ret;
    for (int i = 0; i < ARRAY_END; i++)
    {
        if (set[i] == 1 && rhs.set[i] == 1)
            ret.set[i] = 1;
    }
    return ret;
}
void IntegerSet::emptySet() // set all elements of set to 0
{
    for (int *ptr = set; ptr < set + ARRAY_END; ptr++)
    {
        *ptr = 0;
    }
}

void IntegerSet::insertElement(int element)
{
    if (element < 0 || element >= ARRAY_END)
        cout << "Invalid insert attempted!" << endl;
    set[element] = 1;
}
void IntegerSet::deleteElement(int element)
{
    set[element] = 0;
}

bool IntegerSet::isEqualTo(const IntegerSet &rhs) const
{
    for (int i = 0; i < ARRAY_END; i++)
    {
        if (set[i] != rhs.set[i])
            return false;
    }
    return true;
}
