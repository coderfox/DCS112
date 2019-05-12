#ifndef DERIVED_H
#define DERIVED_H
#include "BASE.h"

class DERIVED : public BASE{
    public:	
	DERIVED(int x1, int x2, int x3, int x4, int x5); 			int inc1() ;
	int inc3( ) ;
	void display( ) ;

    private:           
            int mem3;
	BASE mem4;
};


#endif
