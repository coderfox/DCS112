#include <iostream>

using namespace std;

void addxy(int x, int y, int total)
{
    total = x + y;
    cout << "Total from inside addxy: " << total << endl;
}
void subxy(int x, int y, int &total)
{
    total = x - y;
    cout << "Total from inside subxy: " << total << endl;
}

#include <stdio.h>

void printtotal(int total)
{
    printf("Total in Main: %d\n", total);
}
int main()
{

    int x, y, total;
    x = 10;
    y = 5;
    total = 0;

    printtotal(total);
    addxy(x, y, total);

    printtotal(total);

    subxy(x, y, total);
    printtotal(total);
    return 0;
}
