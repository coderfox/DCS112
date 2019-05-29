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
        Node *next;          // 指向下一结点的指针
    };
    Node *top; // 栈顶
};

template <typename ElementType>
Stack<ElementType>::Stack()
{
    top = nullptr;
}

template <typename ElementType>
Stack<ElementType>::~Stack()
{
    while (!isEmpty())
    {
        pop();
    }
}

template <typename ElementType>
void Stack<ElementType>::push(ElementType obj)
{
    top = new Node{obj, top};
}

template <typename ElementType>
void Stack<ElementType>::pop()
{
    auto to_del = top;
    top = top->next;
    delete to_del;
}

template <typename ElementType>
ElementType Stack<ElementType>::getTop() const
{
    return top->element;
}

template <typename ElementType>
bool Stack<ElementType>::isEmpty() const
{
    return top == nullptr;
}
