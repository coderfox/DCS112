#include <iostream>

using namespace std;

int *sort(const int *const array, int size);

int main()
{
    int arr[] = {8, 7, 6, 5, 4, 3, 2, 1};
    int *new_arr = sort(arr, 8);
    for (int i = 0; i < 8; i++)
    {
        cout << new_arr[i] << " ";
    }
    cout << endl;
    delete new_arr;
    return 0;
}