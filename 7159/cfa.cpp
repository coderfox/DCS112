#include <iostream>

using namespace std;

#define OUTPUT(A, B, C)    \
    if (flag[0])           \
        cout << A << endl; \
    if (flag[1])           \
        cout << B << endl; \
    if (flag[2])           \
        cout << C << endl; \
    break;

int main()
{
    int moves, position;
    cin >> moves >> position;
    bool flag[3] = {false};
    flag[position] = true;
    switch (moves % 6)
    {
    case 0:
        break;
    case 1:
        OUTPUT(1, 0, 2);
    case 2:
        OUTPUT(1, 2, 0);
    case 3:
        OUTPUT(2, 1, 0);
    case 4:
        OUTPUT(2, 0, 1);
    case 5:
        OUTPUT(0, 2, 1);
    }
    return 0;
}