#include <cstddef>
#include <algorithm>
#include <iterator>

using namespace std;

template <typename T>
class Stack
{
public:
    Stack();
    bool empty();
    T peek();
    void push(T value);
    T pop();
    int getSize();
    void printStack();

private:
    T _data[1000];
    size_t count;
};

template <typename T>
Stack<T>::Stack()
{
    count = 0;
}

template <typename T>
bool Stack<T>::empty()
{
    return count == 0;
}

template <typename T>
T Stack<T>::peek()
{
    return _data[count - 1];
}

template <typename T>
void Stack<T>::push(T value)
{
    _data[count++] = value;
}

template <typename T>
T Stack<T>::pop()
{
    count--;
    return _data[count];
}

template <typename T>
int Stack<T>::getSize()
{
    return count;
}

template <typename T>
void Stack<T>::printStack()
{
    for (auto id = _data; id < _data + count; id++)
    {
        cout << *id << endl;
    }
}
