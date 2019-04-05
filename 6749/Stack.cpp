#include "Stack.hpp"
#include <algorithm>

using namespace std;

void Stack::copyOnWrite()
{
    if (*p.count > 1)
    {
        node *prev_data = p.data;
        int *prev_count = p.count;
        p.data = new node;
        p.count = new int(0);
        copy(prev_data, prev_data + 1, p.data);
        node *cur = p.data;
        while (cur->next != nullptr)
        {
            node *prev_next = cur->next;
            cur->next = new node;
            copy(prev_next, prev_next + 1, cur->next);
            cur = cur->next;
        }
        (*prev_count)--;
        (*p.count)++;
    }
}

Stack::Stack() : p({nullptr, new int(1)})
{
}
Stack::Stack(const Stack &rhs) : p(rhs.p)
{
    (*rhs.p.count)++;
}
Stack::~Stack()
{
    (*p.count)--;
    if (*p.count <= 0)
    {
        delete p.data;
        delete p.count;
    }
}

Stack Stack::operator=(const Stack &rhs)
{
    return Stack(rhs);
}
void Stack::push(int num)
{
    copyOnWrite();
    p.data = new node(num, p.data);
}
void Stack::pop()
{
    copyOnWrite();
    node *to_del = p.data;
    p.data = p.data->next;
    delete to_del;
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
    p.data = nullptr;
}