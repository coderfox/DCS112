#include <iostream>

using namespace std;

int main()
{
    int num;
    cin >> num;
    int sum = 0;
    for (int i = 0; i < 3; i++)
    {
        sum += num % 10;
        num /= 10;
    }
    cout << sum << endl;
    return 0;
}