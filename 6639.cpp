#include <cmath>

using std::sqrt;

inline double bpow(double value)
{
    return value * value;
}

class Rectangle
{
  private:
    double width, height;

  public:
    Rectangle() : width(1), height(1) {}
    Rectangle(double width, double height) : width(width), height(height) {}
    double getWidth() { return width; }
    double getHeight() { return height; }
    void setWidth(double width) { this->width = width; }
    void setHeight(double height) { this->height = height; }
    double getArea() // { return 0.5 * width * height; }
    {
        return width * height;
    }
    double getPerimeter()
    {
        // return sqrt(bpow(width / 2) + bpow(height)) * 2;
        return (width + height) * 2;
    }
};

// =====================
// framework source code
// =====================
#include <iostream>
#include <iomanip>

using namespace std;
void print(Rectangle &obj)
{
    cout << fixed << setprecision(2)
         << obj.getWidth() << " " << obj.getHeight() << " " << obj.getArea() << " " << obj.getPerimeter() << endl;
}

int main()
{
    Rectangle obj1;
    print(obj1);
    obj1.setWidth(4);
    obj1.setHeight(40);
    print(obj1);
    Rectangle obj2(3.5, 35.9);
    print(obj2);

    return 0;
}
