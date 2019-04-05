#include <string>
using std::string;

class Fan
{
  public:
    Fan() : speed(1), is_on(false), radius(5), color("blue") {}
    int getSpeed() { return speed; }
    void setSpeed(int value) { speed = value; }
    bool isOn() { return is_on; }
    void setOn(bool value) { is_on = value; }
    double getRadius() { return radius; }
    void setRadius(double value) { radius = value; }
    string getColor() { return color; }
    void setColor(string value) { color = value; }

  private:
    int speed;
    bool is_on;
    double radius;
    string color;
};