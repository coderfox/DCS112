#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

int main()
{
    int a, b;
    cin >> a >> b;
    long double d = static_cast<long double>(a) / b;
    int c = floor(d);
    cout << c << endl
         << fixed << setprecision(2) << d << endl;
    return 0;
}