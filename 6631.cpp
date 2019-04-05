#include <iostream>
#include <cstring>
using namespace std;

class Student
{
  public:
    int id;
    char name[50]; // Data field
    int age;       // Data field
    Student();
    Student(int, const char *, int);
    void set(int, const char *, int);
    void print();
};

Student::Student()
{
    id = 0;
    strcpy(name, "No Name");
    age = 18;
}
Student::Student(int id, const char *name = "No Name", int age = 0) : id(id), age(age)
{
    strcpy(this->name, name);
}
void Student::set(int id, const char *name, int age)
{
    this->id = id;
    this->age = age;
    strcpy(this->name, name);
}
void Student::print()
{
    cout << this->name << " (" << this->id << ") is " << this->age << " years old." << endl;
}