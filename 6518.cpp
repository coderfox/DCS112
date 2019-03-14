#include <iostream>
#include <iomanip>

using namespace std;

const double pi = 3.14159265358979;

int main()
{
    long double radius;
    cin >> radius;
    cout << fixed << setprecision(8) << radius * radius * pi << endl;
    return 0;
}