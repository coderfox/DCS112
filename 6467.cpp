#include <iostream>

using namespace std;

int main()
{
    int curr_sum = 0;
    for (int i = 0; i < 4; i++)
    {
        int num;
        cin >> num;
        curr_sum += num;
    }
    cout << 15 - curr_sum << endl;
    return 0;
}