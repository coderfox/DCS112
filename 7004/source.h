#include <cstring>

using namespace std;

class base
{
    char name[20];
    int age;

public:
    base() {}
    void setname(char arr[])
    {
        strcpy(this->name, arr);
    }
    void setage(int age)
    {
        this->age = age;
    }
    char *getname()
    {
        return this->name;
    }
    int getage()
    {
        return this->age;
    }
};

class leader : virtual public base
{
private:
    char job[20];
    char dep[20];

public:
    void setjob(char *job)
    {
        strcpy(this->job, job);
    }
    void setdep(char *dep)
    {
        strcpy(this->dep, dep);
    }
    char *getjob()
    {
        return this->job;
    }
    char *getdep()
    {
        return this->dep;
    }
};

class engineer : virtual public base
{
private:
    char major[20];
    char prof[20];

public:
    void setmajor(char *major)
    {
        strcpy(this->major, major);
    }
    void setprof(char *prof)
    {
        strcpy(this->prof, prof);
    }
    char *getmajor()
    {
        return major;
    }
    char *getprof()
    {
        return prof;
    }
};

class chairman : public leader, public engineer
{
private:
public:
};
