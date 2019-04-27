//
//  main.cpp
//  C++
//
//  Created by 李天培 on 16/2/25.
//  Copyright © 2016年 lee. All rights reserved.
//
 #include <iostream>
#include "Inheritance.hpp"
using std::cin;
using std::cout;
using std::endl;
using std::string;
int main() {
    freopen("Tests/in1", "r", stdin);
    freopen("Tests/out1m", "w", stdout);
    int token;
    cin >> token;
    cout << "test token: " << token << endl;
    cout << "\ncreat base A" << endl;
    baseA ba;
    cout << "\ncreat base B" << endl;
    baseB bb;
    cout << "\ncreat derived A" << endl;
    derivedA da;
    cout << "\ncreat derived B" << endl;
    derivedB db;
    cout << "\ncreat C" << endl;
    C c;
    cout << "\ndestructor" << endl;
    return 0;
}