#include "demo.hpp"

int main()
{
    char ch1 = 'A', ch2 = 'B';
    int iv1 = 3, iv2 = 5;
    double dv1 = 2.8, dv2 = 8.5;

    // 调用第一个函数模板的实例
    demoFunc(dv1, dv2);

    // 调用第二个函数模板的实例
    demoFunc(iv1);

    // 调用非模板函数demoFunc(int, int)
    demoFunc(iv1, iv2);

    // 调用非模板函数demoFunc(int, int)（进行隐式类型转换）
    demoFunc(ch1, iv2);

    return 0;
}
