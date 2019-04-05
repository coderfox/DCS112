#include "SingleDog.h"
#include <cstring>

int SingleDog::count = 0;

SingleDog::SingleDog(int id_, char *name_) : id(id_)
{
    name = static_cast<char *>(calloc(strlen(name_) + 1, sizeof(char)));
    strcpy(name, name_);
    count++;
}

SingleDog::SingleDog(const SingleDog &other) : SingleDog(other.id, other.name)
{
}

SingleDog::~SingleDog()
{
    free(name);
    count--;
}

int SingleDog::getCount()
{
    return count;
}