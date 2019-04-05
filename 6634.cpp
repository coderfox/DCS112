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
    //void set(int, char*, int);
    //void print();
};

void set(Student &, int, const char *, int);
void print(Student);

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
void set(Student &stu, int id, const char *name, int age)
{
    stu.id = id;
    stu.age = age;
    strcpy(stu.name, name);
}
void print(Student stu)
{
    cout << stu.name << " (" << stu.id << ") is " << stu.age << " years old." << endl;
}

#include <iostream>
#include <cstring>

using namespace std;

int main()
{

    Student std1, std2(123, "Larry Jordan", 18), std3(124);
    set(std1, 100, "Steven Gates", 61);
    print(std1);
    print(std2);
    print(std3);
    return 0;
}
