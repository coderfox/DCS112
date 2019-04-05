class Date
{
  public:
    Date(int y, int m, int d)
    {
        year = y;
        month = m;
        day = d;
    }

    int getYear() { return year; }

    void setYear(int y) { year = y; }

  private:
    int year, month, day;
};

class Person

{

  public:
    Person(int id, int year, int month, int day)
    {

        this->id = id;

        birthDate = new Date(year, month, day);
    }

    ~Person() { delete birthDate; }

    int getId() { return id; }

    Date *getBirthDate() const { return birthDate; }

  private:
    int id;

    Date *birthDate;
};