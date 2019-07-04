#include <iostream>
#include "source.h"

using namespace std;

void f1(int);
void f2(int);
void f3(int);

int main() {
    for (int i = 0; i < 4; i++)
        f1(i);
    cout << "End of main" << endl;
    return 0;
}
