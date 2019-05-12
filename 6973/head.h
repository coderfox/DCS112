#include <iostream>

class BASE {
 public:
     int i;
};

class BASE1: public BASE {};

class BASE2: public BASE {};

class DERIVED: public BASE1, public BASE2 {};
