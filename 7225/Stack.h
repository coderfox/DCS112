const int MAX_LEN = 5;

template <class T>
class Stack
{
public:
    explicit Stack();

    bool empty() const;

    int size() const;

    T &top();

    const T &top() const;

    void push(const T &x);

    void pop();

private:
    T data[MAX_LEN];

    int stack_size;
};

template <class T>
Stack<T>::Stack()
{
    stack_size = 0;
}

template <class T>
bool Stack<T>::empty() const
{
    return size() == 0;
}

template <class T>
int Stack<T>::size() const
{
    return stack_size;
}

template <class T>
T &Stack<T>::top()
{
    if (empty())
        throw 1;
    return data[stack_size - 1];
}

template <class T>
const T &Stack<T>::top() const
{
    if (empty())
        throw 1;
    return data[stack_size - 1];
}

template <class T>
void Stack<T>::push(const T &x)
{
    if (stack_size >= MAX_LEN) // stack full
    {
        if (x > top())
            top() = x;
        return;
    }
    data[stack_size++] = x;
}

template <class T>
void Stack<T>::pop()
{
    if (empty())
        throw 1.;
    stack_size--;
}