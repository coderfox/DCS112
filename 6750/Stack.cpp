#include "Stack.hpp"
#include <algorithm>
#include <iostream>
#include <iomanip>

#define DEBUG

using namespace std;

Stack::Stack() : data(nullptr)
{
}
Stack::Stack(const Stack &rhs) : data(rhs.data)
{
    if (data == nullptr)
        return;
    node *prev_data = data;
    data = new node;
#ifdef DEBUG
    cout << "[NEW]" << hex << data << endl;
#endif
    copy(prev_data, prev_data + 1, data);
    node *cur = data;
    while (cur->next != nullptr)
    {
        node *prev_next = cur->next;
        cur->next = new node;
#ifdef DEBUG
        cout << "[NEW]" << hex << cur->next << endl;
#endif
        copy(prev_next, prev_next + 1, cur->next);
        cur = cur->next;
    }
}
Stack::~Stack()
{
    clear();
}

Stack Stack::operator=(const Stack &rhs)
{
    Stack tmp = Stack(rhs);
    swap(tmp.data, this->data);
    return *this;
}
void Stack::push(int num)
{
    data = new node(num, data);
#ifdef DEBUG
    cout << "[NEW]" << hex << data << endl;
#endif
}
void Stack::pop()
{
    node *to_del = data;
    data = data->next;
#ifdef DEBUG
    cout << "[DELETE]" << hex << to_del << endl;
#endif
    delete to_del;
}
int Stack::top() const
{
    return data->num;
}
bool Stack::empty() const
{
    return data == nullptr;
}
void Stack::clear()
{
    while (!empty())
        pop();
    // data = nullptr;
}