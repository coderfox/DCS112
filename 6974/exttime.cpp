#include "exttime.h"
#include <iostream>

using namespace std;

ExtTime::ExtTime(int initHrs, int initMins, int initSecs, ZoneType initZone) : Time(initHrs, initMins, initSecs), zone(initZone)
{
}

ExtTime::ExtTime() : Time(), zone(EST)
{
}

void ExtTime::Set(int hours, int minutes, int seconds, ZoneType timeZone)
{
    Time::Set(hours, minutes, seconds);
    zone = timeZone;
}

void ExtTime::Write() const
{
    Time::Write();
    cout << " ";
    switch (zone)
    {
    case EST:
        cout << "EST";
        break;
    case CST:
        cout << "CST";
        break;
    case MST:
        cout << "MST";
        break;
    case PST:
        cout << "PST";
        break;
    case EDT:
        cout << "EDT";
        break;
    case CDT:
        cout << "CDT";
        break;
    case MDT:
        cout << "MDT";
        break;
    case PDT:
        cout << "PDT";
        break;
    }
}
