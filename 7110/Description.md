# [template]class template from lecture 6

## Description
Implement the ```Stack``` template with pointer.
```
template <typename ElementType> //genericStack.h
class Stack
{
public:
	Stack();
	~Stack();
	void push(ElementType obj); 
	void pop();
	ElementType getTop() const;
	bool isEmpty() const;

private:
	struct Node // 栈结点类型
	{
		ElementType element; // 结点中存放的元素
		Node *next;			 // 指向下一结点的指针
	};
	Node *top; // 栈顶
}
```
## Output
```
8 7 6 5 4 3 2 1 
```
