#include <ctime>
#include <iostream>

using std::cout;

class Time
{
    int Hour, Minute, Second;

  public:
    Time();
    Time(int totalSeconds);
    int getHour();
    int getMinute();
    int getSecond();
};

Time::Time() : Time(static_cast<int>(std::time(nullptr)))
{
}

Time::Time(int epoch)
{
    int today_seconds = epoch % (24 * 60 * 60);
    Hour = today_seconds / (60 * 60);
    Minute = today_seconds % (60 * 60) / 60;
    Second = today_seconds % 60;
}

int Time::getHour() { return Hour; }
int Time::getMinute() { return Minute; }
int Time::getSecond() { return Second; }

int main()
{
    Time time = Time();
    cout << time.getHour() << ' ' << time.getMinute() << ' ' << time.getSecond();
    return 0;
}