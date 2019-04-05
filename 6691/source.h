class Date
{
  public:
    Date(int newYear, int newMonth, int newDay);
    int getYear();
    void setYear(int newYear);
    int getMonth();
    int getDay();
    void setMonth(int Month);
    void setDay(int Day);

  private:
    int year;
    int month;
    int day;
};

Date::Date(int year, int month, int day) : year(year), month(month), day(day) {}
int Date::getYear() { return year; }
void Date::setYear(int newYear) { year = newYear; }
int Date::getMonth() { return month; }
int Date::getDay() { return day; }
void Date::setMonth(int newMonth) { month = newMonth; }
void Date::setDay(int newDay) { day = newDay; }

class Person
{
  public:
    Person(int id, int year, int month, int day);
    Person(const Person &); // copy constructor
    ~Person();
    int getId();
    Date *getBirthDate();
    static int getNumberOfObjects(); //return the number of Person objects

  private:
    int id;
    Date *birthDate;
    static int numberOfObjects; //count the number of Person objects
};

int Person::numberOfObjects = 0;

Person::Person(int id, int year, int month, int day) : id(id)
{
    birthDate = new Date(year, month, day);
    numberOfObjects++;
}
Person::Person(const Person &rhs) : Person(rhs.id, rhs.birthDate->getYear(), rhs.birthDate->getMonth(), rhs.birthDate->getDay())
{
}
Person::~Person()
{
    delete birthDate;
    numberOfObjects--;
}

int Person::getId() { return id; }
Date *Person::getBirthDate() { return birthDate; }
int Person::getNumberOfObjects() { return numberOfObjects; }
