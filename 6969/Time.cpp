#include "Time.h"
#include <iostream>
#include <iomanip>

using namespace std;

void Time::Set(int hours, int minutes, int seconds)
{
    hrs = hours;
    mins = minutes;
    secs = seconds;
}

void Time::Increment()
{
    secs++;
    if (secs >= 60)
    {
        secs %= 60;
        mins++;
    }
    if (mins >= 60)
    {
        mins %= 60;
        hrs++;
    }
    if (hrs >= 24)
    {
        hrs %= 24;
    }
}

void Time::Write() const
{
    cout << setfill('0') << setw(2) << hrs << ":" << setfill('0') << setw(2) << mins << ":" << setfill('0') << setw(2) << secs;
}

Time::Time(int initHrs, int initMins, int initSecs) : hrs(initHrs), mins(initMins), secs(initSecs)
{
}

Time::Time() : hrs(0), mins(0), secs(0)
{
}
