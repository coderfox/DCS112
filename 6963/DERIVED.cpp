#include "DERIVED.h"
#include <iostream>

using namespace std;

DERIVED::DERIVED(int x1, int x2, int x3, int x4, int x5) : BASE(x1, x2), mem3(x5), mem4(x3, x4)
{
}

int DERIVED::inc1()
{
    BASE::inc1();
}

int DERIVED::inc3()
{
    mem3++;
}

void DERIVED::display()
{
    BASE::display();
    mem4.display();
    cout << "mem3=" << mem3 << endl;
}
