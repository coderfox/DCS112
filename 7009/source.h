class Point
{
    int x, y;

public:
    Point(int x, int y) : x(x), y(y)
    {
    }
    void Move(int x, int y)
    {
        this->x += x;
        this->y += y;
    }
    int Getx() const
    {
        return x;
    }
    int Gety() const
    {
        return y;
    }
};

class Rectangle : public Point
{
    int width, length;

public:
    Rectangle(int x, int y, int length, int width) : Point(x, y), width(width), length(length)
    {
    }
    int Getlength()
    {
        return length;
    }
    int Getwidth()
    {
        return width;
    }
    int Getarea()
    {
        return width * length;
    }
};