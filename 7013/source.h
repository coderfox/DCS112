#include <string>

using std::string;

struct Person
{
    string name;
    string address;
    string phoneNumber;
    string email;
    virtual string toString()
    {
        return "Person";
    }
};

struct Student : public Person
{
    enum class_status
    {
        frssman,
        sophomore,
        junior,
        senior
    };
    class_status status;
    virtual string toString()
    {
        return "Student";
    }
};

struct MyDate
{
    int year;
    int month;
    int day;
    virtual string toString()
    {
        return "MyDate";
    }
};

struct Employee : public Person
{
    string office;
    int salary;
    MyDate dateHired;
    virtual string toString()
    {
        return "Employee";
    }
};

struct Faculty : public Employee
{
    string officeHours;
    int rank;
    virtual string toString()
    {
        return "Faculty";
    }
};

struct Staff : public Employee
{
    string title;
    virtual string toString()
    {
        return "Staff";
    }
};