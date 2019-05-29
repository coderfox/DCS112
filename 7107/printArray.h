#include <iostream>
#include <algorithm>

using namespace std;

template <typename T, std::size_t N>
void printValues(T (&arr)[N])
{
    copy(arr, arr + N, ostream_iterator<T>(cout, "\n"));
}
