#include <iostream>
#include <cstdlib>
#include "STACK.h"
using namespace std;

int main()
{
    freopen("Tests/in1", "r", stdin);
    freopen("Tests/out1m", "w", stdout);
    STACK turner;       // 声明一个元素为整数类型的堆栈
    ELEMENT user_input; // 用户输入的元素（即整数类型）
    int loop;           // 循环变量
    int max_input = 20;
    for (loop = 1; loop <= max_input; loop++) // 由用户输入若干个元素
    {
        turner.push(loop); // 将用户输入的元素压入栈中
    }

    turner.display(); // 测试堆栈中的内容

    for (loop = 1; loop <= max_input; loop++)
    {
        if (!turner.is_empty()) // 仅当堆栈不为空时才处理
        {
            user_input = turner.get_top(); // 取出栈顶元素的值
            turner.pop();                  // 将栈顶元素弹出
            cout << loop << " " << user_input << endl;
        }
    }

    return 0;
}
