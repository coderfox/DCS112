# [template]non-type parameter class template from lecture 6

## Description
Implement the following template:
```
template <typename ElementType, std::size_t N>
class Stack
{
public:
    Stack();
    void push(ElementType obj);
    void pop();
    ElementType getTop() const;
    bool isEmpty() const;

private:
    ElementType elements[N]; // 堆栈中存放的元素
    std::size_t count;       // 堆栈中现有元素的数目
};
```
**Note: size_t is in header <cstddef\>**
## Output
```
3
2
0
1

```