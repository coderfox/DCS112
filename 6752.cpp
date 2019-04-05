#ifndef PERSON_H_
#define PERSON_H_

#include <iostream>
using namespace std;

class Date
{
public:
  Date(int newYear, int newMonth, int newDay);
  int getYear();
  void setYear(int newYear);
  int getMonth();
  void setMonth(int);
  int getDay();
  void setDay(int);

private:
  int year;
  int month;
  int day;
};

class Person
{
public:
  Person(int _id, int year, int month, int day);
  Person(Person &); // copy constructor
  ~Person();
  int getId();
  Date *getBirthDate();

private:
  int id;
  Date *birthDate;
};

#endif

#include <algorithm>

using namespace std;

Date::Date(int y, int m, int d)
{
  year = y;
  month = m;
  day = d;
}

int Date::getYear() { return year; }

void Date::setYear(int y) { year = y; }

Person::Person(int id, int year, int month, int day)
{

  this->id = id;

  birthDate = new Date(year, month, day);
}

Person::Person(Person &rhs) : id(rhs.id)
{
  birthDate = new Date(0, 0, 0);
  copy(rhs.birthDate, rhs.birthDate + 1, birthDate);
}

Person::~Person() { delete birthDate; }

int Person::getId() { return id; }

Date *Person::getBirthDate() { return birthDate; }
