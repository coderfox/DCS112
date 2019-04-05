#include <algorithm>
#include <cstdlib>
#include "array.hpp"

using std::copy;

void swap(int *a, int *b)
{
    if (*a != *b)
    {
        *a ^= *b;
        *b ^= *a;
        *a ^= *b;
    }
}
int partion(int *num, int p, int q)
{
    int pivot = num[p];
    int r = p;
    for (int i = p + 1; i <= q; i++)
    {
        if (num[i] < pivot)
        {
            swap(&num[i], &num[r++]);
            swap(&num[i], &num[r]);
        }
    }
    return r;
}
void quick_sort(int *num, int p, int q)
{
    if (p < q)
    {
        int r = partion(num, p, q);
        quick_sort(num, p, r - 1);
        quick_sort(num, r + 1, q);
    }
}

array::array(size_t size) : _size(size)
{
    _data = new data_type[size];
}
array::~array()
{
    delete[] _data;
}
array::size_t array::max_size()
{
    return _size;
}
array::data_type &array::at(const data_type &i)
{
    return _data[i];
}
array::data_type &array::front()
{
    return _data[0];
}
array::data_type &array::back()
{
    return _data[_size - 1];
}
array::pointer array::data()
{
    return reinterpret_cast<array::pointer>(_data);
}
void array::fill(const data_type &value)
{
    for (size_t i = 0; i < _size; i++)
    {
        _data[i] = value;
    }
}
void array::resize(int newSize)
{
    pointer old = _data;
    _data = new data_type[newSize];
    copy(old, old + _size, _data);
    delete[] old;
    _size = newSize;
}
void array::sort(int from, int to)
{
    quick_sort(_data, from, to - 1);
}
