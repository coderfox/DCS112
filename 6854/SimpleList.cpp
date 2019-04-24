#include "SimpleList.hpp"
#include <sstream>
#include <algorithm>

using namespace std;

list::list() : head(nullptr), _size(0)
{
}
list::list(const list &rhs) : list()
{
    if (rhs.head == nullptr)
        return;
    head = new node(rhs.head->data, rhs.head->next);
    _size = rhs._size;
    node *ptr = head;
    while (ptr->next != nullptr)
    {
        ptr->next = new node(ptr->next->data, ptr->next->next);
        ptr = ptr->next;
    }
}
list &list::operator=(const list &rhs)
{
    list tmp(rhs);
    swap(head, tmp.head);
    swap(_size, tmp._size);
    return *this;
}
list::~list()
{
    clear();
}

bool list::empty(void) const
{
    return _size == 0;
}
int list::size(void) const
{
    return _size;
}

std::string list::toString(void) const
{
    stringstream ss;
    node *ptr = head;
    while (ptr != nullptr)
    {
        ss << ptr->data << "->";
        ptr = ptr->next;
    }
    ss << "NULL";
    return ss.str();
}

void list::insert(int position, const int &data)
{
    if (position > _size)
        return;
    _size++;
    if (position == 0)
    {
        head = new node(data, head);
    }
    else
    {
        node *ptr = head;
        for (int i = 0; i < position - 1; i++)
            ptr = ptr->next;
        ptr->next = new node(data, ptr->next);
    }
}
void list::erase(int position)
{
    if (position >= _size)
        return;
    _size--;
    if (position == 0)
    {
        node *ptr = head;
        head = head->next;
        delete ptr;
        return;
    }
    node *ptr = head;
    for (int i = 0; i < position - 1; i++)
        ptr = ptr->next;
    node *pdel = ptr->next;
    ptr->next = ptr->next->next;
    delete pdel;
}

list &list::sort(void)
{
    if (_size <= 1)
        return *this;
    list left, right;
    node *ptr = head;
    int pivot = ptr->data;
    for (int i = 1; i < _size; i++)
    {
        ptr = ptr->next;
        if (ptr->data < pivot)
        {
            left.insert(left.size(), ptr->data);
        }
        else
        {
            right.insert(right.size(), ptr->data);
        }
    }
    left.sort();
    right.sort();
    clear();
    ptr = left.head;
    for (int i = 0; i < left.size(); i++)
    {
        insert(size(), ptr->data);
        ptr = ptr->next;
    }
    insert(size(), pivot);
    ptr = right.head;
    for (int i = 0; i < right.size(); i++)
    {
        insert(size(), ptr->data);
        ptr = ptr->next;
    }
    return *this;
}