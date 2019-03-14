#include <cstdlib>
#include <iostream>

using namespace std;

int *doubleCapacity(int *list, int size)
{
    int *ret = new int[size * 2];
    for (int i = 0; i < size; i++)
    {
        ret[i] = list[i];
    }
    return ret;
}

int main()
{
    int list[5] = {1, 2, 3, 4, 5};
    int *newlist = doubleCapacity(list, 5);
    for (int i = 0; i < 2 * 5; i++)
        cout << *(newlist + i) << " ";
    return 0;
}