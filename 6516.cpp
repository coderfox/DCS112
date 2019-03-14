#include <iostream>

using namespace std;
int sum(int a = 0, int b = 100, int c = 0)
{
    return a + b + c;
}

int main()
{
    cout << sum() << endl;
    cout << sum(6) << endl;
    cout << sum(6, 10) << endl;
    cout << sum(6, 10, 20) << endl;

    return 0;
}
