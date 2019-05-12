# [inhenritance] Base & Derived from_lecture 4

## description

```cpp
简单的类继承练习，有以下类声明：
class BASE {
    public:
	BASE(int p1, int p2);

	int inc1();
           int inc2();

	void display();

     private:
           int mem1, mem2;
};

class DERIVED : public BASE{
    public:
	DERIVED(int x1, int x2, int x3, int x4, int x5); 			int inc1() ;
	int inc3( ) ;
	void display( ) ;

    private:
            int mem3;
	BASE mem4;
};

```
