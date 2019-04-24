#include <sstream>
#include <algorithm>
#include "List.hpp"

using namespace std;

typedef list::size_type lsize_t;
typedef list::data_type data_t;
typedef list::listNode node_t;

list::list() : head(nullptr), tail(nullptr), _size(0)
{
}
list::list(const data_type data[], int length) : list()
{
    for (auto ptr = data; ptr < data + length; ptr++)
    {
        push_back(*ptr);
    }
}
list::list(const list &rhs) : list()
{
    *this = rhs;
}
list &list::operator=(const list &rhs)
{
    clear();
    node_t *ppos = rhs.head;
    while (ppos != nullptr)
    {
        push_back(ppos->data);
        ppos = ppos->next;
    }
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
lsize_t list::size(void) const
{
    return _size;
}
data_t &list::front(void) const
{
    return head->data;
}
data_t &list::back(void) const
{
    return tail->data;
}
std::string list::toString(void) const
{
    stringstream ss;
    if (head == nullptr && tail == nullptr)
        return "NULL";
    ss << "NULL<-";
    const node_t *ptr = head;
    while (ptr != nullptr)
    {
        ss << ptr->data;
        ptr = ptr->next;
        if (ptr != nullptr)
            ss << "<->";
    }
    ss << "->NULL";
    return ss.str();
}
void list::assign(const list &rhs)
{
    *this = rhs;
}
void list::assign(const data_t data[], int length)
{
    *this = list(data, length);
}
void list::push_front(const data_t &data)
{
    head = new node_t(data, head, nullptr);
    if (head->next != nullptr)
    {
        head->next->prev = head;
    }
    if (tail == nullptr)
        tail = head;
    _size++;
}
void list::push_back(const data_t &data)
{
    tail = new node_t(data, nullptr, tail);
    if (tail->prev != nullptr)
    {
        tail->prev->next = tail;
    }
    if (head == nullptr)
        head = tail;
    _size++;
}
void list::pop_front(void)
{
    if (head == nullptr)
        return;
    auto pdel = head;
    head = head->next;
    if (head != nullptr)
        head->prev = nullptr;
    delete pdel;
    _size--;
}
void list::pop_back(void)
{
    if (tail == nullptr)
        return;
    auto pdel = tail;
    tail = tail->prev;
    if (tail != nullptr)
        tail->next = nullptr;
    delete pdel;
    _size--;
}
void list::insert(int position, const data_t &data)
{
    auto ppos = at(position);
    if (ppos == nullptr)
    {
        if (position == 0)
            push_front(data);
        else if (position == _size)
            push_back(data);
        return;
    }
    auto node = new node_t(data, ppos, ppos->prev);
    if (ppos->prev != nullptr)
        ppos->prev->next = node;
    ppos->prev = node;
    if (ppos == head)
        head = node;
    if (ppos == tail)
        tail = node;
    _size++;
}
void list::erase(int position)
{
    auto ppos = at(position);
    if (ppos == nullptr)
        return;
    if (ppos == head)
        head = ppos->next;
    if (ppos == tail)
        tail = ppos->prev;
    if (ppos->prev != nullptr)
        ppos->prev->next = ppos->next;
    if (ppos->next != nullptr)
        ppos->next->prev = ppos->prev;
    delete ppos;
    _size--;
}
void list::clear(void)
{
    auto ppos = head;
    while (ppos != nullptr)
    {
        auto pdel = ppos;
        ppos = ppos->next;
        delete pdel;
    }
    head = nullptr;
    tail = nullptr;
    _size = 0;
}
void list::split(int position, list *des1, list *dest2)
{
    auto ptr = head;
    auto ppos = at(position);
    des1->clear();
    dest2->clear();
    for (; ptr != ppos; ptr = ptr->next)
    {
        des1->push_back(ptr->data);
    }
    for (; ptr != nullptr; ptr = ptr->next)
    {
        dest2->push_back(ptr->data);
    }
}
list &list::merge(const list &src1, const list &src2)
{
    list li;
    for (auto ptr = src1.head; ptr != nullptr; ptr = ptr->next)
    {
        li.push_back(ptr->data);
    }
    for (auto ptr = src2.head; ptr != nullptr; ptr = ptr->next)
    {
        li.push_back(ptr->data);
    }
    *this = li;
    return *this;
}
list &list::remove_if(bool (*condition)(listPointer))
{
    for (auto ptr = head; ptr != nullptr;)
    {
        auto next = ptr->next;
        if (condition(ptr))
        {
            if (ptr == head)
                head = ptr->next;
            if (ptr == tail)
                tail = ptr->prev;
            if (ptr->prev != nullptr)
                ptr->prev->next = ptr->next;
            if (ptr->next != nullptr)
                ptr->next->prev = ptr->prev;
            delete ptr;
            _size--;
        }
        ptr = next;
    }
    return *this;
}
list &list::unique(void)
{
    for (auto ptr = head; ptr != nullptr; ptr = ptr->next)
    {
        for (auto pfind = ptr->next; pfind != nullptr;)
        {
            auto next = pfind->next;
            if (pfind->data == ptr->data)
            {
                if (pfind == head)
                    head = pfind->next;
                if (pfind == tail)
                    tail = pfind->prev;
                if (pfind->prev != nullptr)
                    pfind->prev->next = pfind->next;
                if (pfind->next != nullptr)
                    pfind->next->prev = pfind->prev;
                delete pfind;
                _size--;
            }
            pfind = next;
        }
    }
    return *this;
}
list &list::reverse(void)
{
    auto ppos = head;
    while (ppos != nullptr)
    {
        swap(ppos->prev, ppos->next);
        ppos = ppos->prev;
    }
    swap(head, tail);
    return *this;
}
data_t &list::operator[](int index)
{
    return at(index)->data;
}
list &list::operator+=(const list &rhs)
{
    for (auto ptr = rhs.head; ptr != nullptr; ptr = ptr->next)
    {
        push_back(ptr->data);
    }
    return *this;
}
std::ostream &operator<<(std::ostream &os, const list &li)
{
    os << li.toString();
    return os;
}
