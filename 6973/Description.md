# [Interitance]Duplicate interitance

给定如下继承关系：
```c++
class BASE {
 public:
     int i;
};

class BASE1: public BASE {};

class BASE2: public BASE {};

class DERIVED: public BASE1, public BASE2 {};
```

请根据 main 函数以及下面的输入输出来实现来两个函数：
```c++
DERIVED set(int, int);
void get(DERIVED &);
```

# Input
```
2
1 2
3 4
```

# Output
```
BASE1 i: 1
BASE2 i: 2
BASE1 i: 3
BASE2 i: 4
```