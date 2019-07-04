#include "Stack.hpp"
#include <algorithm>

using namespace std;

void Stack::copyOnWrite()
{
    if (*p.count == 1)
        return;
    auto src = p.data;
    (*p.count)--;
    p.data = nullptr;
    p.count = new int(1);
    for (; src != nullptr && src->next != nullptr; src = src->next)
    {
        push(src->num);
    }
}

Stack::Stack()
{
    p.data = nullptr;
    p.count = new int(1);
}

Stack::Stack(const Stack &rhs)
{
    p.data = rhs.p.data;
    p.count = rhs.p.count;
    (*p.count)++;
}

Stack::~Stack()
{
    (*p.count)--;
    if (*p.count == 0)
    {
        delete p.count;
        while (!empty())
            pop();
    }
}

Stack Stack::operator=(const Stack &rhs)
{
    Stack tmp = rhs;
    swap(tmp.p, p);
    return *this;
}

void Stack::push(int num)
{
    copyOnWrite();
    p.data = new node(num, p.data);
}

void Stack::pop()
{
    copyOnWrite();
    auto pdel = p.data;
    p.data = pdel->next;
    delete pdel;
}

int Stack::top() const
{
    return p.data->num;
}

bool Stack::empty() const
{
    return p.data == nullptr;
}

void Stack::clear()
{
    while (!empty())
        pop();
}