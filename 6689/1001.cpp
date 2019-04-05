#include "Object.h"

void TestObjects()
{
    // Object 1 is created, we've got 1 object(s) now!
    Object obj1(1);
    { // Object 2 is created, we've got 2 object(s) now!
        Object obj2(2);
        {
            // Object 3 is created, we've got 3 object(s) now!
            Object obj3(3);
            // Object 3 is deleted, we've got 2 object(s) now!
        }
        // Object 2 is deleted, we've got 1 object(s) now!
    }
    // Object 4 is created, we've got 2 object(s) now!
    Object obj4(4);
    // Object 4 is deleted, we've got 1 object(s) now!
    // Object 1 is deleted, we've got 0 object(s) now!
}