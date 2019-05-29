#include "array_basedGStack.hpp"
#include <iostream>
using namespace std;

int main()
{
    Stack<int, 10> stack; // 声明一个保存10个int型元素的堆栈
    stack.push(1);
    stack.push(2);
    stack.push(3);
    cout << stack.getTop() << endl;
    stack.pop();
    cout << stack.getTop() << endl;
    stack.pop();
    cout << stack.isEmpty() << endl;
    stack.pop();
    cout << stack.isEmpty() << endl;
    return 0;
}
