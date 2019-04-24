#include <iostream>
#include <string>
#include "complex.h"
using namespace std;

int main() {
    string complexString1;
    char op;
    string complexString2;
    cin >> complexString1 >> op >> complexString2;

    Complex complex1;
    complex1.fromString(complexString1);
    Complex complex2;
    complex2.fromString(complexString2);
    Complex complex3;

    if (op == '+') {
        complex3 = complex1 + complex2;
    } else if (op == '-') {
        complex3 = complex1 - complex2;
    } else if (op == '*') {
        complex3 = complex1 * complex2;
    } else if (op == '/') {
        complex3 = complex1 / complex2;
    }
    cout << complex1 << " " << op
    << " (" << complex2 << ") = " << complex3 << endl;
    return 0;
}

