#include <cstddef>

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

template <typename ElementType, std::size_t N>
Stack<ElementType, N>::Stack()
{
    count = 0;
}

template <typename ElementType, std::size_t N>
void Stack<ElementType, N>::push(ElementType obj)
{
    elements[count++] = obj;
}

template <typename ElementType, std::size_t N>
void Stack<ElementType, N>::pop()
{
    count--;
}

template <typename ElementType, std::size_t N>
ElementType Stack<ElementType, N>::getTop() const
{
    return elements[count - 1];
}

template <typename ElementType, std::size_t N>
bool Stack<ElementType, N>::isEmpty() const
{
    return count == 0;
}
