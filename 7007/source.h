#include <cmath>

using std::sqrt;

inline double pow2(double x)
{
    return x * x;
}

class MyPoint
{
private:
    double x, y;

public:
    // The no-arg constructor that contruccts a point with coordinates(0,0)
    MyPoint() : x(0), y(0)
    {
    }

    MyPoint(double x, double y) : x(x), y(y)
    {
    }
    double getX() const
    {
        return x;
    }
    double getY() const
    {
        return y;
    }

    //display the distance between two points in two-dimensional space.
    double distance(const MyPoint &point)
    {
        return sqrt(pow2(getX() - point.getX()) + pow2(getY() - point.getY()));
    }
};

class ThreeDPoint : public MyPoint
{
private:
    double z;

public:
    // The no-arg constructor that contruccts a point with coordinates(0,0,0)
    ThreeDPoint() : MyPoint(), z(0)
    {
    }

    ThreeDPoint(double x, double y, double z) : MyPoint(x, y), z(z)
    {
    }
    double getZ() const
    {
        return z;
    }

    //display the distance between two points in Three-dimensional space.
    double distance(const ThreeDPoint &point)
    {
        return sqrt(pow2(getX() - point.getX()) + pow2(getY() - point.getY()) + pow2(z - point.z));
    }
};
