# [Overloading operator] 重载操作符() _ from lecture 3

## description
```
重载操作符（），使得能够对象能够像函数一样调用（函数对象）
class Exchange
{
    public:
	void operator()(int&, int&);
};


```