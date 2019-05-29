#include <string>
#include <cmath>

using std::sqrt;
using std::string;

class GeometricObject
{
public:
    GeometricObject(string color, bool filled)
    {
        this->color = color;
        this->filled = filled;
    }

    string getColor() const
    {
        return color;
    }
    void setColor(string color)
    {
        this->color = color;
    }
    bool isFilled() const
    {
        return filled;
    }
    void setFilled(bool filled)
    {
        this->filled = filled;
    }
    string toString() const
    {
        return "Geometric object color " + color +
               " filled " + ((filled) ? "true" : "false");
    }

private:
    string color;
    bool filled;
};

// Design a class named Triangle that extends GeometricObject class.
// The class contains:
// Three double data fields named side1, side2, and side3 with default values 1.0 to denote three sides of the triangle.
// A no-arg constructor that creates a default triangle with color = "blue", filled = true.
// A constructor that creates a triangle with the specified side1, side2, side3 and color = "blue", filled = true.
// The accessor functions for all three data fields, named getSide1(), getSide2(), getSide3().
// A function named getArea() that returns the area of this triangle.
// A function named getPerimeter() that returns the perimeter of the triangle.
class Triangle : public GeometricObject
{
    double side1, side2, side3;

public:
    Triangle() : GeometricObject("blue", true), side1(1.0), side2(1.0), side3(1.0)
    {
    }
    Triangle(double side1, double side2, double side3) : GeometricObject("blue", true), side1(side1), side2(side2), side3(side3)
    {
    }
    double getSide1()
    {
        return side1;
    }
    double getSide2()
    {
        return side2;
    }
    double getSide3()
    {
        return side3;
    }
    double getArea()
    {
        double p = getPerimeter() / 2;
        return sqrt(p * (p - side1) * (p - side2) * (p - side3));
    }
    double getPerimeter()
    {
        return side1 + side2 + side3;
    }
};