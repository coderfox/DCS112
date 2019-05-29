template <typename T, int N>
class Stack
{
public:
    Stack();
    ~Stack();
    bool empty();
    T peek();
    void push(T value);
    T pop();
    int size();

private:
    T *elements;
    int num;
};

template <typename T, int N>
Stack<T, N>::Stack()
{
    elements = new T[N];
    num = 0;
}

template <typename T, int N>
Stack<T, N>::~Stack()
{
    delete[] elements;
}

template <typename T, int N>
bool Stack<T, N>::empty()
{
    return num == 0;
}

template <typename T, int N>
T Stack<T, N>::peek()
{
    return elements[num - 1];
}

template <typename T, int N>
void Stack<T, N>::push(T value)
{
    elements[num++] = value;
}

template <typename T, int N>
T Stack<T, N>::pop()
{
    return elements[--num];
}

template <typename T, int N>
int Stack<T, N>::size()
{
    return num;
}
