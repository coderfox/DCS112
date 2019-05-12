#include <iostream>
#include "head.h"

using namespace std;

DERIVED set(int a, int b)
{
    DERIVED d;
    d.BASE1::i = a;
    d.BASE2::i = b;
    return d;
}

void get(DERIVED &obj)
{
    cout << "BASE1 i: " << obj.BASE1::i << endl;
    cout << "BASE2 i: " << obj.BASE2::i << endl;
}
