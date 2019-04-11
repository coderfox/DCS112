#include "Stack.hpp"
void Stack::copyOnWrite()
{
    if (*(this->p.count) == 1)
        return;
    if (*(this->p.count) > 1)
        *(this->p.count) -= 1;
    node *now = new node;
    now->next = NULL;
    node *pre;
    pre = now;
    while (p.data->next != NULL)
    {
        node *newptr = new node;
        p.data = p.data->next;
        newptr->num = p.data->num;
        now->next = NULL;
        if (!now->next)
        {
            now->next = newptr;
            pre = newptr;
        }
        else
        {
            pre->next = newptr;
            pre = pre->next;
        }
    }
    p.count = new int;
    *(p.count) = 1;
    p.data = now;
}
Stack::Stack()
{
    p.data = new node;
    p.data->next = NULL;
    p.count = new int;
    *(p.count) = 1;
}
Stack::Stack(const Stack &s)
{
    p.count = s.p.count;
    p.data = s.p.data;
    *(p.count) += 1;
    ;
}
Stack::~Stack()
{
    if (*(p.count) > 1)
    {
        *(p.count) -= 1;
        p.data = NULL;
    }
    else
    {
        node *nowptr = p.data;
        while (p.data != NULL)
        {
            nowptr = p.data;
            p.data = p.data->next;
            delete nowptr;
        }
        delete p.count;
    }
}
Stack Stack::operator=(const Stack &s)
{
    if (this == &s)
    {
        //        *(p.count) -= 1;
        return *this;
    }
    this->~Stack();
    this->p.count = s.p.count;
    this->p.data = s.p.data;
    *(p.count) += 1;
    return *this;
}
void Stack::push(int x)
{
    copyOnWrite();
    node *now = p.data;
    while (now->next != NULL)
    {
        now = now->next;
    }
    node *newptr = new node;
    newptr->num = x;
    newptr->next = NULL;
    now->next = newptr;
}
void Stack::pop()
{
    copyOnWrite();
    node *now = p.data;
    node *pre;
    while (now->next != NULL)
    {
        pre = now;
        now = now->next;
    }
    delete now;
    pre->next = NULL;
}
int Stack::top() const
{
    if (p.data->next == NULL)
        return 0;
    node *now = p.data;
    while (now->next != NULL)
    {
        now = now->next;
    }
    return now->num;
}
bool Stack::empty() const
{
    if (p.data->next == NULL)
        return true;
    else
        return false;
}
void Stack::clear()
{
    if (*(this->p.count) > 1)
    {
        *(p.count) -= 1;
        p.data = new node;
        p.data->next = NULL;
    }
    else
    {
        node *nowptr = p.data;
        while (p.data != NULL)
        {
            nowptr = p.data;
            p.data = p.data->next;
            delete nowptr;
        }
        p.data = new node;
    }
}