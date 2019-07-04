#include "Stack.hpp"
#include <algorithm>
#include <iostream>
#include <iomanip>

#define DEBUG

using namespace std;

Stack::Stack()
{
    data = nullptr;
}

Stack::Stack(const Stack &rhs) : Stack()
{
    for (auto ptr = rhs.data; ptr != nullptr; ptr = ptr->next)
    {
        push(ptr->num);
        // cout << "[DEBUG] push " << ptr->num << endl;
    }
}

Stack::~Stack()
{
    clear();
}

Stack Stack::operator=(const Stack &rhs)
{
    Stack tmp = rhs;
    swap(data, tmp.data);
    return *this;
}

void Stack::push(int num)
{
    data = new node(num, data);
}

void Stack::pop()
{
    auto pdel = data;
    data = pdel->next;
    delete pdel;
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
}