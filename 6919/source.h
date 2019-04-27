#include <cmath>

using namespace std;

inline double pow2(double base)
{
  return base * base;
}

class Point
{
private:
  double x, y;

public:
  Point();
  Point(double xv, double yv);
  Point(Point &pt);
  double getx();
  double gety();
};

class Circle : Point
{
private:
  double r;

public:
  Circle();
  Circle(double x, double y, double r);
  int position(Point &pt);
};

class Rectangle : Point
{
private:
  Point pt_rb;

public:
  Rectangle();
  Rectangle(double x1, double x2, double y1, double y2);
  int position(Point &pt);
};

Point::Point() : x(0), y(0)
{
}
Point::Point(double xv, double yv) : x(xv), y(yv)
{
}
Point::Point(Point &pt) : Point(pt.x, pt.y)
{
}
double Point::getx()
{
  return x;
}
double Point::gety()
{
  return y;
}

Circle::Circle() : Point(0, 0), r(0)
{
}
Circle::Circle(double x, double y, double r) : Point(x, y), r(r)
{
}
int Circle::position(Point &pt)
{
  auto dist = sqrt(pow2(getx() - pt.getx()) + pow2(gety() - pt.gety()));
  if (dist < r)
    // 假如点A落在圆内或是矩形内，则该函数返回-1；
    return -1;
  else if (dist == r)
    // 如果落在圆上或是矩形上，则返回0,；
    return 0;
  else
    // 如果落在外面，则返回1。
    return 1;
}

Rectangle::Rectangle() : Point(0, 0), pt_rb(0, 0)
{
}
Rectangle::Rectangle(double x1, double y1, double x2, double y2) : Point(x1, y1), pt_rb(x2, y2)
{
}
int Rectangle::position(Point &pt)
{
  if (getx() < pt.getx() && pt.getx() < pt_rb.getx() && gety() < pt.gety() && pt.gety() < pt_rb.gety())
    return -1;
  else if ((getx() == pt.getx() && gety() == pt.gety()) ||
           (pt_rb.getx() == pt.getx() && pt_rb.gety() == pt.gety()))
    return 0;
  else
    return 1;
}