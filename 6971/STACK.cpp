#include "STACK.h"
#include <iostream>

using namespace std;

STACK::STACK() : top(nullptr)
{
} // 构造函数，设置栈顶为空指针

STACK::~STACK()
{
    while (top != nullptr)
        pop();
} // 析构函数，释放堆栈结点占用的存储空间

void STACK::push(ELEMENT obj)
{
    NODE *node = new NODE;

    node->element = obj;
    node->link = top;

    top = node;
} // 将元素obj压入栈顶
void STACK::pop()
{
    auto pdel = top;
    top = top->link;
    delete pdel;
} // 将当前栈顶的元素弹出栈中。要求：栈不为空。
ELEMENT STACK::get_top()
{
    return top->element;
} // 返回当前栈顶的元素值。要求：栈不为空。
int STACK::is_empty()
{
    return top == nullptr;
} // 判断当前堆栈是否为空，空则返回1，非空则返回0
void STACK::display()
{
    auto pcur = top;
    while (pcur != nullptr)
    {
        cout << pcur->element << ' ';
        pcur = pcur->link;
    }
    cout << endl;
} // 自顶向下显示堆栈中的元素