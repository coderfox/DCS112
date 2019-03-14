#include <iostream>

using namespace std;

int main()
{
    int m, n;
    cin >> m >> n;
    int **arr = new int *[m];
    for (int i = 0; i < m; i++)
    {
        arr[i] = new int[n];
    }
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            int num;
            cin >> num;
            arr[i][j] = num;
        }
    }
    for (int i = 0; i < m; i++)
    {
        cout << arr[i][0];
        for (int j = 1; j < n; j++)
        {
            cout << ' ' << arr[i][j];
        }
        cout << endl;
    }
    for (int i = 0; i < m; i++)
    {
        delete[] arr[i];
    }
    delete[] arr;
    return 0;
}