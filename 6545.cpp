#include <iostream>

using namespace std;

int main()
{
    int a, b;
    cin >> a >> b;
    cout << a + b << endl;
    cout << a - b << endl;
    cout << a * b << endl;
    cout << ((b == 0) ? 0 : (static_cast<double>(a) / b)) << endl;
    return 0;
}