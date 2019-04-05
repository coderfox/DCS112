#include <cmath>
using std::sqrt;

class MyPoint
{
  private:
    double x, y;

  public:
    MyPoint()
    {
        x = 0;
        y = 0;
    }
    MyPoint(double x, double y)
    {
        this->x = x;
        this->y = y;
    }
    double getX() { return x; }
    double getY() { return y; }
    double distance(MyPoint &point)
    {
        return sqrt(
            (this->x - point.x) * (this->x - point.x) +
            (this->y - point.y) * (this->y - point.y));
    }
};

// =====================
// framework source code
// =====================
#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>
using namespace std;

int main()
{
    MyPoint p1, p2;
    cout << fixed << setprecision(2)
         << p1.getX() << " " << p1.getY() << " "
         << p1.distance(p2) << endl;
    double x, y;
    while (cin >> x >> y)
    {
        MyPoint p3 = MyPoint(x, y);
        cout << fixed << setprecision(2)
             << p3.getX() << " " << p3.getY() << " "
             << p3.distance(p1) << endl;
    }
    return 0;
}
