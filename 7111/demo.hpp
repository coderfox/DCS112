#include <iostream>

using namespace std;

#define PRINT(S) \
    cout << S;

template <typename T>
void demoFunc(const T v1, const T v2)
{
    PRINT("the first generic version of demoFunc()\nthe arguments: ");
    cout << v1 << ' ' << v2 << endl;
}

template <typename T>
void demoFunc(const T v)
{
    PRINT("the second generic version of demoFunc()\nthe argument: ");
    cout << v << endl;
}

void demoFunc(const int v1, const int v2)
{
    PRINT("the ordinary version of demoFunc()\nthe arguments: ");
    cout << v1 << ' ' << v2 << endl;
}
