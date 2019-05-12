#ifndef BASE_H
#define BASE_H
#include <iostream>
using namespace std;

class BASE {
    public: 
	BASE(int p1, int p2);
	
	int inc1();	
           int inc2();

	void display(); 
    
     private:
           int mem1, mem2;
};                                 

#endif
