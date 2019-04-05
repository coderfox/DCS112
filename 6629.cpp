#include <iostream>

using namespace std;

class Foo
{
  public:
    Foo();
    Foo(bool b);
    void p();

  private:
    int x, y;
};

Foo::Foo()
{
    x = 0;
    y = 0;
}
Foo::Foo(bool b)
{
    if (b)
    {
        cout << "please enter x and y.\n";
        cin >> x >> y;
    }
    else
        x = y = 0;
}
void Foo::p()
{
    cout << "x is " << x << ", "
         << "y is " << y << ".\n";
}
